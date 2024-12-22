#include "OGLRenderer.h"
#include <math.h>

OGLRenderer::OGLRenderer(GLFWwindow* win)
{
    mRenderData.rdWindow = win;
}
bool OGLRenderer::init(unsigned int width, unsigned int height)
{
    mRenderData.rdWidth = width;
    mRenderData.rdHeight = height;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::log(1,"%s :Failed to initialize GLAD.\n",__FUNCTION__);
        return false;
    }
    if (!GLAD_GL_VERSION_4_6) {
        Logger::log(1, "%s error: failed to get at least OpenGL 4.6\n", __FUNCTION__);
        return false;
    }
     mUserInterface.init(mRenderData);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&mRenderData.rdNrAttributes);

    mObjectModel = new ObjectModel();
    mObjectModel->setObjectCount(100);
    return true;
}

void OGLRenderer::resize(unsigned int width, unsigned int height)
{
    mRenderData.rdWidth = width;
    mRenderData.rdHeight = height;
    glViewport(0,0,width,height);
}

void OGLRenderer::draw()
{
    double tickTime = glfwGetTime();
    mRenderData.rdTickDiff = tickTime - mLastTickTime;

    mRenderData.rdFrameTime = mFrameTimer.stop();
    mFrameTimer.start();
    mViewMatrix = mCamera.getViewMatrix();
    mProjectionMatrix = glm::perspective(glm::radians(45.0f),(float)mRenderData.rdWidth/(float)mRenderData.rdHeight,0.1f,100.0f);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draw Here
    mObjectModel->draw();
    if(mRenderData.rdUsePolygonMode)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if(mRenderData.rdIsColorChanged)
    {
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) +0.5f;
        glUniform4f(mRenderData.rdVertexColorPosition, 0.0f, greenValue, 0.0f, 1.0f);
    }
    else{
        glUniform4f(mRenderData.rdVertexColorPosition,0.5,0.5,0.5,1.0);
    }




    glBindVertexArray(0);
    mUserInterface.createFrame(mRenderData);
    mUserInterface.render();

    mLastTickTime = tickTime;


}

void OGLRenderer::handleMousePressEvents(double xPos, double yPos)
{
    glm::vec3 pos = {xPos, yPos, 0.0f};
    mFirstMouse = true;
}

void OGLRenderer::handleMouseReleasedEvents(double xPos, double yPos)
{
    glm::vec3 pos = {xPos, yPos, 0.0f};
}

void OGLRenderer::cleanUp()
{
    mUserInterface.cleanUp();
}

