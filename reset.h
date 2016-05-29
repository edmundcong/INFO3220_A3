#ifndef RESET_H
#define RESET_H

#include "universebody.h"
#include "universecomposite.h"

class reset : public Visitor
{
public:
    reset();

    void visit(UniverseBody &body) override;
    void visit(UniverseComposite& composite) override;
};

#endif // RESET_H
