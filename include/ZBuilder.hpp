#pragma once

#include <string>
#include <unordered_map>
#include <QApplication>
#include <memory>
#include <GlobalCommand.hpp>

class ZBuilder {
    private:
        std::string id;
        std::unordered_map<char, int> widget_prototypes;
        std::unordered_map<char, int> layout_prototypes;
        std::unordered_map<char, int> location_prototypes;
        std::unordered_map<char, int> size_prototypes;
        std::unordered_map<char, int> theme_prototypes;
        std::unordered_map<char, int> animation_prototypes;
        std::unordered_map<char, int> widgets;
        std::unique_ptr<QApplication> app;

    public:
        ZBuilder(int& argc, char** argv);
        int run();
};
