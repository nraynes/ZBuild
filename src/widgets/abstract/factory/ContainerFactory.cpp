#include <ContainerFactory.hpp>
#include <ContainerBuilder.hpp>
#include <ZInterface.hpp>
#include <Container.hpp>
#include <string>

ContainerFactory::ContainerFactory(std::shared_ptr<ZBuilder> zbuilder, std::shared_ptr<Container> parent) : ZInterface(zbuilder), parent(parent) {}

ContainerBuilder ContainerFactory::make(std::string widget_id) {
    return ContainerBuilder(widget_id, this->zbuilder);
}
