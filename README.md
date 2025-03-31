# ZBuild

ZBuild is a wrapper for Qt, and is designed to make UI development simple and easy while keeping access to all the advanced features of Qt allowing you to make high quality native looking applications in code with as low as just 1 line of code.

# Building Package

This project was developed on MAC. If you're a windows user, sorry, you'll have to wait until I get around to updating the readme to include setup instructions for Windows.
Follow the steps below to build the package manually, or, you can use the cmake script provided to build it.

## Step 1: Configure and build
```
cd <path_to_project>
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Step 2: Install (system-wide or locally)
```
cmake -B build -DCMAKE_INSTALL_PREFIX=./zbuild-install
cmake --build build
sudo cmake --install build
```

## Package
```
cd zbuild-install
sudo tar -czf zbuild-0.1.0.tar.gz *
```

# Installing Package

This step will install the project to your machine for use as a dependency in other projects. There is also a cmake script toi automate this if needed. Package must be built first in order to run the install script.

## Step 1: Install and setup ZBuild

Install ZBuild by downloading the tar.gz file or creating it locally via the previous section.

- Move tar to home folder.
```
mkdir $HOME/ZBuild
mv zbuild-0.1.0.tar.gz $HOME/ZBuild
cd $HOME/ZBuild
```

- Command to extract tar.gz.  
```
tar -xzf zbuild-0.1.0.tar.gz
```

- (Optionally) Delete tar.gz.
```
rm zbuild-0.1.0.tar.gz
```

## Step 2: Install and setup Qt

Install Qt by downloading the tar.gz file from the official [website](https://www.qt.io/offline-installers).
The latest version ZBuild uses is 6.8.3.

- Extract the tar.xz file (replace with name of file you downloaded).  
```
cd <path_to_where_qt_tar.xz_downloaded>
tar -xf qt-everywhere-src-6.8.3.tar.xz
```

- Configure Qt (This will take a while, be prepared to wait for like 30 minutes).
```
cd qt-everywhere-src-6.8.3
./configure -prefix $HOME/Qt6
cmake --build .
```

## Step 3: Include in CMakeLists.txt

```
find_package(ZBuild REQUIRED)

