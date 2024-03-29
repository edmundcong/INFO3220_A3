#ifndef UNIVERSECOMPONENT_H
#define UNIVERSECOMPONENT_H

#include <QPainter>
#include <string>

//you probably don't want to change this
#define GRAVITATIONAL_CONSTANT (6.67408e-11)

//enum identifying the type of component
enum UniverseComponentType { planet, star, blackhole, solarsystem, galaxy, cluster, universe };

//forward declaration
class UniverseBody;

//forward declaration of the visitor
class Visitor;

class UniverseComponent {

public:
    UniverseComponent(
            UniverseComponentType type,
            const std::string& name,
            const std::string& parentName = "")
        : m_type(type), m_name(name), m_parentName(parentName) { }
    virtual ~UniverseComponent() { }

    //accept visitor method for element heirarhcy
    virtual void accept(Visitor& v) = 0;

    //composite operation: render the subtree
    virtual void render(QPainter& painter) const = 0;
    virtual void renderLabel(QPainter& painter) const = 0;

    //composite operation: apply the attraction from this component, to the specified leaf
    virtual void addAttractionTo(UniverseBody& other) const = 0;

    //composite operation: reset the accumulated forces on all sub-components to zero
    virtual void resetForces() = 0;

    //composite operation: update attractive forces to all components of this object, from the specified component
    virtual void addAttractionFrom(const UniverseComponent& component) = 0;

    //composite operation: update the positions of all components of this object
    virtual void updatePosition(int timestep) = 0;

    //composite operation: convert relative positions to absolute positions
    //i.e. translate all child objects by the parent's position and velocity
    virtual void convertRelativeToAbsolute(double xp, double yp, double xv, double yv) = 0;

    //accessor methods
    void setName(const std::string& name) { m_name = name; }
    const std::string& getName() const { return m_name; }
    const std::string& getParentName() const { return m_parentName; }
    UniverseComponentType getType() const { return m_type; }


private:
    UniverseComponentType m_type;
    std::string m_name;
    std::string m_parentName;


};

#endif // UNIVERSECOMPONENT_H
