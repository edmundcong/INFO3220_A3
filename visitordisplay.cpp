#include "visitordisplay.h"

VisitorDisplay::VisitorDisplay()
{
//  m_planetaryInfo = new QLabel("Test label",);
//  m_planetaryInfo->setGeometry(QRect(QPoint(600, 0), QSize(100, 50)));

  std::cout << "Test" << std::endl;
}

void VisitorDisplay::visit(UniverseBody &body)
{
    std::string parent_type = "";

    if (body.getType() == 0 || body.getType() == 1)
    {
        parent_type = "solarsystem";
    }
    else if (body.getType() == 2 || body.getType() == 3)
    {
        parent_type = "galaxy";
    }
    else if(body.getType() == 4)
    {
        parent_type = "cluster";
    }

    std::cout << body.getName() << " is a child of the " << body.getParentName() << " " << parent_type <<  std::endl;
    std::cout << "X: " << body.getPositionX() << " Y: " << body.getPositionY() << std::endl;

}

void VisitorDisplay::visit(UniverseComposite &planetaryBodies)
{
    for(UniverseComponent* child : planetaryBodies.getChildren())
    {
        child->accept(*this);
    }
}
