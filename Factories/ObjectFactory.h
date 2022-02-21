#pragma once

#include "Modelling/Objects/Object.h"
#include "Modelling/Objects/Sphere.h"
#include "Modelling/Objects/Plane.h"

#include "Modelling/Objects/Mesh.h"



class ObjectFactory
{
    ObjectFactory(){};

public:
    typedef enum  {
        SPHERE,
        PLANE,
        TRIANGLE,
        MESH,
        CYLINDER,
        FITTEDPLANE
    } OBJECT_TYPES;

    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    shared_ptr<Object> createObject(OBJECT_TYPES t);

    // Crea un objecte gizmo per una data concreta
    // FASE 2: Cal incloure la translació i l'escalat per a poder escalar l'objecte sogon el valor de la dada
    shared_ptr<Object> createObject(  QString s, float data, OBJECT_TYPES t);

    OBJECT_TYPES getIndexType (shared_ptr<Object> l);
    OBJECT_TYPES getObjectType(QString name);
    QString      getNameType(int  t);
};

