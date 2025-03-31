#pragma once

#include <ZInterface.hpp>
#include <QPointer>
#include <string>
#include <memory>

class ZBuilder;
class Container;

class ContainerBuilder : public ZInterface {
    private:
        QPointer<Container> widget;

    public:
        ContainerBuilder(std::string widget_id, std::shared_ptr<ZBuilder> zbuilder, QPointer<Container> widget = nullptr);

        QPointer<Container> build();
};
