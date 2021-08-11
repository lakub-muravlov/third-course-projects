#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <Psapi.h>
#include <locale.h>

using namespace std;

struct Process
{
    DWORD procID;
    WCHAR procName[MAX_PATH];
    WCHAR procOwner[MAX_PATH];
    WCHAR procDomain[MAX_PATH];
    DWORD procState;
    DOUBLE procTime;
    DOUBLE procMem;
};

struct TimeProcess
{
    ULONGLONG timeProc = 0;
    ULONGLONG timeSystem = 0;
};

Process GetProcess(DWORD Pid)
{
    Process current;
    current.procID = Pid;
    HANDLE descriptProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, Pid);
    HANDLE tokenHandle;
    if (descriptProcess)
    {
        GetExitCodeProcess(descriptProcess, &current.procState);
        GetProcessImageFileName(descriptProcess, current.procName, MAX_PATH);
        if (OpenProcessToken(descriptProcess, TOKEN_READ, &tokenHandle))
        {
            PTOKEN_USER myUser = NULL;
            DWORD tokenInfoLen = 0;
            GetTokenInformation(tokenHandle, TokenUser, myUser, tokenInfoLen, &tokenInfoLen);
            myUser = (PTOKEN_USER)malloc(tokenInfoLen);
            if (myUser)
            {
                if (GetTokenInformation(tokenHandle, TokenUser, myUser, tokenInfoLen, &tokenInfoLen))
                {
                    DWORD size = MAX_PATH;
                    SID_NAME_USE sidname;
                    LookupAccountSid(NULL, myUser->User.Sid, current.procOwner, &size, current.procDomain, &size, &sidname);
                }
                free(myUser);
            }
            PROCESS_MEMORY_COUNTERS tempmem;
            if (GetProcessMemoryInfo(descriptProcess, &tempmem, sizeof(tempmem)))
            {
                MEMORYSTATUSEX memStEx;
                memStEx.dwLength = sizeof(memStEx);
                if (GlobalMemoryStatusEx(&memStEx))
                {
                    current.procMem = tempmem.WorkingSetSize * 100.0 / memStEx.ullTotalPhys;
                }
            }
            CloseHandle(tokenHandle);
        }
        CloseHandle(descriptProcess);
    }
    else
    {
        current.procID = 0;
    }
    return current;
}

ULONGLONG timeDiff(const FILETIME& A, const FILETIME& B)
{
    LARGE_INTEGER first, second;
    first.LowPart = A.dwLowDateTime;
    first.HighPart = A.dwHighDateTime;
    second.LowPart = B.dwLowDateTime;
    second.HighPart = B.dwHighDateTime;
    return first.QuadPart + second.QuadPart;
}

void GetTime(DWORD PID, TimeProcess* timeptr)
{
    FILETIME CreationProcTime;
    FILETIME ExitProcTime;
    FILETIME KernelProcTime;
    FILETIME UserProcTime;
    FILETIME IdleTime;
    FILETIME KernelSysTime;
    FILETIME UserSysTime;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, PID);
    if (hProcess)
    {
        if (GetProcessTimes(hProcess, &CreationProcTime, &ExitProcTime, &KernelProcTime, &UserProcTime))
        {
            timeptr->timeProc = timeDiff(KernelProcTime, UserProcTime);
        }
        if (GetSystemTimes(&IdleTime, &KernelSysTime, &UserSysTime))
        {
            timeptr->timeSystem = timeDiff(KernelSysTime, UserSysTime);
        }
    }
}

MEMORYSTATUSEX thisMemory;

void getMemoryInfo() {
    thisMemory.dwLength = sizeof(thisMemory);
    GlobalMemoryStatusEx(&thisMemory);

    wcout << "Used memory (%):          " << thisMemory.dwMemoryLoad << " %" << endl;
    wcout << "Total physical memory:    " << thisMemory.ullTotalPhys / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
    wcout << "Free physical memory:     " << thisMemory.ullAvailPhys / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
    wcout << "Total paging file:        " << thisMemory.ullTotalPageFile / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
    wcout << "Free paging file:         " << thisMemory.ullAvailPageFile / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
    wcout << "Total virtual memory:     " << thisMemory.ullTotalVirtual / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
    wcout << "Free virtual memory:      " << thisMemory.ullAvailVirtual / 1024.0 / 1024.0 / 1024.0 << " GB" << endl;
}

