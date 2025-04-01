#include <Widget.hpp>
#include <Container.hpp>
#include <QPointer>

Widget::Widget(QPointer<Container> parent) : QWidget(parent) {}
