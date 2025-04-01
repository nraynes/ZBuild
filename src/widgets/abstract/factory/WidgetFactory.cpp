#include <WidgetFactory.hpp>
#include <WidgetBuilder.hpp>
#include <ZInterface.hpp>
#include <Container.hpp>
#include <string>

WidgetFactory::WidgetFactory(std::shared_ptr<ZBuilder> zbuilder, std::shared_ptr<Container> parent) : ZInterface(zbuilder), parent(parent) {}

WidgetBuilder WidgetFactory::make(std::string widget_id) {
    return WidgetBuilder(widget_id, this->zbuilder);
}
