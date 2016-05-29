#ifndef FETCHFURTHESTBODIES_H
#define FETCHFURTHESTBODIES_H

#include "universebody.h"
#include "universecomponent.h"
#include "config.h"

class fetchFurthestBodies : public Visitor
{
public:
    fetchFurthestBodies();

    void visit(UniverseBody &body) override;
    void visit(UniverseComposite &composite) override;

    void convertCoordinates();

    double m_x1;
    double m_x2;
    double m_y1;
    double m_y2;

    double m_sx;
    double m_sy;

};

#endif // FETCHFURTHESTBODIES_H
