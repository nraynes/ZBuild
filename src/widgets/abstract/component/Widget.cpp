#include <Widget.hpp>
#include <ZInterface.hpp>
#include <ZBuilder.hpp>
#include <QPointer>
#include <string>
#include <memory>

Widget::Widget(std::string id, std::shared_ptr<ZBuilder> zbuilder, QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f), ZInterface(zbuilder) {
    this->zbuilder->register_widget(id, QPointer<Widget>(this));
}
