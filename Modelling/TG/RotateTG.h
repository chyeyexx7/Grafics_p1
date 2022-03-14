#ifndef ROTATETG_H
#define ROTATETG_H

#include "TG.h"

class RotateTG: public TG
{
public:
    glm::vec3 rotation;
    glm::vec3 axis_vector;
    RotateTG(glm::vec3 axisV, float angle);
    virtual ~RotateTG();
};

#endif // ROTATETG_H
