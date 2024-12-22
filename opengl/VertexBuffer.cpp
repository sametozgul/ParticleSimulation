#include "VertexBuffer.h"
#include "Logger.h"

#include <iostream>
void VertexBuffer::cleanup() {
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1,&mEBO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteBuffers(1, &instanceColorVBO);
    glDeleteVertexArrays(1, &mVAO);

}

void VertexBuffer::init(OGLMesh vertexData_, std::vector<glm::vec3> colors,std::vector<glm::mat4> models)
{
    mVertexData = vertexData_;
    modelMatrices = models;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);
    glGenBuffers(1, &instanceVBO);
    glGenBuffers(1, &instanceColorVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertexData.vertices.size() * sizeof(OGLVertex), &mVertexData.vertices.at(0), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mVertexData.indices.size() * sizeof(unsigned int), &mVertexData.indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OGLVertex), (void*) offsetof(OGLVertex, position));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, instanceColorVBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);  // Per-instance


    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4),
                 &modelMatrices[0], GL_STATIC_DRAW);

    for(unsigned int i = 0; i < modelMatrices.size(); i++)
    {
        std::size_t v4s = sizeof(glm::vec4);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4*v4s, (void*)0);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4*v4s, (void*)(1*v4s));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4*v4s, (void*)(2*v4s));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4*v4s, (void*)(3*v4s));
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);

    }
    // glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Logger::log(1, "%s: VAO and VBO initialized\n", __FUNCTION__);
}
void VertexBuffer::bind() {
    glBindVertexArray(mVAO);
}

void VertexBuffer::unbind() {
    glBindVertexArray(0);
}

void VertexBuffer::draw(GLuint mode, unsigned int start, unsigned int num) {
    glDrawArrays(mode, start, num);
}

void VertexBuffer::draw()
{
    glBindVertexArray(mVAO);
    glDrawElementsInstanced(GL_TRIANGLE_FAN, static_cast<unsigned int>(mVertexData.indices.size()), GL_UNSIGNED_INT, 0, modelMatrices.size());
    glBindVertexArray(0);
}

void VertexBuffer::bindAndDraw(GLuint mode) {
    bind();
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mVertexData.indices.size()), GL_UNSIGNED_INT, 0);
    unbind();
}

void VertexBuffer::upload(std::vector<glm::mat4> models)
{
    modelMatrices = models;
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0,  modelMatrices.size() * sizeof(glm::mat4),
                    &modelMatrices[0]);
}
