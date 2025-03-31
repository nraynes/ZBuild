#include <ZBuilder.hpp>
#include <Widget.hpp>
#include <QPointer>
#include <memory>

ZBuilder::ZBuilder(int& argc, char** argv) : app(std::make_unique<QApplication>(argc, argv)), id("root") {}

void ZBuilder::register_widget(std::string widget_id, QPointer<Widget> widget) {
    this->widgets[widget_id] = widget;
}

QPointer<Widget> ZBuilder::widget(std::string widget_id) {
    if (this->widgets.find(widget_id) != this->widgets.end()) {
        return this->widgets[widget_id];
    } else {
        return nullptr;
    }
}

int ZBuilder::run() {
    return this->app->exec();
}
