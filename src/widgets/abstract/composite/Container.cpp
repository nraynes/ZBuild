#include <Container.hpp>
#include <QPointer>

Container::Container(QPointer<Container> parent) : QWidget(parent) {}
