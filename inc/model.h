#ifndef MODEL_H_

#define MODEL_H_

#include "types.h"


class AbstractModel
{
public:
    virtual ~AbstractModel() = default;
    virtual void draw() = 0;
};


class BaseModel: public AbstractModel
{
protected:
    mat4Type getRotationMatrix(vec3Type rotateVec);
    vec4Type rotateVec(vec4Type vec, vec3Type rotateVec);

public:
    virtual ~BaseModel() = default;
    virtual void draw() = 0;

};

#endif