target_link_libraries(<app_name> PRIVATE ZBuild::ZBuild)
```

## Step 4: Build project.

Build with the commands below or use cmake in vscode. Kit configuration available below.
```
cmake -B build
cmake --build build
```

## Step 5: Set up CMake Kit (If Using VS Code)

- Ensure that extensions "Cmake Tools" from Microsoft and "Cmake" from twxs are installed in VSCode.

- Create a .vscode folder in your project (If you haven't already), then create a file called cmake-kits.json.
```
cd <path_to_project>
mkdir .vscode
touch .vscode/cmake-kits.json
open .vscode/cmake-kits.json
```

- Paste this into the cmake-kits.json file and save it. Make sure that you use that actual path name and not $HOME here.
```
[
    {
        "name": "Qt6 with Ninja",
        "compilers": {
            "CXX": "/usr/bin/clang++",
            "C": "/usr/bin/clang"
        },
        "environmentVariables": {
            "CMAKE_PREFIX_PATH": "<$HOME_path>/ZBuild;<$HOME_path>/Qt6"
        },
        "toolchainFile": "",
        "preferredGenerator": {
            "name": "Ninja"
        }
    },
    {
        "name": "Qt6 with Ninja + Auto Package",
        "compilers": {
            "CXX": "/usr/bin/clang++",
            "C": "/usr/bin/clang"
        },
        "environmentVariables": {
            "CMAKE_PREFIX_PATH": "<$HOME_path>/ZBuild;<$HOME_path>/Qt6",
            "CMAKE_BUILD_TYPE": "Release",
            "ZBUILD_AUTO_PACKAGE": "ON"
        },
        "toolchainFile": "",
        "preferredGenerator": {
            "name": "Ninja"
        }
    },
    {
        "name": "Qt6 with Ninja + Auto Package & Install",
        "compilers": {
            "CXX": "/usr/bin/clang++",
            "C": "/usr/bin/clang"
        },
        "environmentVariables": {
            "CMAKE_PREFIX_PATH": "<$HOME_path>/ZBuild;<$HOME_path>/Qt6",
            "CMAKE_BUILD_TYPE": "Release",
            "ZBUILD_AUTO_PACKAGE": "ON",
            "ZBUILD_AUTO_INSTALL": "ON"
        },
        "toolchainFile": "",
        "preferredGenerator": {
            "name": "Ninja"
        }
    }
]
```

- Next, hit "Cmd + Shift + P" and choose "CMake: Configure", then choose the kit "Qt6 with Ninja".
- If you already configured the project, the choose "CMake: Select a Kit" instead.
- If you are just developing in the ZBuild project and not installing it to another project, don't include the ZBuild path in CMAKE_PREFIX_PATH for the kit. However, if you are using ZBuild as a dependency in another project, you'll have to install it to your machine via the instructions above and make sure to use the CMAKE_PREFIX_PATH from the kits above. Alternatively, change the path names to a custom location if you installed ZBuild or Qt to a custom location on your machine. Both ZBuild and Qt must be installed separately.
- The first kit is the only kit needed if installing the project as a dependency. The other 2 kits are for automatic building and installing if you are developing in ZBuild.
- These different kits give the option to automatically package and/or install the release version of the project.

# Development Settings

The following are my developer settings that I prefer for VSCode. These go in the .vscode folder in a settings.json file.

```
{
  "cmake.sourceDirectory": "${workspaceFolder}",
  "cmake.cmakePath": "/opt/homebrew/bin/cmake",
  "cmake.generator": "Ninja",
  "cmake.buildDirectory": "${workspaceFolder}/build",
  "cmake.configureOnOpen": true,
  "C_Cpp.default.compileCommands": "${workspaceFolder}/build/compile_commands.json",
  "files.associations": {
      "vector": "cpp",
      "__bit_reference": "cpp",
      "__split_buffer": "cpp",
      "cstddef": "cpp",
      "cstdint": "cpp",
      "cstdlib": "cpp",
      "cstring": "cpp",
      "initializer_list": "cpp",
      "iosfwd": "cpp",
      "istream": "cpp",
      "limits": "cpp",
      "locale": "cpp",
      "new": "cpp",
      "ostream": "cpp",
      "sstream": "cpp",
      "stdexcept": "cpp",
      "string": "cpp",
      "tuple": "cpp",
      "typeinfo": "cpp",
      "__hash_table": "cpp",
      "__locale": "cpp",
      "__node_handle": "cpp",
      "__threading_support": "cpp",
      "__tree": "cpp",
      "__verbose_abort": "cpp",
      "array": "cpp",
      "bitset": "cpp",
      "cctype": "cpp",
      "clocale": "cpp",
      "cmath": "cpp",
      "complex": "cpp",
      "cstdarg": "cpp",
      "cstdio": "cpp",
      "ctime": "cpp",
      "cwchar": "cpp",
      "cwctype": "cpp",
      "deque": "cpp",
      "execution": "cpp",
      "memory": "cpp",
      "fstream": "cpp",
      "iomanip": "cpp",
      "ios": "cpp",
      "iostream": "cpp",
      "list": "cpp",
      "map": "cpp",
      "mutex": "cpp",
      "optional": "cpp",
      "print": "cpp",
      "queue": "cpp",
      "ratio": "cpp",
      "stack": "cpp",
      "streambuf": "cpp",
      "string_view": "cpp",
      "unordered_map": "cpp",
      "valarray": "cpp",
      "variant": "cpp",
      "algorithm": "cpp",
      "random": "cpp"
  }
}
```

# Widget Factory

A **factory** (uses factory design pattern) provides the interface for acquiring the builder for each type of widget.

# Widgets

There are 3 different basic types of widgets.
- **Display Widgets**: Widgets that display things.
- **Control Widgets**: Widgets that control things.
- **Container Widgets**: Widgets that contain other widgets.

Each widget has some kind of *internal content*. This content can be text, an image, or even other widgets.

The container widget is the only widget that can contain multiple other widgets as internal content.

Widgets follow the **composite** design pattern, where container widgets are composites and both control and display widgets are leaves. This allows for a simple hierarchical widget structure and easy custom layouts.

Widgets implement the **state** design pattern for their event handling. This allows the behavior defined by the event to be implemented separate from the widgets.

Widgets themselves are built via a **builder** design pattern. This separates each widget configuration setting, layout configuration, and theme configuration from the widget itself and provides a neat interface for setting them. Each widget has an ID that must be set to allow searching via hashmap in the main application.

### Events

Events are specific actions or states that a widget is in when something happens. For example, a widget can be clicked and will then be in the "clicked" state, which is handled via the .on_click() event. These events can be bound to methods or functions in order to create custom logic for your application. Every event bound method will be supplied with 1 argument, and thats a pointer to the main application. This gives each event bound method access to values from other widgets internal states, or the ability to alter the UI based on some custom logic.

#### Event Modifiers

Event modifiers allow you to delay an event bound method from executing for a certain amount of time after a relative point in time. This relative point could be when an event starts, or when an event finishes. The 2 core event modifiers available are:

<no_modifier> = When no modifier is selected, the event bound method runs immediately when the event happens.  
.finished() = Runs the event bound method when the event is finished.  
.after(ms) = Runs the event bound method after a certain amount of milliseconds from when the event starts. This can be placed after *.finished()* to run the event bound method a certain amount fo milliseconds from when the event finishes.  

### Qt Wrapper

There is an **adapter** (uses adapter design pattern) that adapts the format of inputs from ZBuild to Qt, separating the implementation of ZBuild from Qt. This allows for any GUI library to be used instead of Qt as long as it supports similar features.

# ZBuilder

Finally, the ZBuilder is the main application that also follows the **builder** design pattern and allows you to build the entire GUI, with the root functioning as a Container widget, allowing you to set the layout. You can chain commands to create new widgets, configure them, and access the whole gui container and all contained widgets for reference. You can set the active widget being modified with a specific command from the builder as well to go back and configure previously created widgets.

This allows you to functionally create a gui in one line of code.

## Prototypes

You can create **prototypes** of widgets, layouts, or layout components like size, location, or theme to reuse throughout the application. These get saved to the ZBuilder as pointers in a hashmap so they can be retreived easily.

You will also be able to build individual widgets or layouts and store them in separate files if necessary via the widget factory. You can add these widgets or layouts to the ZBuilder (or another component builder) via the .use_prototype(prototype_id), but this can all be done in the main builder as well since it will store pointers to the prototypes.

# Builder Reference
```
ZBuilder(**root_params)  # create a new gui builder and sets the root as the active widget.
```

NOTE: The ZBuilder has properties that save specific information about the application such as storing:  
    - hashmap of widget prototypes. (May come with a few defaults, like multiple widgets in a container set as a template.)  
    - hashmap of layout prototypes. (May come with some default layouts.)  
    - hashmap of location prototypes. (May come with a few defaults, like "align_center", "align_left", etc.)  
    - hashmap of size prototypes. (May come with a few defaults, like "stretch", "fixed", etc.)  
    - hashmap of theme prototypes. (May come with a few defaults.) 
    - hashmap of animation prototypes. (May come with a few defaults.) 
    - hashmap of widget pointers by id (for easy retrieval).  
    - ID of root window, "root".  
    - Window title.  
    - Window icon.  
    - Debug mode. (Shows bounding boxes and anchor points for debugging.)  
    - etc.  
```
.run()  # Starts the application, no need to change the active widget if it precedes this, since this will exit the builder anyways.

