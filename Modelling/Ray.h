#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

using namespace glm;

class Ray {
  private:
    vec3 origin;
    vec3 direction;
    float t_min;
    float t_max;
  public:
    Ray() {}

    Ray(const vec3 &orig, const vec3 &dir, float t_min_=0.01f, float t_max_=std::numeric_limits<float>::infinity()):
      origin(orig),
      direction(dir),
      t_min(t_min_),
      t_max(t_max_)
    {}

    /* retorna el punt del raig en en temps/lambda t */
    vec3 operator() (const float &t) const {
      return origin + direction*t;
    }

    vec3 getOrigin() const       { return origin; }
    vec3 getDirection() const    { return direction; }
    vec3 pointAtParameter(float t) const { return origin + t*direction; }
    float  getTmin() const {return t_min;}
    float  getTmax() const {return t_max;}
    void   setTmin(float tmin) { t_min = tmin;}
    void   setTmax(float tmax) {t_max = tmax; }


};

