#include "AbstractFactoryScenes.h"

shared_ptr<SceneFactory> AbstractFactoryScenes::getSceneFactory(Serializable::SaveFormat saveFormat,
                                                    QString nameFile) {
    QFile loadFile(saveFormat == Serializable::Json
        ? QString(nameFile.append(".json"))
        : QString(nameFile.append(".dat")));
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the scene file.");
        return nullptr;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonParseError error;
    QJsonDocument loadDoc(/*saveFormat == Serializable::Json
        ?*/ QJsonDocument::fromJson(saveData, &error)
        /*: QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject())*/);

    if (loadDoc.isNull()) {
        qWarning("Parse error in json scene file.");
        return nullptr;
    }
    QJsonObject json = loadDoc.object();

    SceneFactory::SCENE_TYPES currentType;
    if (json.contains("typeScene") && json["typeScene"].isString()) {
        currentType = SceneFactory::getSceneFactoryType(json["typeScene"].toString());
        shared_ptr<SceneFactory> sf;
        switch (currentType)  {
        case SceneFactory::SCENE_TYPES::VIRTUALWORLD:
            sf = make_shared<SceneFactoryVirtual>();
            break;
        case SceneFactory::SCENE_TYPES::REALDATA:
            sf = make_shared<SceneFactoryData>();
            break;
        case SceneFactory::SCENE_TYPES::TEMPORALVW:
            // TO DO:  Afegir les factories de escenes temporals amb les animacions
            // Cal substituir la seguent linia de codi
            sf = make_shared<SceneFactoryVirtual>();
            break;
        case SceneFactory::SCENE_TYPES::TEMPORALDATA:
            // TO DO:  Afegir les factories de dades temporals amb les animacions
            // Cal substituir la seguent linia de codi
            sf = make_shared<SceneFactoryData>();
            break;
        default:
            sf = make_shared<SceneFactoryVirtual>();
            break;
        }
        QTextStream(stdout) << "Loaded format of the scene using "
                            << (saveFormat != Serializable::Json ? "CBOR" : "JSON") << "...\n";
        return sf;
    } else {
        qWarning("Parse error in json scene: Undefined scene format.");
        return nullptr;
    }
}
