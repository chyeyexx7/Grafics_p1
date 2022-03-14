#include "RotateTG.h"

RotateTG::RotateTG(glm::vec3 axisV, float angle): axis_vector(axisV)
{
    this->rotation = rotation;
    matTG = glm::rotate(glm::mat4(1.0f), this->rotation, this->axis_vector);
}

RotateTG::~RotateTG()
{

}
