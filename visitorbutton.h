#ifndef VISITORBUTTON_H
#define VISITORBUTTON_H

class visitorButton : public Visitor
{
public:
    visitorButton();

    void visit(UniverseBody& body) override;
    void visit(UniverseComposite& composite) override;
};

#endif // VISITORBUTTON_H

#ifndef ADDBUTTONTOBODYVISITOR_H
#define ADDBUTTONTOBODYVISITOR_H

#include "universebody.h"
#include "universecomposite.h"
#include <QPushButton>


class AddButtonToBodyVisitor : public Visitor
{
public:
    AddButtonToBodyVisitor();

    void visit(UniverseBody& body) override;
    void visit(UniverseComposite& composite) override;

};

#endif // ADDBUTTONTOBODYVISITOR_H
