# include <windows.h>
# include <iostream>
# include <vector>

# define DISK_NAME_SIZE 4

using namespace std;

struct DiskInfo {
    TCHAR name[DISK_NAME_SIZE];
    DWORD system_flags;
    DWORD serial_number;
    TCHAR file_system[10];
    __int64 total_space;
    __int64 free_space;
};

//обьявления методов, реализация под мейном
vector<DiskInfo> getDisksInfo();

void printInfo(vector<DiskInfo> vector);

int main(int argc, char **argv) {
    vector<DiskInfo> info = getDisksInfo();
    printInfo(info);
}

void printInfo(vector<DiskInfo> vector) {
    for (auto &i : vector) {
        cout << "Disk name : \t\t" << i.name << endl;
        cout << "System flags : \t\t" << i.system_flags << endl;
        cout << "Serial number : \t" << i.serial_number << endl;
        cout << "File system : \t\t" << i.file_system << endl;
        cout << "Total space : \t\t" << i.total_space / (1024 * 1024) << " MB" << endl;
        cout << "Free space : \t" << i.free_space / (1024 * 1024) << " MB" << endl << endl;
    }
}

vector<DiskInfo> getDisksInfo() {
    auto *disk_names_arr = new TCHAR;
    int disks_num = GetLogicalDriveStrings(MAXINTATOM, disk_names_arr) / DISK_NAME_SIZE;
    vector<DiskInfo> disks_info_queue;
    for (int i = 0; i < disks_num; ++i) {
        DiskInfo *disk_info = new DiskInfo();
        strcpy(disk_info->name, disk_names_arr);
        GetVolumeInformation(disk_info->name, NULL, 0, &disk_info->serial_number, 0, &disk_info->system_flags,
                             disk_info->file_system, sizeof(disk_info->file_system));
        GetDiskFreeSpaceEx(disk_info->name, (PULARGE_INTEGER) &disk_info->free_space,
                           (PULARGE_INTEGER) &disk_info->total_space, NULL);
        disks_info_queue.push_back(*disk_info);
        disk_names_arr += sizeof(TCHAR) * DISK_NAME_SIZE;
    }
    return disks_info_queue;
}