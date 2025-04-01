#include <Unit.hpp>
#include <QWidget>
#include <QPointer>

Unit::Unit(UnitType type) : type(type) {}

void Unit::relative_to(QPointer<QWidget> widget) {
    this->relative_widget = widget;
}
