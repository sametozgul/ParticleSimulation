
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include <stb_image.h>

bool Texture::loadTexture(const std::string& fileName,const GLuint& mode)
{
    mFileName = fileName;
    unsigned char *data = stbi_load(mFileName.c_str(),&mWidth,&mHeight,&mNrChannels,0);
    if(!data){
        Logger::log(1,"%s: the image cannot be loaded.\n",__FUNCTION__);
        stbi_image_free(data);
        return false;
    }
    GLenum format = GL_RED;
    if (mNrChannels == 1)
        format = GL_RED;
    else if (mNrChannels == 3)
        format = GL_RGB;
    else if (mNrChannels == 4)
        format = GL_RGBA;
    glGenTextures(1,&mTexture);
    glBindTexture(GL_TEXTURE_2D,mTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, mode);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    Logger::log(1,"Texture is loaded.\n");
    return true;
}

void Texture::bind(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mTexture);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::cleanUp(){
    glDeleteTextures(1, &mTexture);
}
