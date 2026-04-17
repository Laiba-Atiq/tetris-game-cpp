#pragma once
#include "tetrimino.h"

class LShape : public tetrimino {
public:
    LShape(int n = 1);
};

class JShape : public tetrimino {
public:
    JShape(int n = 2);
};

class IShape : public tetrimino {
public:
    IShape(int n = 3);
};

class OShape : public tetrimino {
public:
    OShape(int n = 4);
    void rotate();
};

class SShape : public tetrimino {
public:
    SShape(int n = 5);
};

class ZShape : public tetrimino {
public:
    ZShape(int n = 6);
};

class TShape : public tetrimino {
public:
    TShape(int n = 7);
};
