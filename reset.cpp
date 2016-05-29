#include "reset.h"

reset::reset()
{
}

void reset::visit(UniverseBody &body)
{
    body.setPosition(body.getInitialPositionX(), body.getInitialPositionY());
}

void reset::visit(UniverseComposite &composite)
{
    composite.setPosition(composite.getInitialPositionX(), composite.getInitialPositionY());
}
