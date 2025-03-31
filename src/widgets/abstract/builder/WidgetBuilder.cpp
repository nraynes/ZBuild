#include <WidgetBuilder.hpp>
#include <ZBuilder.hpp>
#include <Widget.hpp>
#include <QPointer>


WidgetBuilder::WidgetBuilder(std::string widget_id, std::shared_ptr<ZBuilder> zbuilder, QPointer<Widget> widget) : ZInterface(zbuilder) {
    if (widget != nullptr) {
        this->widget = widget;
    } else {
        this->widget = QPointer<Widget>(new Widget());
    }
    this->zbuilder->register_widget(widget_id, this->widget);
}

QPointer<Widget> WidgetBuilder::build() {
    return this->widget;
}
