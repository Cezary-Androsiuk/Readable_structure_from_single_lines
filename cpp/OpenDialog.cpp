#include "OpenDialog.hpp"

std::string OpenFileDialog(const char* message)
{
    OPENFILENAME ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name
    HWND hwnd = NULL;       // owner window
    HANDLE hf;              // file handle

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = message;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    if (GetOpenFileName(&ofn) == TRUE) 
    {
        return std::string(ofn.lpstrFile);
    }
    return std::string();
}

std::string OpenFolderDialog(const char* message)
{
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    char szFolder[MAX_PATH];
    bi.hwndOwner = NULL;
    bi.pszDisplayName = szFolder;
    bi.lpszTitle = message;
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = NULL;
    bi.lParam = 0;
    bi.iImage = -1;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != NULL) {
        // Get the name of the folder and put it in path
        char path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            // Free memory used
            IMalloc* imalloc = 0;
            if (SUCCEEDED(SHGetMalloc(&imalloc))) {
                imalloc->Free(pidl);
                imalloc->Release();
            }
            return std::string(path);
        }
    }
    return std::string();
}