#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct FileInfo {
    string name;
    long size{};
    bool is_hidden{};
    bool is_readonly{};
};

void getFilesInfo(basic_string<char> path, vector<FileInfo> &info);

void printInfo(const vector<FileInfo> &info);

void getFileInfo(WIN32_FIND_DATA dataa, basic_string<char> basicString);

int main(int argc, char **argv) {
    vector<FileInfo> info;

    getFilesInfo(R"(D:\Documents\Learn_3Course\OS\Lab3\Lab3_1FileTreeWIN32\Test_folder)", info);
    printInfo(info);

    return 0;
}

FileInfo getFileInfoNode(WIN32_FIND_DATA data, basic_string<char> path) {
    FileInfo current;

    current.name = path;
    current.size = (data.nFileSizeHigh * (MAXDWORD + 1)) + data.nFileSizeLow;
    current.is_readonly = data.dwFileAttributes & FILE_ATTRIBUTE_READONLY;
    current.is_hidden = data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN;
    return current;
}

void getFilesInfo(basic_string<char> path, vector<FileInfo> &info) {
    vector<FileInfo> file_info;
    WIN32_FIND_DATA file_data;
    HANDLE file_handle = FindFirstFile((path).c_str(), &file_data);
    //If there are folded directories or files and last element in path isn't * char - call function again to list all
    //contents
    if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && path.back() != '*') {
        getFilesInfo(path + "/*", info);
        return;
    }
    if (path.back() == '*') {//if last char is *, delete it from path and recursively go through all dirs
        //and add data about files in them into vector with information, from which to previous function
        path.pop_back();
        do {
            string file_name(file_data.cFileName);
            if (file_name == ".." || file_name == ".") {
                continue;
            }
            if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                getFilesInfo(path + file_name + "/*", info);
                continue;
            }
            info.push_back(getFileInfoNode(file_data, path + file_name));
        } while (FindNextFile(file_handle, &file_data) != 0);
    } else {
        info.push_back(getFileInfoNode(file_data, path));
    }
}

void printInfo(const vector<FileInfo> &info) {
    int max_size=0, mem_gist=0, mem_it_size=0, total_files=0;
    for (auto &i : info) {
        cout << i.name << endl;
        cout << "\t Size: " << i.size << " bytes" << endl;
        cout << "\t Hidden: " << (i.is_readonly ? "+" : "-") << endl;
        cout << "\t Readonly: " << (i.is_hidden ? "+" : "-") << endl;
    }
    for (auto &i : info) {
            if(i.size>max_size)
                max_size=i.size;
            total_files++;
    }
    while (mem_it_size<max_size){
        for (auto &i : info) {
            if(i.size>=mem_it_size && i.size<=mem_it_size+4096) {
                mem_gist++;
            }
        }
        cout<<"Interval"<<mem_it_size<<"-"<<mem_it_size+4096<<" bytes, files amount - "<<mem_gist<<", histogram(%): ";
        for(int i=0;i<100*mem_gist/total_files;i++)
            cout<<"|";
        cout<<endl;
        mem_gist=0;
        mem_it_size+=4096;
    }
    //cout<<max_size<<endl;
    cout << "Total num of files : " << info.size();
}
