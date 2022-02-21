#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"
#include <memory>
#include "DataSettings/Serializable.h"

using namespace glm;
using namespace std;

class Light: public Serializable {
protected:
    vec3 Ia;
    vec3 Id;
    vec3 Is;

public:
    /*
     * Constructor de la classe Light.
     * param Ia: component ambient de la llum.
     * param Id: component difosa de la llum.
     * param Is: component especular de la llum.
     * */
    Light(vec3 Ia, vec3 Id, vec3 Is);
    Light();
    vec3 getIa();
    vec3 getId();
    vec3 getIs();
    //Calcula l'atenuacio de la llum al punt passat per parametre
    virtual float attenuation(vec3 point) = 0;
    //Calcula el vector L al punt passat per parametre
    virtual vec3 vectorL(vec3 point) = 0;
    //Calcula la distancia del punt a la llum
    virtual float distanceToLight(vec3 point) = 0;
    virtual ~Light() {};

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;
};

#endif // LIGHT_H
