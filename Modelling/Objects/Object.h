#pragma once

#include "Modelling/Ray.h"
#include "Modelling/Hitable.h"
#include "Modelling/Animation.h"

#include "Factories/MaterialFactory.h"
#include "DataSettings/Serializable.h"


using namespace std;
// Es la classe pare de tots els objectes que s'han de visualitzar.
// Es fa una classe Objectes que hereda de Hitable i ha d'implementar el metode intersection

class Object: public Hitable, public Animable, public Serializable {
  public:
    Object();
    Object(float d);
    virtual ~Object() {};

    // Metodes a implementar en les classes filles: son  metodes abstractes
    virtual bool closestHit(Ray& r, HitInfo& info) const = 0;
    virtual bool hasHit(const Ray& r) const = 0;
    virtual void aplicaTG(shared_ptr<TG>) = 0 ;

    // OPCIONAL: Mètode que retorna totes les interseccions de l'objecte
    //    virtual bool allHits(const Ray& r, vector<shared_ptr<HitInfo> infos) const = 0;

    virtual void read (const QJsonObject &json);
    virtual void write(QJsonObject &json) const;
    virtual void print(int indentation) const;

    float    getData();
    void     setMaterial(shared_ptr<Material> m);

    shared_ptr<Material> getMaterial();
    QString name;
protected:
    shared_ptr<Material> material;   // Material de l'objecte
    float data;           // valor samplejat per aquest objecte,
                          // en el cas que provingui d'un fitxer de dades
                          // sino, per defecte és -1

};