.widget(widget_id)  # Returns a pointer to a specific widget from root via hashmap lookup. This allows you to change what widget is being built mid chain.  
    .<widget_editor>
```

## Container Widget Builder
```
.<method_that_called_container>(widget_id)
    .<widget_editor>  # Edits the container widget.  
    .get(widget_id)  # Gets a widget within this container specifically.  
        .<widget_editor>  
    .add()  
        .use_prototype(prototype_id, widget)  # Instantiate a prototyped widget, or load a widget from separate file.  
            .<widget_editor>  
        .<widget_type>(widget_id)  
            .<widget_editor>  
    .delete(widget_id)  
```

## Widget Builder
```
.<method_that_called_widget>(widget_id)  
    .theme()
        .<theme_builder>
    .layout()  
        .<layout_builder>  
    .animation()
        .add(animation_id)
            .<animation_builder>
        .remove(animation_id)  # Removes animation.
        .start(animation_id)  # Start Animation.
    .<event_type>  # May or may not have event param.  
        .after(milliseconds)  # Can specify time in ms to run bound method after event starts.  
        .finished()  # Specifes to run bound method after event finishes.  
            .after(milliseconds)  # Can specify time in ms to run bound method after event finishes.  
        .<modifier>(modifier_params)  # Specific events may have additional modifiers.  
        .bind(method)  # Method recieves a pointer to the root window which contains the entire app. This also exits the event editor. Bound method defaults to running right when event starts unless modifers are present.  
        .animate(animation_id)  # Bind an animation to this event. Animation will start when event conditions trigger.
    .<configuration>(configuration_params)  # Specific widgets may have additional configuration options.  
    .prototype(prototype_id)  # Creates a prototype of this widget that can be instantiated multiple times. Saves to root window.  
    .done()  # Exits widget editor. Returns to the container hosting this widget.  
    .build()  # Returns a fully built widget to use outside of the main builder.  
