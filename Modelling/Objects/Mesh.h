#pragma once

#include <vector>
#include <string>
#include <limits>

#include <QString>
#include <QFile>
#include <QRegularExpression>


#include <iostream>
#include <stdlib.h>
#include <cstring>

#include "Object.h"
#include "Factories/ObjectFactory.h"
#include "Cara.h"
#include "Triangle.h"

using namespace std;

class Mesh : public Object
{
public:
    Mesh() {};
    Mesh(const QString &fileName);
    Mesh(const QString &fileName, float data);
    virtual bool closestHit( Ray& r, HitInfo& info) const override;
    virtual bool hasHit(const Ray& r) const override;

    virtual void aplicaTG(shared_ptr<TG> tg) override;

    virtual void read (const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

   virtual ~Mesh();
private:

    QString nom;
    vector<Cara> cares; // cares de l'objecte
    vector<vec4> vertexs; // vertexs de l'objecte sense repetits
    vector<Triangle> triangles; // triangulos del objeto

    void load(QString filename);
    void construeix_triangles();
};

