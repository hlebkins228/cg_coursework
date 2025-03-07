#ifndef CAMERA_H_

#define CAMERA_H_

#include <memory>

#include "types.h"
#include "model.h"


class Camera: BaseModel
{
private:
    vec3Type eye = vec3Type(0.0, 0.0, -1.0);        // позиция камеры
    vec3Type lookAt = vec3Type(0.0);                // точка, куда смотрит камера
    vec3Type up = vec3Type(0.0, 1.0, 0.0);

    mat4Type viewMatrix = mat4Type(1.0);

    // experiment
    vec3Type angleVec = vec3Type(0.0);


    bool cameraChanged = true;

public:
    Camera() {}
    Camera(vec3Type& pos, vec3Type& eye, vec3Type& up, vec3Type& right) : lookAt(lookAt), eye(eye), up(up) {}
    ~Camera() {}
    
    // set
    void setLookAt(vec3Type& lookAt) { this->lookAt = lookAt; }
    void setEye(vec3Type& eye)       { this->eye = eye; }
    void setUp(vec3Type& up)         { this->up = up;   }

    // get
    vec3Type getLookAt()             { return lookAt; }
    vec3Type getEye()                { return eye;    }
    vec3Type getUp()                 { return up;     }

    bool isCameraChanged()           { return cameraChanged; }

    // change camera pos
    void move(cordType dx, cordType dy, cordType dz);
    void rotate(float angleX, float angleY, float angleZ);
    
    mat4Type getViewMatrix();

    virtual void draw() override { return; }

};
using cameraPtr = std::shared_ptr<Camera>;

#endif