void PrintInformation(Process* processarr, DWORD countproc)
{
    wcout << "--------------------------------------------------------------------------------------------------------\n";
    wprintf(L"| %-5s | %-35s | %-7s | %-6s | %-8s | %-4s | %-15s |\n", L"PID", L"Name", L"State", L"Memory,%", L"Time,%", L"User", L"Domain");
    wcout << "--------------------------------------------------------------------------------------------------------\n";
    PWCHAR name;
    for (DWORD i = 0; i < countproc; i++)
    {
        if (processarr[i].procID != 0)
        {
            PWCHAR temp = name = wcstok(processarr[i].procName, L"\\");
            while (temp != NULL)
            {
                name = temp;
                temp = wcstok(NULL, L"\\");
            }
            wprintf(L"| %-5u | %-35s | %-7s | %-7lf | %-7lf | %-4s | %-10s |\n",
                processarr[i].procID, name, processarr[i].procState == 259 ? L"running" : L"waiting",
                processarr[i].procMem, processarr[i].procTime,
                processarr[i].procOwner, processarr[i].procDomain);
        }
    }
    wcout<<"--------------------------------------------------------------------------------------------------------\n";
}

int main()
{
    char chooseState='0';
    while (chooseState!='3') {
    cout << "What info do you want to see?" << endl << "Enter 'M' to see current memory status" << endl << "Enter 'T' to see process table" << endl;
    double freq;
    cin >> chooseState;
    if (chooseState == 'M' || chooseState == 'm') {
        cout << "Choose info refresh rate in seconds:\n";
        cin >> freq;
            int count = 0;
            while (true) {
                system("cls");
                getMemoryInfo();
                Sleep(freq * 1000);
                count++;
                if (count == 9) {
                    cout << "If you want to resume monitoring this data press 1" << endl;
                    cout << "If you want to choose other option press 2" << endl;
                    cout << "If you want to exit press 3" << endl;
                    cin >> chooseState;
                    if (chooseState == '1') { count = 0; }
                    if (chooseState == '2') { break; }
                    if (chooseState == '3') { return 0; }
                }
            }
        }
        else if (chooseState == 't' || chooseState == 'T') {
            cout << "Choose info refresh rate in seconds:\n";
            cin >> freq;
            DWORD desProcesses[1024];
            DWORD sizeofArray, countProcess;
            int count = 0;
            while (true)
            {
                system("cls");
                if (EnumProcesses(desProcesses, sizeof(desProcesses), &sizeofArray) == 0) return 27;
                countProcess = sizeofArray / sizeof(DWORD);
                Process* Processes = new Process[countProcess];
                TimeProcess* startTime = new TimeProcess[countProcess];
                TimeProcess* endTime = new TimeProcess[countProcess];

                for (DWORD i = 0; i < countProcess; i++)
                {
                    Processes[i] = GetProcess(desProcesses[i]);
                    GetTime(desProcesses[i], startTime + i);
                }
                Sleep(2000);
                for (DWORD i = 0; i < countProcess; i++)
                {
                    GetTime(desProcesses[i], endTime + i);
                }

                for (DWORD i = 0; i < countProcess; i++)
                {
                    Processes[i].procTime = 100.0 * (endTime[i].timeProc - startTime[i].timeProc) /
                        (endTime[i].timeSystem - startTime[i].timeSystem);
                }
                PrintInformation(Processes, countProcess);
                count++;
                if (count == 9) {
                    cout << "If you want to resume monitoring this data press 1" << endl;
                    cout << "If you want to choose other option press 2" << endl;
                    cout << "If you want to exit press 3" << endl;
                    cin >> chooseState;
                    if (chooseState == '1') { count = 0; }
                    if (chooseState == '2') { break; }
                    if (chooseState == '3') { return 0; }
                }
                Sleep(freq * 1000);
            }
        }
        else
            cout << "Wrong letter, try again";
    }
    return 0;
}