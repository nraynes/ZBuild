ZBuild is a wrapper for Qt to make GUI development easy and simple for quick prototyping or basic tools.

Features:

There are 3 different types of *decorator** wrapped widgets:
Display Widgets
Control Widgets
Container Widgets

Display widgets are widgets that display something.
Control widgets are widgets that control things.
Container widgets are widgets that contain other widgets.

Pretty simple right.

The Container widgets are structure as **composites** to allow for easy handling of the internal widgets. This type of widget allows you to configure the layout inside the container. The root of the gui is a Container widget as well.

Each widget implements events that use a **state** design pattern so that different behaviour can be defined when the widget is in different states, or different events happen, or none at all.

There is an **adapter** design pattern that takes specific params, and converts them to the appropriate params for Qt so that everything has one interface.

A **Factory** supplies each of the wrapped widgets via a **builder** for that widget.

The **builder** for the widget will allow you to create and configure a widget easily in a chainable format. This will also allow you to bind control widgets to events and allows the current widget access to the full app and all widgets, able to reference one by id if needed in the event that updates are needed.

Finally, there will be a **builder** that allows you to build the entire GUI, with the root functioning as a Container widget, allowing you to set the layout. You can chain commands to create new widgets, configure them, and access the whole gui container and all contained widgets for reference. You can set the active widget being modified with a specific command from the builder as well to go back and configure previously created widgets.

This allows you to functionally create a gui in one line of code.

You can create **prototypes** of widgets, layouts, or layout components like size or location to reuse throughout the application. These get saved to the root window as pointers in a hashmap so they can be retreived easily.

You will also be able to build individual widgets or layouts and store them in variables for use outside the builder if necessary via the actual widgetbuilder. You can add these widgets or layouts to another builder via the .use_prototype(prototype_id), but this can all be done in the main builder anyways since it will store pointers to the prototypes.

ZBuild basics:

ZBuild(**root_params) = create a new gui builder and set the root as the active widget. Root window is a special container type widget.
NOTE: The root window has properties that save specific information about the application such as storing:
    - widget prototypes. (May come with a few defaults, like multiple widgets in a container set as a template.)
    - layout prototypes. (May come with some default layouts.)
    - location prototypes. (May come with a few defaults, like "align_center", "align_left", etc.)
    - size prototypes. (May come with a few defaults, like "stretch", "fixed", etc.)
    - ID of root window, "root".
    - hashmap of widget pointers by id (for easy retrieval).
    - Window title.
    - Window icon.
    - Debug mode. (Shows bounding boxes and anchor points for debugging.)
    - etc.

.start() = Starts the application, no need to change the active widget if it precedes this, since this will exit the builde anyways.

.build() = Just builds the aplication, but does not start it.

# Any widget has access to this command.

.widget(widget_id)  # Returns a pointer to a specific widget from root via hashmap lookup. This allows you to change what widget is being built mid chain.
    .<widget_editor>

# Container Widgets

container  # Root window is a container, but this applies to all container widgets. 
    .<widget_editor>  # Edits the container widget.
    .get(widget_id)  # Gets a widget within this container specifically.
        .<widget_editor>
    .add()
        .use_prototype(prototype_id)  # Instantiate a prototyped widget.
            .<widget_editor>
        .<widget_type>(widget_id)
            .<widget_editor>
    .delete(widget_id)
        

# Widget editor.

.<method_that_called_widget>
    .layout()
        .<layout_manager>
        .use_prototype(prototype_id)  # Use a layout prototype. Will override all current layout settings.
    .<event_type>  # May or may not have event param.
        .after(milliseconds)  # Can specify time in ms to run bound method after event starts.
        .finished()  # Specifes to run bound method after event finishes
            .after(milliseconds)  # Can specify time in ms to run bound method after event finishes.
        .<modifier>(modifier_params)  # Specific events may have additional modifiers.
        .bind(method)  # Method recieves a pointer to the root window which contains the entire app. This also exits the event editor. Bound method defaults to running right when event starts unless modifers are present.
    .<configuration>(configuration_params)  # Specific widgets may have additional configuration options.
    .prototype(prototype_id)  # Creates a prototype of this widget that can be instantiated multiple times. Saves to root window.
    .done()  # Exits widget editor. Returns to the container hosting this widget.
    .build()  # Returns a fully built widget to use outside of the main builder.

# Layout manager.

.<method_that_called_layout_manager>
    .size()
        .<size_manager>
        .use_prototype(prototype_id)  # Use a size prototype. Will override all current size settings.
    .location()
        .<location_manager>
        .use_prototype(prototype_id)  # Use a location prototype. Will override all current location settings.
    .prototype(prototype_id)  # Creates a prototype of this layout that can be reused by multiple widgets. Saves to root window. # Does not save relative_to information.
    .build()  # Finalizes the layout and returns to the widget editor that called the manager.

## Size manager

