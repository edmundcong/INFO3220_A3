#include "visibility.h"

visibility::visibility()
{

}

void visibility::visit(UniverseBody &body)
{
    if (body.getType() == 0)
    {
        QColor temp = body.getColor();
        body.setColor(body.getAltColour());
        body.setAltColour(temp);
    }
}

void visibility::visit(UniverseComposite &composite)
{
    //do nothing since this is not a leaf
}
