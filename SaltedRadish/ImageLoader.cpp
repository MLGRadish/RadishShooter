#include "ImageLoader.h"
#include "GLTexture.h"
#include "err.h"
#include "IOManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture ImageLoader::loadPNG(const std::string& filePath)
{
    GLTexture texture = {};
    std::vector<unsigned char> in;
    int width, height;

    if (!IOManager::readToFileBuffer(filePath, in)) {
        fatalError("Failed to load cat images!");
    }

    unsigned const char* out = stbi_load_from_memory(&in[0], in.size(), &width, &height, nullptr, STBI_rgb_alpha);

    if (out == nullptr) {
        fatalError("Failed to decode cat images!");
    }

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return texture;
}

GLTexture ImageLoader::loadCubemap(const std::vector<std::string>& faces)
{
    GLTexture texture = {};
    std::vector<unsigned char> in;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);

    int width, height;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        if (!IOManager::readToFileBuffer(faces[i], in)) {
            fatalError("Failed to load cat images! " + faces[i]);
        }

        const unsigned char* out = stbi_load_from_memory(&in[0], in.size(), &width, &height, nullptr, STBI_rgb_alpha);

        if(out == nullptr) {
            fatalError("Failed to decode cat images!");
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    texture.width = width;
    texture.height = height;

    return texture;
}
