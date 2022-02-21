#pragma once

#include "SceneFactory.h"

class SceneFactoryVirtual : public SceneFactory
{

public:
    SceneFactoryVirtual();

    virtual shared_ptr<Scene>  createScene (Serializable::SaveFormat saveFormat, QString nomFitxer) override;
    virtual shared_ptr<Scene>  createScene() override;

    virtual void read(const QJsonObject &json) override;
    virtual void write(QJsonObject &json) const override;
    virtual void print(int indentation) const override;

    bool load(Serializable::SaveFormat saveFormat, QString nameFile);
    bool save(Serializable::SaveFormat saveFormat, QString nameFile) const;

private:
    void OneSphere(shared_ptr<Scene> s);
};


