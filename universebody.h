#ifndef UNIVERSEBODY_H
#define UNIVERSEBODY_H

#include "visitor.h"
#include <QPushButton>


class UniverseBody : public UniverseComponent
{
public:
    UniverseBody(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "");

    virtual ~UniverseBody() {}

    //Accept visitor
    virtual void accept(Visitor& v) { v.visit(*this); }

    /*********************************************
     * Inherited methods from UniverseComponent
     * *******************************************/
    //render the subtree
    virtual void render(QPainter &painter) const;
    virtual void renderLabel(QPainter& painter) const;

    //apply the attraction from this component, to the specified leaf
    virtual void addAttractionTo(UniverseBody& body) const;

    //update attractive forces to all components of this object, from the specified component
    virtual void addAttractionFrom(const UniverseComponent& component);

    //reset the accumulated forces to zero
    virtual void resetForces();

    //update the positions of all components of this object
    virtual void updatePosition(int timestep);

    //convert the initial (relative) position and velocity, to an absolute one
    //by translating the position and velocity with the values provided
    void convertRelativeToAbsolute(double xp, double yp, double xv, double yv) {
        m_xPosition += xp;
        m_yPosition += yp;
        m_xVelocity += xv;
        m_yVelocity += yv;
    }


    /*********************************************
     * Accessor methods
     * *******************************************/
    const QColor& getColor() const { return m_color; }
    double getPositionX() const { return m_xPosition; }
    double getPositionY() const { return m_yPosition; }
    double getMass() const { return m_mass; }

    void addForce(double x, double y) { m_xForce += x; m_yForce += y; }
    void setPosition(const double x, const double y) { m_xPosition = x; m_yPosition = y; }
    void setVelocity(const double x, const double y) { m_xVelocity = x; m_yVelocity = y; }
    void setRadius(const double& radius) { m_radius = radius; }
    void setMass(const double& mass) { m_mass = mass; }
    void setColor(const QColor& color) { m_color = color; }
    void setAltColour(const QColor& colour) {m_altColour = colour; }
    const QColor& getAltColour() const { return m_altColour; }

    double getInitialPositionX() const { return m_initialXPos; }
    double getInitialPositionY() const { return m_initialYPos; }
    void setInitialXPosition(double x) { m_initialXPos = x; }
    void setInitialYPosition(double y) { m_initialYPos = y; }

private:
    double m_xForce;
    double m_yForce;
    double m_xVelocity;
    double m_yVelocity;
    double m_xPosition;
    double m_yPosition;
    double m_initialXPos;
    double m_initialYPos;

    double m_radius;
    double m_mass;
    QColor m_color;
    QColor m_altColour;
};

#endif // UNIVERSEBODY_H
