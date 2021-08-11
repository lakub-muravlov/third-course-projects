#include <pwd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <cctype>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <iostream>

#define MAX_PATH 255

using namespace std;

struct Process {
    uint procID;
    char procName[MAX_PATH];
    char procOwner[MAX_PATH];
    char procState;
    double procTime;
    double procMem;
};

struct TimeProcess {
    ulong timeProc = 0;
    ulong timeSystem = 0;
};


Process GetProcess(uint pid) {
    Process thisProc;
    char Path[MAX_PATH];
    sprintf(Path, "/proc/%d/stat", pid);
    FILE *file = fopen(Path, "r");
    if (file) {
        fscanf(file, "%d %s %c", &thisProc.procID, &thisProc.procName, &thisProc.procState);
        fclose(file);
    }
    struct stat mystat;
    stat(Path, &mystat);
    struct passwd *pw_d;
    pw_d = getpwuid(mystat.st_uid);
    strcpy(thisProc.procOwner, pw_d->pw_name);
    char Path2[MAX_PATH] = "";
    sprintf(Path2, "/proc/%d/statm", pid);
    FILE *file2 = fopen(Path2, "r");
    ulong memProc, memSys;

    if (file2) {
        fscanf(file2, "%lu", &memProc);
        fclose(file2);
    }
    struct sysinfo mem;
    sysinfo (&mem);
    memSys = mem.totalram;
    thisProc.procMem = memProc*100.0 / memSys ;

    return thisProc;
}

bool GetListProcess(uint PidArray[], uint *sizeArray) {
    uint i = 0;
    DIR *dir = opendir("/proc");
    if (dir == NULL) return false;
    struct dirent *dirdata;
    while (dirdata = readdir(dir)) {
        if (isdigit(dirdata->d_name[0]))
            PidArray[i++] = atoi(dirdata->d_name);

    }
    *sizeArray = i;
    return true;
}

void PrintInformation(Process *processarr, uint countproc) {

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-45s | %-5s | %-10s | %-10s | %-5s |\n", "PID", "Name", "State", "Memory(MB)", "Time(%)",
           "User");
    printf("---------------------------------------------------------------------------------------------------\n");

    for (uint i = 0; i < countproc; i++) {
        if (processarr[i].procID != 0) {
            printf("| %-5u | %-45s | %-5c | %-10lf | %-10lf | %-5s |\n",
                   processarr[i].procID, processarr[i].procName, processarr[i].procState,
                   processarr[i].procMem, processarr[i].procTime,
                   processarr[i].procOwner);
        }

    }
    printf("---------------------------------------------------------------------------------------------------\n");

}


TimeProcess GetTime(uint Pid) {
    TimeProcess time;
    Process current;
    char Path[MAX_PATH] = "";
    sprintf(Path, "/proc/%d/stat", Pid);
    FILE *file = fopen(Path, "r");
    ulong kerTimeProc;
    ulong userTimeProc;
    char value;
    if (file) {
        for (int i = 0; i < 13; i++) {
            fscanf(file, "%*s");
        }
        fscanf(file, "%lu %lu", &userTimeProc, &kerTimeProc);
        time.timeProc = userTimeProc + kerTimeProc;
        fclose(file);
    }
    char Path2[MAX_PATH];
    sprintf(Path2, "/proc/stat");
    FILE *file2 = fopen(Path2, "r");
    ulong user, nice, syst, idle, iowait, irq, softirq;
    if (file2) {
        fscanf(file2, "%*s");
        fscanf(file2, "%lu %lu %lu %lu %lu %lu %lu", &user, &nice, &syst, &idle, &iowait, &irq, &softirq);
        time.timeSystem = (user + nice + syst + idle + iowait + irq + softirq);
        fclose(file2);
    }

    return time;
}

void GetMemoryInfo() {
    struct sysinfo memory;
    sysinfo(&memory);
    cout << "Used memory (%): " << (memory.totalram - memory.freeram)*100.0/ memory.totalram << endl;
    cout << "Total memory (MB): "<<memory.totalram/1024.0/1024.0<<endl;
    cout << "Total swap memory (MB): "<<memory.totalswap<<endl;
    cout << "Buffer memory (MB): "<<memory.bufferram/1024.0/1024.0<<endl;
}


int main() {
    int freq = 200;
    //printf("Enter the pause duration | frequency of updating (in seconds)\n");
    //scanf("%d",&freq);
    uint desProcesses[1024];
    uint countProcess = 0;
    while (true) {
        GetMemoryInfo();
        if (GetListProcess(desProcesses, &countProcess) == 0) return 27;
        Process *myProcesses = new Process[countProcess];
        TimeProcess *startTime = new TimeProcess[countProcess];
        TimeProcess *endTime = new TimeProcess[countProcess];

        for (uint i = 0; i < countProcess; i++) {
            myProcesses[i] = GetProcess(desProcesses[i]);
            startTime[i] = GetTime(desProcesses[i]);
        }
        sleep(1);
        for (uint i = 0; i < countProcess; i++) {
            endTime[i] = GetTime(desProcesses[i]);
        }

        for (uint i = 0; i < countProcess; i++) {
            myProcesses[i].procTime = 100.0 * (endTime[i].timeProc - startTime[i].timeProc) /
                                      (endTime[i].timeSystem - startTime[i].timeSystem);
        }
        PrintInformation(myProcesses, countProcess);

        sleep(freq);
    }
}
