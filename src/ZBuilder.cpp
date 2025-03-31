#include <ZBuilder.hpp>
#include <memory>

ZBuilder::ZBuilder(int& argc, char** argv) : app(std::make_unique<QApplication>(argc, argv)), id("root") {}

int ZBuilder::run() {
    return this->app->exec();
}
