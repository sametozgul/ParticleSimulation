#ifndef OGLRENDERER_H
#define OGLRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Timer.h"
#include "OGLRenderData.h"
#include "UserInterface.h"
#include "Camera.h"
#include "ObjectModel.h"
class OGLRenderer
{
public:
    OGLRenderer(GLFWwindow* win);
    bool init(unsigned int width, unsigned int height);
    void resize(unsigned int width, unsigned int height);
    void handleMousePressEvents(double xPos, double yPos);
    void handleMouseReleasedEvents(double xPos, double yPos);
    void draw();
    void cleanUp();
    ObjectModel *mObjectModel = nullptr;

private:
    Timer mFrameTimer{};
    OGLRenderData mRenderData{};
    UserInterface mUserInterface{};
    Camera mCamera{};
    glm::mat4 mModelMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
    double mLastTickTime = 0.0;
    bool mFirstMouse = false;

};

#endif // OGLRENDERER_H
