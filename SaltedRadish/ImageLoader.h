#pragma once
#include "GLTexture.h"

#include <string>
#include <vector>

class ImageLoader {
public:
	static GLTexture loadPNG(const std::string& filePath);
    static GLTexture loadCubemap(const std::vector<std::string>& faces);
};
