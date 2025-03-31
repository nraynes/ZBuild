#pragma once

#include <QPointer>
#include <memory>
#include <string>

class ZBuilder;
class Widget;

class ZInterface {
    protected:
        std::shared_ptr<ZBuilder> zbuilder;

    public:
        ZInterface(std::shared_ptr<ZBuilder> zbuilder);

        QPointer<Widget> widget(std::string widget_id);

        int run();
};
