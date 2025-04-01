#pragma once

#include <memory>

class ZInterface;

class UnitSelector {
    private:
        ZInterface* parent;

    public:
        UnitSelector(ZInterface* parent);
        void pixels();
        void percent();
        void scaled();
};