.<method_that_called_size_manager>
    .auto()  # scales automatically to fit.
        .fit_content() # Scales to fit inner content. (Ex: text, other widgets inside container, etc.)
            .padding(value)  # Sets padding around inner content.
                .fixed()  # default. fixes padding so it cannot change. Can cause parts of widget to be hidden if window is to small.
                .scaled()  # allows padding to squish if window size changes and becomes too small. cannot be below 0.
                .unit()
                    .pixels()  # default.
                    .scale()  # scaled value where 1 represents the height or width value of the relative widget.
                        .relative_to(widget_id)  # Defaults to container holding this widget.
                    .percent()  # percent value, just the scaled value * 100.
                        .relative_to(widget_id)  # Defaults to container holding this widget.
        .fit_container()  # Scales to fit to container holding widget.
            .margin(value)  # Sets margin around bounding box.
                .fixed()  # default. fixes margin so it cannot change. Can cause parts of widget to be hidden if window is to small.
                .scaled()  # allows margin to squish if window size changes and becomes too small. cannot be below 0.
                .unit()
                    .pixels()  # default.
                    .scale()  # scaled value where 1 represents the height or width value of the relative widget.
                        .relative_to(widget_id)  # Defaults to container holding this widget.
                    .percent()  # percent value, just the scaled value * 100.
                        .relative_to(widget_id)  # Defaults to container holding this widget.
    .fixed()  # size does not change with window resizing or layout updates.
        .<size_selector>  
    .scaled()  # size does change with window resizing or layout updates.
        .<size_selector>
    .prototype(prototype_id)  # Saves a prototype of this size configuration to the root window. # Does not save relative_to information.
    .build()  # builds the size and returns to the layout manager.

## Location manager

.<method_that_called_location_manager>
    .fixed()  # location does not change with window resizing or layout updates.
        .<point_selector>  # defaults relative to root window.
    .scaled()  # location does change with window resizing or layout updates.
        .<point_selector>  # defaults relative to container holding widget.
    .distance()  # sets anchor point some unit length away from relative point of another widget.
        .<point_selector>  # relative point: defaults relative to container holding widget.
        .fixed(unit)  # Fixed unit distance. Does not change with window resizing or layout updates. Will override scaled if it's the last one set.
        .scaled(unit)  # Scaled relative to some widgets height and weight values. Will override fixed if it's the last one set.
            .relative_to(widget_id)  # defaults relative to size of relative point. But can be set to be scaled off a different widget if desired.
        .angle(degree)  # Direction from relative anchor point. 0 = right.
        .left()  # Sets angle to 180.
        .right()  # Sets angle to 0.
        .up()  # Sets angle to 90.
        .down()  # Sets angle to 270.
        .set()  # Finalizes setting, returns to current widget editor main.
    .prototype(prototype_id)  # Saves a prototype of this location configuration to the root window. # Does not save relative_to information.
    .build()  # builds the location and returns to the layout manager.


## Relativity selector

.<method_that_called_relativity_selector>
    .relative_to()
        .anchor() # Setting size of widget relative to itself will always default to this.
        .center()
        .top_left()
        .top_right()
        .bottom_left()
        .bottom_right()
        .top()
        .bottom()
        .left()
        .right()
        .point()
            .<point_selector>  # Applies to the callers relative widget only, does not allow for further recursion.

## Point selector

.<method_that_called_point_selector>  # Picks a point relative to another widget based on some unit of measurement.
    .relative_to(widget_id)  # This option is not available if called from the relativity selector, and defaults to the relative widget that selector is selecting for.
    .unit()
        .pixels()
        .scale()  # scaled value where 1 represents the height or width value of the relative widget.
        .percent()  # percent value, just the scaled value * 100.
    .X(x_unit)
        .<relativity_selector>    # defaults relative to anchor point.
    .Y(y_unit)
        .<relativity_selector>    # defaults relative to anchor point.
    .set()  # Configures point and exits selector.

## Size selector

.<method_that_called_size_selector>  # Picks a size based on unit distances away from relative anchor point.
    .relative_to(widget_id)  # defaults relative to widget calling size selector.
    .unit()
        .pixels()
        .scale()  # scaled value where 1 represents the height or width value of the relative widget.
        .percent()  # percent value, just the scaled value * 100.
    .left(x_unit)
        .<relativity_selector>  # defaults relative to anchor point.
    .right(x_unit)
        .<relativity_selector>  # defaults relative to anchor point.
    .top(y_unit)
        .<relativity_selector>  # defaults relative to anchor point.
    .bottom(y_unit)
        .<relativity_selector>  # defaults relative to anchor point.
    .set()  # Configures size and exits selector.


EXAMPLE USAGE:

ZBuild()
  .title("ZLogin App")
  .icon(":/icons/zbuild.png")
  .debug_mode(true)  // shows anchor boxes and layout hints
  .add().container("main_frame")
    .layout()
      .size()
        .scaled()
            .relative_to("root")
            .unit().pixels()
            .auto().fit_container().margin(10).scaled()
            .set()  // take full window space, with 10 pixel margin. Auto scales with window resizing.
      .location()
        .scaled()  # Using scaled allows the pixel values to change with windows resize, using fixed would keep the x, y values the same no matter the resize.
            .unit().pixels
            .X(0).relative_to().center()
            .Y(0).relative_to().center()
            .set()  // set anchor to center of main window.
      .build()

    .add.label("login_label")
      .layout()
        .location()
            .scaled()
                .unit().pixels
                .X(0).relative_to().top()
                .Y(-10).relative_to().top()  # Set 10 pixels from the top of container.
        .size()
            .scaled()
                .auto().fit_content().padding(5).scaled()
        .build()
      .text("Login")
      .font("Arial", 18, true)
      .prototype("title_label_style")  // save for reuse
      .done()

    .add.text_input("username_input")
      .layout()
        .use_prototype("align_center")  // maybe sets location to center X, Y
        .build()
      .placeholder("Username")
      .done()

  .start();  // Run the app!