#pragma once

#include <ZInterface.hpp>
#include <QPointer>
#include <string>
#include <memory>

class ZBuilder;
class Widget;

class WidgetBuilder : public ZInterface {
    private:
        QPointer<Widget> widget;

    public:
        WidgetBuilder(std::string widget_id, std::shared_ptr<ZBuilder> zbuilder, QPointer<Widget> widget = nullptr);

        QPointer<Widget> build();
};
