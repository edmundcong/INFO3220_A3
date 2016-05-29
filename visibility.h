#ifndef VISIBILITY_H
#define VISIBILITY_H

#include "universebody.h"
#include "universecomposite.h"

class visibility : public Visitor
{
public:
    visibility();

    void visit(UniverseBody &body) override;
    void visit(UniverseComposite& composite) override;
};

#endif // VISIBILITY_H
