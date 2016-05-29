#ifndef UNIVERSECOMPOSITE_H
#define UNIVERSECOMPOSITE_H

#include "visitor.h"
#include <string>
#include <vector>


class UniverseComposite : public UniverseComponent {

public:
    UniverseComposite(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "");
    virtual ~UniverseComposite();

    //build up the composition
    virtual void add(UniverseComponent* component) { m_children.push_back(component); }

    //Accept visitor
    virtual void accept(Visitor& v);
    virtual std::vector<UniverseComponent*> getChildren() { return m_children; }

    /*********************************************
     * Inherited methods from UniverseComponent
     * *******************************************/
    virtual void render(QPainter& painter) const;
    virtual void renderLabel(QPainter& painter) const;
    virtual void addAttractionTo(UniverseBody& other) const;
    virtual void resetForces();
    virtual void addAttractionFrom(const UniverseComponent& component);
    virtual void updatePosition(int timestep);

    /*********************************************
     * Methods used to enable construction of the universe with relative positions
     * *******************************************/
    void setPosition(double x, double y) { m_xPosition = x; m_yPosition = y; }
    void setVelocity(double x, double y) { m_xVelocity = x; m_yVelocity = y; }
    //propagates the position and velocity of each object down to it's children
    void convertRelativeToAbsolute(double xp, double yp, double xv, double yv);
    double getInitialPositionX() const { return m_initialXPos; }
    double getInitialPositionY() const { return m_initialYPos; }
    void setInitialXPosition(double x) { m_initialXPos = x; }
    void setInitialYPosition(double y) { m_initialYPos = y; }

private:
    std::vector<UniverseComponent*> m_children;

    //used only to enable construction of the universe with relative positions
    double m_xVelocity;
    double m_yVelocity;
    double m_xPosition;
    double m_yPosition;
    double m_initialXPos;
    double m_initialYPos;
};

#endif // UNIVERSECOMPOSITE_H
