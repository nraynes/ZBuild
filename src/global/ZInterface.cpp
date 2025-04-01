#include <ZInterface.hpp>
#include <ZBuilder.hpp>
#include <Unit.hpp>
#include <QPointer>
#include <QWidget>
#include <memory>

ZInterface::ZInterface(std::shared_ptr<ZBuilder> zbuilder) : zbuilder(zbuilder), unit(std::make_unique<Unit>(UnitType::PIXELS)) {}

QPointer<QWidget> ZInterface::widget(std::string widget_id) {
    return this->zbuilder->widget(widget_id);
}

void ZInterface::set_unit(std::unique_ptr<Unit> unit) {
    this->unit = std::move(unit);
}

int ZInterface::run() {
    return this->zbuilder->run();
}