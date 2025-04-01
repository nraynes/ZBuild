#pragma once

#include <QWidget>
#include <QPointer>
#include <unordered_map>

class Container : public QWidget {
    Q_OBJECT

    public:
        Container(QPointer<Container> parent = nullptr);
};
