#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "camera.h"
#include "types.h"

void Camera::move(cordType dx, cordType dy, cordType dz)
{
    cameraChanged = true;
}

void Camera::rotate(float angleX, float angleY, float angleZ)
{
    angleVec.x = angleX;
    angleVec.y = angleY;
    angleVec.z = angleZ;

    cameraChanged = true;
}

// обновляет видовую матрицу (если та изменилась) перед передачей
mat4Type Camera::getViewMatrix()
{
    if (!cameraChanged)
    {
        return viewMatrix;
    }

    //rotate
    vec4Type temp = rotateVec(vec4Type(eye - lookAt, 1.0), angleVec);
    vec3Type rotatedEye = vec3Type(temp.x, temp.y, temp.z) + lookAt;
    vec3Type forward = glm::normalize(rotatedEye - lookAt);
    vec3Type right = glm::normalize(glm::cross(up, forward));
    up = glm::cross(forward, right);
    
    mat4Type mRotate = mat4Type(
        vec4Type(right.x, up.x, forward.x, 0.0),
        vec4Type(right.y, up.y, forward.y, 0.0),
        vec4Type(right.z, up.z, forward.z, 0.0),
        vec4Type(0.0, 0.0, 0.0, 1.0)
    );
    
    mat4Type mMove = mat4Type(
        vec4Type(1.0, 0.0, 0.0, 0.0),
        vec4Type(0.0, 1.0, 0.0, 0.0),
        vec4Type(0.0, 0.0, 1.0, 0.0),
        vec4Type(-rotatedEye.x, -rotatedEye.y, -rotatedEye.z, 1.0)
    );

    viewMatrix = mRotate * mMove;
    cameraChanged = false;

    return viewMatrix;
}