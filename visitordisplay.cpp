#include "visitordisplay.h"

VisitorDisplay::VisitorDisplay()
{

}

void VisitorDisplay::visit(UniverseBody &body)
{
    std::cout << body.getName() << std::endl;
    std::cout << body.getPositionX() << std::endl;
    std::cout << body.getPositionY() << std::endl;
}

void VisitorDisplay::visit(UniverseComposite &composite)
{
    std::vector<UniverseComponent*> children = composite.getChildren();

    for(UniverseComponent* child : children)
    {
        child->accept(*this);
    }
}
