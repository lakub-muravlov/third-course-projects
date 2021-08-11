#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <list>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

struct FileInfo
{
    int links{};
    string path;
};

map <int, list<FileInfo>> files;

void scanDirectories(const string& path)
{
    DIR* directory;
    struct dirent* entry;
    directory = opendir(path.c_str());
    if (!directory)
    {
        cout << "\033[31mCannot open file " << path << "\033[0m" << endl;
        return;
    }
    entry = readdir(directory);
    while (entry)
    {
        if (entry->d_type == DT_DIR)
        {
            if (string(entry->d_name) != "." && string(entry->d_name) != "..")
            {
                scanDirectories(path + "/" + entry->d_name);
            }
        }
        else if (entry->d_type == DT_REG)
        {
            string pathFile = path + "/" + entry->d_name;
            struct stat fileInfo{};
            stat(pathFile.c_str(), &fileInfo);
            if(fileInfo.st_nlink >= 2)
            {
                FileInfo info;
                info.links = fileInfo.st_nlink;
                info.path = pathFile;
                files[fileInfo.st_ino].push_back(info);
            }
        }
        entry = readdir(directory);
    }
    closedir(directory);
}

void printFilesInfo()
{
    for (auto & it : files)
    {
        for (const FileInfo& info : it.second)
        {
            cout << setw(15) << left << it.first;
            cout << setw(20) << left << info.links;
            cout << setw(40) << left << info.path;
            cout << endl;
        }
        cout << endl;
    }
    cout << setw(15) << left << "INODE #";
    cout << setw(20) << left << "Hardlinks amount";
    cout << setw(40) << left << "PATH";
    cout << endl;
}

int main()
{
    string root = "/";
    scanDirectories(root);

    printFilesInfo();
    return 0;
}
