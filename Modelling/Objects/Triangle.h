#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Object.h"
#include "Modelling/Animation.h"
#include "Modelling/Objects/Plane.h"
#include "Modelling/TG/TranslateTG.h"
#include "Modelling/TG/ScaleTG.h"

class Triangle: public Object
{
public:
    // Constructors
    Triangle() {};
    Triangle(vec3 p1, vec3 p2, vec3 p3, float data);
    Triangle(float data);

    // Destructor
    virtual ~Triangle() {};

    virtual bool closestHit(Ray& r, HitInfo& info) const override;
    virtual bool hasHit(const Ray& r) const override;
    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;


    // Calcula el normal del triangle
    vec3 calculateNormal() const;


private:
    // Tres vértices del triangulo
    vec3 p1, p2, p3;
    // Normal del triangle
    vec3 normal;
};

#endif // TRIANGLE_H
