#ifndef VISITOR_H
#define VISITOR_H
#include <iostream>
#include "universecomponent.h"

//forward declarations of the two concrete types
class UniverseBody;
class UniverseComposite;

class Visitor
{
public:
    virtual void visit(UniverseBody& body) = 0;
    virtual void visit(UniverseComposite& composite) = 0;
};


#endif // VISITOR_H
