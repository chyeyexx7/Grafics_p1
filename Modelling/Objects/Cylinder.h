#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Sphere.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"
#include "Modelling/TG/ScaleTG.h"

class Cylinder: public Object
{
public:
    // Constructors
    Cylinder() {};
    Cylinder(vec3 cen, vec3 ax, float r, float h, float data);
    Cylinder(float data);

    // Destructor
    virtual ~Cylinder() {};

    virtual bool closestHit(Ray& r, HitInfo& info) const override;
    virtual bool hasHit(const Ray& r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;


    // Getters
    vec3 getCenter() { return center;};
    vec3 getAxis() { return axis;};
    float getHeight() { return h;};
    float getRadius() { return radius;}


private:
    // Centre del cilindro
    vec3 center;
    // Axis del cilindro
    vec3 axis;
    // Radio del cilindro
    float radius;
    // Numero PI
    const float PI = 3.141592653;
    // Altura cilindro
    float h;

};

#endif // CYLINDER_H
