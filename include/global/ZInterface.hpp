#pragma once

#include <QPointer>
#include <QWidget>
#include <memory>
#include <string>

class ZBuilder;

class ZInterface {
    protected:
        std::shared_ptr<ZBuilder> zbuilder;

    public:
        ZInterface(std::shared_ptr<ZBuilder> zbuilder);

        QPointer<QWidget> widget(std::string widget_id);

        int run();
};
