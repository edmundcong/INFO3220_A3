#include "fetchfurthestbodies.h"

fetchFurthestBodies::fetchFurthestBodies()
{
    m_sx = 0;
    m_sy = 0;

    m_x1 = 0; //left
    m_x2 = 0; //right
    m_y1 = 0; //top
    m_y2 = 0; //bot
}

void fetchFurthestBodies::visit(UniverseBody &body)
{
    if (body.getPositionX() < m_x1)
    {
        m_x1 = body.getPositionX();
    }
    else if (body.getPositionX() > m_x2)
    {
        m_x2 = body.getPositionX();
    }

    if (body.getPositionY() < m_y2)
    {
        m_y2 = body.getPositionY();
    }
    else if (body.getPositionY() > m_y1)
    {
        m_y1 = body.getPositionY();
    }
}


void fetchFurthestBodies::visit(UniverseComposite &composite)
{
    //do nothing since no bodies
}

void fetchFurthestBodies::convertCoordinates()
{
    Config* config = Config::getInstance();

    m_x1 = m_x1 / config->getDistanceScale();
    m_x2 = m_x2 / config->getDistanceScale();
    m_y1 = m_y1 / config->getDistanceScale();
    m_y2 = m_y2 / config->getDistanceScale();

    m_sx = -(m_x2/m_x1);
    m_sy = -(m_y1/m_y2);
}
