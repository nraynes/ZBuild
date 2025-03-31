#pragma once

#include <ZBuilder.hpp>
#include <ZInterface.hpp>
#include <QWidget>
#include <string>
#include <memory>

class Widget : public QWidget, public ZInterface {
    Q_OBJECT
    
    public:
        Widget(std::string id, std::shared_ptr<ZBuilder> zbuilder, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};
