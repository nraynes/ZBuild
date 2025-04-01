#pragma once

#include <QWidget>
#include <QPointer>

class Container;

class Widget : public QWidget {
    Q_OBJECT
    
    public:
        Widget(QPointer<Container> parent = nullptr);
};
