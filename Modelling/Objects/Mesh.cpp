#include <QVector>
#include <QVector3D>

#include "Mesh.h"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
}

Mesh::Mesh(const QString &fileName, float data): Object(data)
{
    nom = fileName;
    load(fileName);
}

Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();
    if (triangles.size() > 0) triangles.clear();

}

void Mesh::construeix_triangles() {
    // TO DO Fase 1: A implementar
    for (Cara c: cares) {
        vector<int> temp = c.idxVertices;
        vec3 p1(vertexs[temp[0]]);
        vec3 p2(vertexs[temp[1]]);
        vec3 p3(vertexs[temp[2]]);
        //Triangle *triangle = new Triangle(p1, p2, p3, data);
        triangles.push_back(Triangle(p1, p2, p3, data));
    }
}


bool Mesh::closestHit(Ray &raig, HitInfo& info) const {

    // TODO Fase 1: A implementar
    bool hasHit = false;
    float closest = std::numeric_limits<float>::max();
    HitInfo temp;
    for(Triangle t: triangles) {
        if(t.closestHit(raig, temp) && temp.t < closest) {
            closest = temp.t;
            info = temp;
            hasHit = true;
        }
    }

    return hasHit;
}



bool Mesh::hasHit(const Ray& raig) const {
    // TO DO Fase 1: A implementar
    for(Triangle t: triangles) {
        if(t.hasHit(raig)) {
           return true;
        }
    }
    return false;

}

void Mesh::aplicaTG(shared_ptr<TG> t) {
    // TO DO: Fase 1
    for(Triangle triangle: triangles) {
        triangle.aplicaTG(t);
    }
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {

                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {

                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        cares.push_back(*cara);
                    }
                }
            }
            file.close();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}


//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}





