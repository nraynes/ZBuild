#pragma once

#include <Unit.hpp>
#include <QPointer>
#include <QWidget>
#include <memory>
#include <string>

class ZBuilder;

class ZInterface {
    protected:
        std::shared_ptr<ZBuilder> zbuilder;
        std::unique_ptr<Unit> unit;

    public:
        ZInterface(std::shared_ptr<ZBuilder> zbuilder);

        QPointer<QWidget> widget(std::string widget_id);

        void set_unit(std::unique_ptr<Unit> unit);

        int run();
};
