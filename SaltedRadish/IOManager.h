#pragma once
#include <vector>
#include <string>

class IOManager {
public:
    static bool readToFileBuffer(const std::string& filePath ,std::vector<unsigned char>& buffer);
};
