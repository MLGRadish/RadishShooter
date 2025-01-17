#include "IOManager.h"

#include <fstream>

bool IOManager::readToFileBuffer(const std::string& filePath, std::vector<unsigned char>& buffer)
{
    std::ifstream file(filePath, std::ios::binary);

    if (file.fail()) {
        perror("Failed to load cat images!");
        return false;
    }

    file.seekg(0, std::ios::end);

    long fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    fileSize -= file.tellg();
    buffer.resize(fileSize);

    file.read(reinterpret_cast<char *>(&buffer[0]), fileSize);

    file.close();

    return true;
}
