#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
class Texture
{
public:
    bool loadTexture(const std::string& fileName,const GLuint& mode);
    void bind();
    void unbind();
    void cleanUp();
private:
    std::string mFileName;
    int mWidth = 0;
    int mHeight = 0;
    int mNrChannels = 0;
    GLuint mTexture = 0;
};

#endif // TEXTURE_H
