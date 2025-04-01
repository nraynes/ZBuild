#pragma once

#include <QWidget>
#include <QPointer>

enum class UnitType {
    PIXELS,
    PERCENT,
    SCALED
};

class Unit {
    private:
        UnitType type;
        QPointer<QWidget> relative_widget;
    
        public:
            Unit(UnitType type);

            void relative_to(QPointer<QWidget> widget);
};
