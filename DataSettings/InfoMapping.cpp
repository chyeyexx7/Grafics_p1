#include "InfoMapping.h"




//! [0]
void InfoMapping::read(const QJsonObject &json)
{
    if (json.contains("Real") && json["Real"].isObject()) {
        QJsonObject jobject = json["Real"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Rxmin = objectsArray[0].toDouble();
            Rzmin = objectsArray[1].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Rxmax = objectsArray[0].toDouble();
            Rzmax = objectsArray[1].toDouble();
         }
    }
    if (json.contains("Virtual") && json["Virtual"].isObject()) {
        QJsonObject jobject = json["Virtual"].toObject();
        if (jobject.contains("minPoint") && jobject["minPoint"].isArray()) {
            QJsonArray objectsArray = jobject["minPoint"].toArray();
            Vxmin = objectsArray[0].toDouble();
            Vymin = objectsArray[1].toDouble();
            Vzmin = objectsArray[2].toDouble();
         }
        if (jobject.contains("maxPoint") && jobject["maxPoint"].isArray()) {
            QJsonArray objectsArray = jobject["maxPoint"].toArray();
            Vxmax = objectsArray[0].toDouble();
            Vymax = objectsArray[1].toDouble();
            Vzmax = objectsArray[2].toDouble();
         }
    }
    if (json.contains("properties") && json["properties"].isArray()) {
        QJsonArray propsArray = json["properties"].toArray();

        for (int propIndex = 0; propIndex < propsArray.size(); propIndex++) {
            QJsonObject propObject = propsArray[propIndex].toObject();
            shared_ptr<PropertyInfo> p = make_shared<PropertyInfo>();
            p->read(propObject);
            vector<vec3> values;
            if (propObject.contains("data") && propObject["data"].isArray()) {
                QJsonArray dataArray = propObject["data"].toArray();
                for (int dataIndex = 0; dataIndex < dataArray.size(); dataIndex++) {
                    QJsonArray value = dataArray[dataIndex].toArray();
                    vec3 sample;
                    sample[0] = value[0].toDouble();
                    sample[1] = value[1].toDouble();
                    sample[2] = value[2].toDouble();
                    values.push_back(sample);
                }
            }
            props.push_back(make_pair(p, values));
        }
    }

}
//! [0]

void InfoMapping:: write(QJsonObject &json) const
{
    QJsonObject jobject;
    QJsonArray  objectsArray;
    objectsArray.append(Rxmin); objectsArray.append(Rzmin);
    jobject["minPoint"] = objectsArray;
    QJsonArray objectsArray2;
    objectsArray2.append(Rxmax); objectsArray2.append(Rzmax);
    jobject["maxPoint"] = objectsArray2;
    json["Real"] = jobject;

    QJsonObject jobject2;
    QJsonArray objectsArray3;
    objectsArray3.append(Vxmin); objectsArray3.append(Vymin);objectsArray3.append(Vzmin);
    jobject["minPoint"] = objectsArray3;
    QJsonArray objectsArray4;
    objectsArray4.append(Vxmax); objectsArray4.append(Vzmax);objectsArray4.append(Vzmax);
    jobject["maxPoint"] = objectsArray4;
    json["Virtual"] = jobject2;

    QJsonArray propsArray;
    for (unsigned int i=0; i<props.size(); i++) {
        QJsonObject propJson;

        props[i].first->write(propJson);

        QJsonArray valuesJson;
        for (unsigned int j=0; j<props[i].second.size(); j++) {
                QJsonArray val;
                val.append(props[i].second[j][0]);
                val.append(props[i].second[j][1]);
                val.append(props[i].second[j][2]);

                valuesJson.append(val);
        }
        propJson["data"] = valuesJson;
        propsArray.append(propJson);
    }
    json["properties"] = propsArray;

}

void InfoMapping::print(int indentation) const
{
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "Real:\t \n";
    QTextStream(stdout) << indent+2 << "minPoint:\t"  << Rxmin<<", "<< Rzmin<<"\n";
    QTextStream(stdout) << indent+2 << "maxPoint:\t"  << Rxmax<<", "<< Rzmax<<"\n";

    QTextStream(stdout) << indent << "Virtual:\t \n";
    QTextStream(stdout) << indent+2 << "minPoint:\t"  << Vxmin<<", "<< Vymin<<", "<< Vzmin<<"\n";
    QTextStream(stdout) << indent+2 << "maxPoint:\t"  << Vxmax<<", "<< Vymax<<", "<< Vzmin<<"\n";

    QTextStream(stdout) << indent << "properties:\t\n";
    for (unsigned int i=0; i<props.size(); i++) {
        props[i].first->print(indentation+4);
         QTextStream(stdout) << indent << "data:\t\n";
        for (unsigned int j=0; j<props[i].second.size(); j++) {
               QTextStream(stdout) << indent << "[ "<< props[i].second[j][0]<< ", "<< props[i].second[j][1]<< ", "<<props[i].second[j][2]<< " ]\n ";
        }
    }
 }

