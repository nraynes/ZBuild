#pragma once

#include <ZInterface.hpp>
#include <QPointer>
#include <string>
#include <memory>

class ZBuilder;
class Widget;
class Container;

class WidgetBuilder : public ZInterface {
    private:
        QPointer<Widget> widget;

    public:
        WidgetBuilder(std::string widget_id, std::shared_ptr<ZBuilder> zbuilder, QPointer<Container> parent = nullptr, QPointer<Widget> widget = nullptr);

        QPointer<Widget> build();
};
