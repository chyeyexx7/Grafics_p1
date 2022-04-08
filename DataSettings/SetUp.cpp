#include "SetUp.h"

SetUp::SetUp()
{
  camera = make_shared<Camera>();
  MAXDEPTH=1;
}

bool SetUp::load(Serializable::SaveFormat saveFormat, QString nameFile)
{
    QFile loadFile(/*saveFormat == Json
        ? */QString(nameFile.append(".json"))/*
        : QString(nameFile.append(".dat"))*/);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open the setup file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonParseError error;
    QJsonDocument loadDoc(/*saveFormat == Json
        ? */QJsonDocument::fromJson(saveData, &error)
        /*: QJsonDocument(QCborValue::fromCbor(saveData).toMap().toJsonObject())*/);


    if (loadDoc.isNull()) {
        qWarning("Parse error in json.");
        return false;
    }
    QJsonObject object = loadDoc.object();

    read(object);

    QTextStream(stdout) << "Loaded setup using "
                        << (saveFormat != Json ? "CBOR" : "JSON") << "...\n";
    return true;
}
//! [3]

//! [4]
bool SetUp::save(SetUp::SaveFormat saveFormat, QString nameFile) const
{
    QFile saveFile(saveFormat == Json
                   ? QString(nameFile.append(".json"))
                   : QString(nameFile.append(".dat")));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open setup file.");
        return false;
    }

    QJsonObject setUpObject;
    write(setUpObject);
    saveFile.write(/*saveFormat == Json
        ? */QJsonDocument(setUpObject).toJson()
        /*: QCborValue::fromJsonValue(setUpObject).toCbor()*/);

    return true;
}

//! [0]
void SetUp::read(const QJsonObject &json)
{
    if (json.contains("renderType") && json["renderType"].isString())
        renderingType = RayTracingFactory::getInstance()->getRenderType(json["renderType"].toString());
    if (json.contains("output") && json["output"].isString())
        outputFile =json["output"].toString();

    if (json.contains("camera")) {
        QJsonObject camObject = json["camera"].toObject();
        camera->read(camObject);
    }
    if (json.contains("lights") && json["lights"].isArray()) {
        QJsonArray lightsArray = json["lights"].toArray();

        for (int lightIndex = 0; lightIndex < lightsArray.size(); lightIndex++) {
            QJsonObject lightObject = lightsArray[lightIndex].toObject();
            shared_ptr<Light> l;
            if (lightObject.contains("type") && lightObject["type"].isString()) {
                QString ligthStr = lightObject["type"].toString().toUpper();
                l = LightFactory::getInstance().createLight(LightFactory::getInstance().getLightType(ligthStr));
                l->read(lightObject);
                lights.push_back(l);
            }
        }
    }
    if (json.contains("globalLight") && json["globalLight"].isArray()) {
        QJsonArray globalVec = json["globalLight"].toArray();
        globalLight[0] = globalVec[0].toDouble();
        globalLight[1] = globalVec[1].toDouble();
        globalLight[2] = globalVec[2].toDouble();
    }
    if (json.contains("background") && json["background"].isBool())
        background = json["background"].toBool();
    if (json.contains("colorTopBackground") && json["colorTopBackground"].isArray()) {
        QJsonArray globalVec = json["colorTopBackground"].toArray();
        topBackground[0] = globalVec[0].toDouble();
        topBackground[1] = globalVec[1].toDouble();
        topBackground[2] = globalVec[2].toDouble();
    }
    if (json.contains("colorDownBackground") && json["colorDownBackground"].isArray()) {
        QJsonArray globalVec = json["colorDownBackground"].toArray();
        downBackground[0] = globalVec[0].toDouble();
        downBackground[1] = globalVec[1].toDouble();
        downBackground[2] = globalVec[2].toDouble();
    }
    if (json.contains("MAXDEPTH") && json["MAXDEPTH"].isDouble()) {
        MAXDEPTH = json["MAXDEPTH"].toInt();
    }
}
//! [0]

