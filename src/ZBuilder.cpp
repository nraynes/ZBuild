#include <ZBuilder.hpp>
#include <QWidget>
#include <QPointer>
#include <memory>

ZBuilder::ZBuilder(int& argc, char** argv) : app(std::make_unique<QApplication>(argc, argv)), id("root") {}

void ZBuilder::register_widget(std::string widget_id, QPointer<QWidget> widget) {
    this->widgets[widget_id] = widget;
}

QPointer<QWidget> ZBuilder::widget(std::string widget_id) {
    if (this->widgets.find(widget_id) != this->widgets.end()) {
        return this->widgets[widget_id];
    } else {
        return nullptr;
    }
}

int ZBuilder::run() {
    return this->app->exec();
}
