#include <cstdio>
#include <string>
#include <fstream>

#include "cpp/Support.hpp"
#include "cpp/OpenDialog.hpp"

// compile:
// g++ main.cpp cpp\OpenDialog.cpp cpp\Support.cpp -lcomdlg32 -o main.exe
// https://json.org/example.html

typedef std::string str;

constexpr size_t stepReadSize = 1024 * 1024; // 10 MB
constexpr char rangeCharactersIn[] = {'{', '(', '['};
constexpr char rangeCharactersOut[] = {'}', ')', ']'};
constexpr char separateCharacters[] = {',', ';'};

std::string getDeepthString(int deepth)
{
    return std::string(deepth *4, ' ');
}

size_t belongToArray(const char character, const char* array, size_t arraySize)
{
    for(int i=0; i<arraySize; i++)
    {
        if(character == array[i])
            return i;
    }
    return -1;
}

std::string processStep(const char* readedStep, size_t stepSize, int &deepth)
{
    std::string processedStep = "";
    for(int j=0; j<stepSize; j++)
    {
        const char &character = readedStep[j];
        size_t position;

        position = belongToArray(character, rangeCharactersIn, sizeof(rangeCharactersIn));
        if(position != -1)
        {   // found in array
            // printf("found rangeCharactersIn %c\n", character);

            processedStep += '\n';
            processedStep += getDeepthString(deepth) + character + '\n';
            ++deepth;
            processedStep += getDeepthString(deepth);
            continue;
        }
        
        position = belongToArray(character, rangeCharactersOut, sizeof(rangeCharactersOut));
        if(position != -1)
        {   // found in array
            // printf("found rangeCharactersOut %c\n", character);

            if(deepth > 0)
                --deepth;
            processedStep += + '\n';
            processedStep += getDeepthString(deepth) + character;
            continue;
        }
        
        position = belongToArray(character, separateCharacters, sizeof(separateCharacters));
        if(position != -1)
        {   // found in array
            // printf("found separateCharacters %c\n", character);

            processedStep += character;
            processedStep += '\n';
            processedStep += getDeepthString(deepth);
            continue;
        }

        // printf("not found %c\n", character);
        processedStep += character;
    }
    return processedStep;
}

int main()
{
    str filePath = OpenFileDialog();
    if(filePath == "") return 0;

    size_t fileSize = getFileSize(filePath);
    if(fileSize == -1)
    {
        fprintf(stderr, "Can't read file size %s\n", filePath.c_str());
        return 10;
    }

    printf("size: % 8lld\n", fileSize);

    std::ifstream infile(filePath, std::ios::binary);
    if(!infile.good())
    {
        fprintf(stderr, "Can't open read file %s\n", filePath.c_str());
        return 20;
    }
    
    std::ofstream outfile(filePath+"2", std::ios::binary);
    if(!outfile.good())
    {
        fprintf(stderr, "Can't open save file %s\n", filePath.c_str());
        return 30;
    }

    size_t readedFileSize = 0;
    int deepth = 0;
    while (fileSize > readedFileSize)
    {
        size_t readSize = 0;

        if(fileSize <= stepReadSize)
            readSize = fileSize;
        else
            readSize = stepReadSize;

        fileSize -= readSize;

        printf("read: % 8lld, left % 8lld\n", readSize, fileSize);

        char buffer[stepReadSize];
        infile.read(buffer, stepReadSize);

        std::string processedStep = processStep(buffer, readSize, deepth);

        outfile.write(processedStep.c_str(), processedStep.size());
    }

    infile.close();
    outfile.close();

}