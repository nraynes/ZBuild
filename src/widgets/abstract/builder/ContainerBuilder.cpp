#include <ContainerBuilder.hpp>
#include <ZBuilder.hpp>
#include <Container.hpp>
#include <QPointer>


ContainerBuilder::ContainerBuilder(std::string widget_id, std::shared_ptr<ZBuilder> zbuilder, QPointer<Container> widget) : ZInterface(zbuilder) {
    if (widget != nullptr) {
        this->widget = widget;
    } else {
        this->widget = QPointer<Container>(new Container());
    }
    this->zbuilder->register_widget(widget_id, this->widget);
}

QPointer<Container> ContainerBuilder::build() {
    return this->widget;
}
