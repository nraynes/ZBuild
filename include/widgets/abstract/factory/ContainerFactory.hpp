#pragma once

#include <ZInterface.hpp>
#include <string>

class ContainerBuilder;
class Container;
class ZBuilder;

class ContainerFactory : public ZInterface {
    private:
        std::shared_ptr<Container> parent;
        
    public:
        ContainerFactory(std::shared_ptr<ZBuilder> zbuilder, std::shared_ptr<Container> parent);
        ContainerBuilder make(std::string widget_id);
};