void SetUp:: write(QJsonObject &json) const
{
   json["renderType"] = RayTracingFactory::getInstance()->getNameType(renderingType);
   json["output"] = outputFile;

    QJsonObject cameraObject;
    camera->write(cameraObject);
    json["camera"] = cameraObject;

    QJsonArray lightsArray;
    for (const shared_ptr<Light> &l : lights) {
        QJsonObject lightObject;
        auto  value = LightFactory::getInstance().getIndexType (l);
        QString className = LightFactory::getInstance().getNameType(value);

        l->write(lightObject);
        lightObject["type"] = className;
        lightsArray.append(lightObject);
    }
    json["lights"] = lightsArray;
    QJsonArray auxArray0;
    auxArray0.append(topBackground[0]);auxArray0.append(topBackground[1]);auxArray0.append(topBackground[2]);
    json["colorTopBackground"] = auxArray0;

    QJsonArray auxArray1;
    auxArray1.append(downBackground[0]);auxArray1.append(downBackground[1]);auxArray1.append(downBackground[2]);
    json["colorDownBackground"] = auxArray1;

    json["background"] = background;
    json["MAXDEPTH"] = MAXDEPTH;
    QJsonArray auxArray;
    auxArray.append(globalLight[0]);auxArray.append(globalLight[1]);auxArray.append(globalLight[2]);
    json["globalLight"] = auxArray;

}

void SetUp::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "renderType:\t" << RayTracingFactory::getInstance()->getNameType(renderingType) << "\n";
    QTextStream(stdout) << indent << "output:\t" << outputFile << "\n";

    camera->print(2);
    QTextStream(stdout) << indent << "Ligths:\t\n";
    for (unsigned int i =0; i< lights.size(); i++) {
        auto value = LightFactory::getInstance().getIndexType (lights[i]);
        QString className = LightFactory::getInstance().getNameType(value);
        QTextStream(stdout) << indent+2 << "type:\t" << className << "\n";

        lights[i]->print(2);

    }
    QTextStream(stdout) << indent << "background:\t" << background << "\n";
    QTextStream(stdout) << indent << "MAXDEPTH:\t" << MAXDEPTH << "\n";
    QTextStream(stdout) << indent << "globalLight:\t" << globalLight[0] << ", "<< globalLight[1] << ", "<< globalLight[2] << "\n";
    QTextStream(stdout) << indent << "colorTopBackground:\t" << topBackground[0] << ", "<< topBackground[1] << ", "<< topBackground[2] << "\n";
    QTextStream(stdout) << indent << "colorDownBackground:\t" << downBackground[0] << ", "<< downBackground[1] << ", "<< downBackground[2] << "\n";
}

RayTracingFactory::RENDER_TYPES SetUp::getRenderType() {
    return renderingType;
}

shared_ptr<Camera> SetUp::getCamera() {
    return(camera);
}

QString SetUp::getOutputFile() {
    return outputFile;
}

vec3 SetUp::getGlobalLight() {
    return globalLight;
}

std::vector<shared_ptr<Light>> SetUp::getLights() {
    return lights;
}

bool SetUp::getBackground() {
    return background;
}

vec3 SetUp::getTopBackground(){ return topBackground; }
vec3 SetUp::getDownBackground() {return downBackground; }

int SetUp::getMAXDEPTH() { return MAXDEPTH;}

void SetUp::setOutpuFile(QString name) {
    this->outputFile = name;
}
void SetUp::setRenderType(RayTracingFactory::RENDER_TYPES type) {
    this->renderingType = type;
}
void SetUp::setCamera(shared_ptr<Camera> cam) {
    this->camera = cam;
}
void SetUp::setGlobalLight(vec3 globalLight) {
    this->globalLight = globalLight;
}
void SetUp::setLights(std::vector<shared_ptr<Light>> lights) {
    this->lights = lights;
}
void SetUp::setBackground(bool back) {
    this->background = back;
}
void SetUp::setTopBackground(vec3 color) {
    this->topBackground = color;
}
void SetUp::setDownBackground(vec3 color) {
    this->downBackground = color;
}