```

## Layout Builder
```
.<method_that_called_layout_builder>  
    .size()  
        .<size_builder>  
    .location()  
        .<location_builder>  
    .prototype(prototype_id)  # Creates a prototype of this layout that can be reused by multiple widgets. Saves to root window. Does not save relative_to information.  
    .use_prototype(prototype_id, layout)
    .build()  # Finalizes the layout and returns to the widget editor that called the manager.  
```

### Size Builder
```
.<method_that_called_size_builder>  
    .auto()  # scales automatically to fit.  
        .fit_content() # Scales to fit inner content. (Ex: text, other widgets inside container, etc.)  
            .padding(value)  # Sets padding around inner content.  
                .fixed()  # default. fixes padding so it cannot change. Can cause parts of widget to be hidden if window is to small.  
                .scaled()  # allows padding to squish if window size changes and becomes too small. cannot be below 0.  
                .<unit_selector> 
        .fit_container()  # Scales to fit to container holding widget.  
            .margin(value)  # Sets margin around bounding box.  
                .fixed()  # default. fixes margin so it cannot change. Can cause parts of widget to be hidden if window is to small.  
                .scaled()  # allows margin to squish if window size changes and becomes too small. cannot be below 0.  
                .<unit_selector>
    .fixed()  # size does not change with window resizing or layout updates.  
        .<size_selector>   
    .scaled()  # size does change with window resizing or layout updates.  
        .<size_selector>  
    .prototype(prototype_id)  # Saves a prototype of this size configuration to the root window. # Does not save relative_to information.  
    .use_prototype(prototype_id, size)
    .build()  # builds the size and returns to the layout manager.  
```

### Location Builder
```
.<method_that_called_location_builder>  
    .Z(index)  # Set the z index for the widget. Controls overlapping.
    .fixed()  # location does not change with window resizing or layout updates.  
        .<point_selector>  # defaults relative to root window.  
    .scaled()  # location does change with window resizing or layout updates.  
        .<point_selector>  # defaults relative to container holding widget.  
    .distance()  # sets anchor point some unit length away from relative point of another widget.  
        .<point_selector>  # relative point: defaults relative to container holding widget.  
        .fixed(value)  # Fixed unit distance. Does not change with window resizing or layout updates. Will override scaled if it's the last one set.  
            .<unit_selector>
        .scaled(value)  # Scaled relative to some widgets height and weight values. Will override fixed if it's the last one set.  
            .<unit_selector>
        .angle(degree)  # Direction from relative anchor point. 0 = right.  
        .left()  # Sets angle to 180.  
        .right()  # Sets angle to 0.  
        .up()  # Sets angle to 90.  
        .down()  # Sets angle to 270.  
        .set()  # Finalizes setting, returns to current widget editor main.  
    .prototype(prototype_id)  # Saves a prototype of this location configuration to the root window. # Does not save relative_to information.  
    .use_prototype(prototype_id, location)
    .build()  # builds the location and returns to the layout manager.  
```

### Unit Selector
```
.<method_that_called_unit_selector>
    .unit()  
        .pixels()  # default.  
        .scale()  # scaled value where 1 represents the height or width value of the relative widget.  
            .relative_to(widget_id)  # Defaults to container holding this widget.  
        .percent()  # percent value, just the scaled value * 100.  
            .relative_to(widget_id)  # Defaults to container holding this widget.
```

### Relativity Selector
```
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
```

### Point Selector
```
.<method_that_called_point_selector>  # Picks a point relative to another widget based on some unit of measurement.  
    .relative_to(widget_id)  # This option is not available if called from the relativity selector, and defaults to the relative widget that selector is selecting for.  
    .X(x_unit)  
        .<unit_selector>
        .<relativity_selector>    # defaults relative to anchor point.  
    .Y(y_unit)  
        .<unit_selector>
        .<relativity_selector>    # defaults relative to anchor point.  
    .set()  # Configures point and exits selector.  
