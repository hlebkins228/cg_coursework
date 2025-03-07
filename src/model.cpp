#include "model.h"


mat4Type BaseModel::getRotationMatrix(vec3Type rotateVec)
{
    mat4Type mRotateX = mat4Type(
        vec4Type(1.0, 0.0, 0.0, 0.0),
        vec4Type(0.0, cos(rotateVec.x), sin(rotateVec.x), 0.0),
        vec4Type(0.0, -sin(rotateVec.x), cos(rotateVec.x), 0.0),
        vec4Type(0.0, 0.0, 0.0, 1.0)
    );
    mat4Type mRotateY = mat4Type(
        vec4Type(cos(rotateVec.y), 0.0, -sin(rotateVec.y), 0.0),
        vec4Type(0.0, 1.0, 0.0, 0.0),
        vec4Type(sin(rotateVec.y), 0.0, cos(rotateVec.y), 0.0),
        vec4Type(0.0, 0.0, 0.0, 1.0)
    );
    mat4Type mRotateZ = mat4Type(
        vec4Type(cos(rotateVec.z), sin(rotateVec.z), 0.0, 0.0),
        vec4Type(-sin(rotateVec.z), cos(rotateVec.z), 0.0, 0.0),
        vec4Type(0.0, 0.0, 1.0, 0.0),
        vec4Type(0.0, 0.0, 0.0, 1.0)
    );

    return mRotateZ * mRotateY * mRotateX;
}

vec4Type BaseModel::rotateVec(vec4Type vec, vec3Type rotateVec)
{
    return getRotationMatrix(rotateVec) * vec;
}
