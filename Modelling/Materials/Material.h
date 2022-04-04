#pragma once

#include <vector>
#include "Modelling/Ray.h"
#include "Modelling/Hitable.h"
#include "DataSettings/Serializable.h"

// Classe abstracte Material. Totes les seves filles hauran de definir el metode abstracte sccater
class Material: public Serializable
{
public:

    Material();
    Material(vec3 d);
    Material(vec3 a, vec3 d, vec3 s, float shininess);
    Material(vec3 a, vec3 d, vec3 s, float shininess, float opacity);
    ~Material();

    virtual vec3 getAttenuation(const Ray& r_in, const HitInfo& rec) const = 0;
    virtual bool getOneScatteredRay(const Ray& r_in, const HitInfo& rec, Ray& r_out) const = 0;
    virtual bool getMultipleScatteredRays(const Ray& r_in, const HitInfo& rec, std::vector<Ray>& r_out) const = 0;
    virtual vec3 getDiffuse(vec2 point) const;

    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    vec3 Kt;
    float nut;
    float shininess;
    float opacity; // opacity es la fraccio de 0..1 (0 és totalment transparent, 1 és totalment opac)

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;

};


