#include "SceneFactoryVirtual.h"


SceneFactoryVirtual::SceneFactoryVirtual():SceneFactory()
{
}

shared_ptr<Scene> SceneFactoryVirtual::createScene(Serializable::SaveFormat saveFormat,
                                                   QString filename) {

    scene= make_shared<Scene>();
    load(saveFormat, filename);
    print(0);

    return scene;
}

shared_ptr<Scene> SceneFactoryVirtual::createScene() {
    scene= make_shared<Scene>();
    //  Test amb una esfera. Provar sense fitxers
    //  Fase 1: Aquest codi es pot modificar per a provar
    //  la visualització de diferents primitives bàsiques
    this->OneSphere(scene);
    return scene;
}

void SceneFactoryVirtual::OneSphere(shared_ptr<Scene> s) {
    auto sphere = make_shared<Sphere>(vec3(0, 0, -1), 0.5, 1.0);
    sphere->setMaterial(make_shared<Lambertian>(vec3(0.5, 0.2, 0.7)));

    // TO DO FASE 3: CODI EXEMPLE PER FER ANIMACIONS

    //    shared_ptr<Animation> anim = make_shared<Animation>();
    //    anim->transf =  make_shared<Translate>(vec3(0.2));
    //    sphere->addAnimation(anim);

    s->objects.push_back(sphere);

}

//! [3]
bool SceneFactoryVirtual::load(SceneFactory::SaveFormat saveFormat, QString nameFile)
{
    QFile loadFile(saveFormat == Json
        ? QString(nameFile.append(".json"))
        : QString(nameFile.append(".dat")));
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the virtual scene file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData, &error)
        : QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject()));


    if (loadDoc.isNull()) {
        qWarning("Parse error in json virtual scene file.");
        return false;
    }
    QJsonObject object = loadDoc.object();
    read(object);

    QTextStream(stdout) << "Loaded virtual scene using "
                        << (saveFormat != Json ? "CBOR" : "JSON") << "...\n";
    return true;
}
//! [3]

//! [4]
bool SceneFactoryVirtual::save(Serializable::SaveFormat saveFormat, QString nameFile) const
{
    QFile saveFile(saveFormat == Json
                   ? QString(nameFile.append(".json"))
                   : QString(nameFile.append(".dat")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open virtual scene file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(saveFormat == Json
        ? QJsonDocument(setUpObject).toJson()
        : QCborValue::fromJsonValue(setUpObject).toCbor());

    return true;
}

//! [0]
void SceneFactoryVirtual::read(const QJsonObject &json)
{
    if (json.contains("scene") && json["scene"].isString())
        scene->name = json["scene"].toString();
    if (json.contains("typeScene") && json["typeScene"].isString())
        currentType = getSceneFactoryType(json["typeScene"].toString());

    if (json.contains("objects") && json["objects"].isArray()) {
        QJsonArray objectsArray = json["objects"].toArray();

        for (int objectIndex = 0; objectIndex < objectsArray.size(); objectIndex++) {
            QJsonObject objectObject = objectsArray[objectIndex].toObject();
            shared_ptr<Object> o;
            if (objectObject.contains("type") && objectObject["type"].isString()) {
                QString objStr = objectObject["type"].toString().toUpper();
                o = ObjectFactory::getInstance().createObject(ObjectFactory::getInstance().getObjectType(objStr));
                o->read(objectObject);
                scene->objects.push_back(o);
            }
        }
    }

}
//! [0]

void SceneFactoryVirtual:: write(QJsonObject &json) const
{
   json["scene"] = scene->name;
   json["typeScene"] = SceneFactory::getNameType(currentType);


    QJsonArray objectsArray;
    for (const shared_ptr<Object> &o : scene->objects) {
        QJsonObject objectObject;
        int  value = ObjectFactory::getInstance().getIndexType (o);
        QString className = ObjectFactory::getInstance().getNameType(value);

        o->write(objectObject);
        objectObject["type"] = className;
        objectsArray.append(objectObject);
    }
    json["objects"] = objectsArray;
}

void SceneFactoryVirtual::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "scene:\t" << scene->name << "\n";
    QTextStream(stdout) << indent << "typeScene:\t" << getNameType(currentType) << "\n";

    QTextStream(stdout) << indent << "Objects:\t\n";
    for (unsigned int i =0; i< scene->objects.size(); i++) {
        auto value = ObjectFactory::getInstance().getIndexType (scene->objects[i]);
        QString className = ObjectFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "name:\t" << scene->objects[i]->name <<"\n";
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";
        scene->objects[i]->print(2);
    }
 }
