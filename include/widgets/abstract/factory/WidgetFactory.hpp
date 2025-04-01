#pragma once

#include <ZInterface.hpp>
#include <string>

class WidgetBuilder;
class Container;
class ZBuilder;

class WidgetFactory : public ZInterface {
    private:
        std::shared_ptr<Container> parent;
        
    public:
        WidgetFactory(std::shared_ptr<ZBuilder> zbuilder, std::shared_ptr<Container> parent);
        WidgetBuilder make(std::string widget_id);
};
