#ifndef VISITORDISPLAY_H
#define VISITORDISPLAY_H

#include "universebody.h"
#include "universecomposite.h"

class VisitorDisplay : public Visitor
{
public:
    VisitorDisplay();

    void visit(UniverseBody & body) override;
    void visit(UniverseComposite & composite) override;
};

#endif // VISITORDISPLAY_H
