//Inherits grid class
//child classes/sub classes for drawing grids for various variable KMAP solver
//Draw fxn is different for different variable KMAPs

#pragma once
#include "grid.h"

class twoVar : public Grid
{
public:
    twoVar();
    void Draw();
};

class threeVar : public Grid
{
public:
    threeVar();
    void Draw();
};

class fourVar : public Grid
{
public:
    fourVar();
    void Draw();
};

class fiveVar : public Grid
{
public:
    fiveVar();
    void Draw();
};