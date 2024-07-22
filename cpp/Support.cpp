#include "Support.hpp"

size_t getFileSize(std::string filePath)
{
    std::fstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
    if(!file)
    {
        fprintf(stderr, "Can't open file to read size %s\n", filePath.c_str());
        return -1;
    }
    return file.tellg();
}