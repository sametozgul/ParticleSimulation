#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OGLRenderData.h"



class VertexBuffer {
public:
    VertexBuffer(){}
    void init(OGLMesh vertexData_, std::vector<glm::vec3> colors, std::vector<glm::mat4> models);
    void bind();
    void unbind();
    void draw(GLuint mode, unsigned int start, unsigned int num);
    void draw();
    void bindAndDraw(GLuint mode);
    void upload(std::vector<glm::mat4> models);
    void cleanup();
    GLuint VAO(){return mVAO;}
    GLuint indicesSize(){return mVertexData.indices.size();}
private:
    std::vector<glm::mat4> modelMatrices;
protected:
    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;
    GLuint instanceVBO = 0;
    GLuint instanceColorVBO = 0;

    OGLMesh mVertexData;
};
