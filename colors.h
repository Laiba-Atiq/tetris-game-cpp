#pragma once
#include <raylib.h>

class colorClass {
private:
    Color clr[8];

public:
    colorClass();
    Color* getColors();
    Color operator[](int index) const;
};
