#pragma once

#include <QPointer>
#include <QApplication>
#include <QWidget>
#include <string>
#include <unordered_map>
#include <memory>

class ZBuilder {
    private:
        std::string id;
        std::unordered_map<std::string, int> widget_prototypes;
        std::unordered_map<std::string, int> layout_prototypes;
        std::unordered_map<std::string, int> location_prototypes;
        std::unordered_map<std::string, int> size_prototypes;
        std::unordered_map<std::string, int> theme_prototypes;
        std::unordered_map<std::string, int> animation_prototypes;
        std::unordered_map<std::string, QPointer<QWidget>> widgets;
        std::unique_ptr<QApplication> app;

    public:
        ZBuilder(int& argc, char** argv);
        void register_widget(std::string widget_id, QPointer<QWidget> widget);
        QPointer<QWidget> widget(std::string widget_id);
        int run();
};
