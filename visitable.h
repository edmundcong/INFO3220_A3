#ifndef VISITABLE_H
#define VISITABLE_H

#include "visitor.h"

class Visitable
{
    virtual void accept(Visitor visitor) = 0;
};

#endif // VISITABLE_H
