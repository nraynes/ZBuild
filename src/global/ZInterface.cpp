#include <ZInterface.hpp>
#include <ZBuilder.hpp>
#include <QPointer>
#include <QWidget>
#include <memory>

ZInterface::ZInterface(std::shared_ptr<ZBuilder> zbuilder) : zbuilder(zbuilder) {}

QPointer<QWidget> ZInterface::widget(std::string widget_id) {
    return this->zbuilder->widget(widget_id);
}

int ZInterface::run() {
    return this->zbuilder->run();
}