```

### Size Selector
```
.<method_that_called_size_selector>  # Picks a size based on unit distances away from relative anchor point.  
    .relative_to(widget_id)  # defaults relative to widget calling size selector.  
    .left(x_unit)  
        .<unit_selector>
        .<relativity_selector>  # defaults relative to anchor point.  
    .right(x_unit)  
        .<unit_selector>
        .<relativity_selector>  # defaults relative to anchor point.  
    .top(y_unit)  
        .<unit_selector>
        .<relativity_selector>  # defaults relative to anchor point.  
    .bottom(y_unit)  
        .<unit_selector>
        .<relativity_selector>  # defaults relative to anchor point.  
    .set()  # Configures size and exits selector.  
```

## Theme Builder
```
.<method_that_called_theme_builder>  
    .use_preset(theme)  # Uses Qt Preset theme.
    .use_prototype(prototype_id)
    .prototype(prototype_id)
    .color(red, green, blue, opacity)
    .border()
        .color(red, green, blue, opacity)
        .thickness(value)
            .<unit_selector>
        .radius(value)  # For creating rounded corners or circles
            .<unit_selector>
    .shadow()
        .offset_x(value)
            .<unit_selector>
        .offset_x(value)
            .<unit_selector>
        .blur_radius(value)
            .<unit_selector>
        .spread(value)
            .<unit_selector>
        .color(red, green, blue, opacity)
        .remove()  # Removes shadow.
    .content()  # Applies to internal content.
        .<type_specific_customization>  # Different types of internal content have different types of theme options (EX: Font).
```

## Animation Builder
```
.<method_that_called_animation_builder>
    .prototype(prototype_id)
    .use_prototype(prototype_id, animation)
    .add_frame()  # Add a frame to specify what state the widget should be in at moment in time.
        .<frame_builder>
```

### Frame Builder
```
.<method_that_called_frame_Builder>
    .index(value)  # Index values specify the order to play frames in.
    .when(ms)  # Specifies when the widget should be in this state.
    .ease(ease_type)  # Specifies how the transition should ease into the next frame.
    .theme()
        .<theme_builder>
    .layout()  
        .<layout_builder>  
```

# EXAMPLE USAGE

**Example 1**
```
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
```

**Example 2**
```
ZBuild()
  .title("Settings")
  .icon(":/icons/settings.png")
  .debug_mode(false)

  .add().container("settings_container")
    .layout()
      .size().scaled().auto().fit_container().margin(10).scaled().build()
      .location().scaled().unit().pixels()
          .X(0).relative_to().center()
          .Y(0).relative_to().center()
          .set()
      .build()

    .add.label("settings_title")
      .layout()
        .location().scaled().X(0).relative_to().top().Y(-10).relative_to().top().set()
        .size().scaled().auto().fit_content().padding(5).scaled().build()
      .text("Application Settings")
      .font("Arial", 16, true)
      .prototype("title_label_style")
      .done()

    .add.toggle("dark_mode_toggle")
      .layout().use_prototype("align_center").build()
      .label("Dark Mode")
      .checked(false)
      .on_toggle().bind([](auto root) {
        auto isDark = root->widget("dark_mode_toggle")->get("checked");
        // Update theme or persist setting
      })
      .done()

    .add.button("save_button")
      .layout().use_prototype("align_center").build()
      .text("Save Settings")
      .on_click().bind([](auto root) {
        // Save all settings
      })
      .done()

    .done()

  .start();
```

**Example 3**
```
ZBuild()
  .title("Dashboard")
  .icon(":/icons/dashboard.png")
  .debug_mode(true)

  .add().container("main")
    .layout().size().scaled().auto().fit_container().margin(15).scaled().build()
            .location().scaled().X(0).relative_to().center().Y(0).relative_to().center().set()
    .build()

    .add.label("welcome")
      .text("Welcome, User")
      .layout().use_prototype("align_top").build()
      .font("Segoe UI", 14, true)
      .done()

    .add.chart("usage_chart")  // Assuming a custom widget and builder were created
      .layout().use_prototype("align_center").build()
      .data_source("resource_usage")
      .refresh_interval(5000)
      .done()

    .add.button("refresh")
      .text("Refresh Now")
      .on_click().bind([](auto root) {
        root->widget("usage_chart")->invoke("refresh");
      })
      .done()

    .done()

  .start();
```
