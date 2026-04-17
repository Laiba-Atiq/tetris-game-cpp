#include "colors.h"

colorClass::colorClass() {
    clr[0] = { 21, 36, 40, 255 };      //background colour
    clr[1] = { 255, 102, 0, 255 };    
    clr[2] = { 0, 122, 255, 255 };    
    clr[3] = { 0, 255, 255, 255 };    
    clr[4] = { 255, 234, 0, 255 };     
    clr[5] = { 0, 220, 0, 255 };       
    clr[6] = { 255, 30, 30, 255 };
    clr[7] = { 180, 0, 255, 255 };
}

Color* colorClass::getColors() {
    return clr;
}

Color colorClass::operator[](int index) const {     //
    return clr[index];
}
