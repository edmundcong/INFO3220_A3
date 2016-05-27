#ifndef VISITOR_H
#define VISITOR_H

#include "view.h"
#include "zoom.h"
#include "timestep.h"

class Visitor
{
public:
    virtual void visit(View *view_Item) = 0;
    virtual void visit(Zoom *zoom_Item) = 0;
    virtual void visit(Timestep *timestep_Item) = 0;
};

#endif // VISITOR_H
