#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache() = default;

TextureCache::~TextureCache() = default;

GLTexture TextureCache::getTexture(const std::string& texturePath)
{
    const auto mit = _textureMap.find(texturePath);

    if (mit == _textureMap.end())
    {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        _textureMap.insert(make_pair(texturePath, newTexture));

        return newTexture;
    }

    return mit->second;
}
