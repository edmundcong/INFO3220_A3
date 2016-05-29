#include "reset.h"

reset::reset()
{
}

void reset::visit(UniverseBody &body)
{
    std::cout << body.getPositionX() << " , " << body.getInitialPositionY() << std::endl;
    body.setPosition(body.getInitialPositionX(), body.getInitialPositionY());
    std::cout << body.getPositionX() << " , " << body.getInitialPositionY() << std::endl;
}

void reset::visit(UniverseComposite &composite)
{
    composite.setPosition(composite.getInitialPositionX(), composite.getInitialPositionY());
    //do nothing since this is not a leaf
}
