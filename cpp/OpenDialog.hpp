#ifndef OPEN_DIALOG
#define OPEN_DIALOG

#include <windows.h>
#include <shlobj.h>
#include <string>

std::string OpenFileDialog(const char* message = "Select File");

std::string OpenFolderDialog(const char* message = "Select Folder");

#endif