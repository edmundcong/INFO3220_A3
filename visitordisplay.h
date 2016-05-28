#ifndef DISPLAYINFOVISITOR_H
#define DISPLAYINFOVISITOR_H

#include "universebody.h"
#include "universecomposite.h"

#include <QLabel>


class VisitorDisplay : public Visitor
{
public:
    VisitorDisplay();

    void visit(UniverseBody& body) override;
    void visit(UniverseComposite& composite) override;

private:
    QLabel* m_planetaryInfo;
};

#endif // DISPLAYINFOVISITOR_H
