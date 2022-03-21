#ifndef FITTEDPLANE_H
#define FITTEDPLANE_H

#include "Plane.h"
//#include "Animation.h"
//#include "Translate.h"
//#include "Scale.h"
#include "Modelling/Animation.h"
#include "Modelling/TG/TranslateTG.h"
#include "Modelling/TG/ScaleTG.h"

class FittedPlane: public Plane
{
public:
    FittedPlane();
    FittedPlane(vec3 normal, vec3 pass_point, vec2 pass_min, vec2 pass_max, float d);
    virtual ~FittedPlane(){}
    virtual bool closestHit(Ray &r, HitInfo &info) const override;
    virtual void aplicaTG(shared_ptr<TG> t);
    virtual void read (const QJsonObject &json) override;

private:
    vec3 normal;
    vec3 point;
    vec2 minpoint;
    vec2 maxpoint;

    double const EPSILON = 0.0000000000001;
};

#endif // FITTEDPLANE_H
