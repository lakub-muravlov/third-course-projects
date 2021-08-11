#include <string>
#include <list>
#include <map>
#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#define MAX_PATH 255
using namespace std;

class Conductor
{

private:
    string currentPath;
    long step;
    int maxCountFiles;
    map<long,long> myMap;

public:

    Conductor(string path,long st)
    {
        currentPath = path;
        step = st;
        maxCountFiles = 0;
    }

    void HandleFolder(string path)
    {

        DIR* folder;
        struct dirent* fl;
        folder = opendir(path.c_str());
        if(!folder)
        {
            return;

        }
        else
        {
            while((fl = readdir(folder))!= NULL)
            {
                if(fl->d_type == DT_DIR)
                {
                    if(!(string(fl->d_name) == "."|| string(fl->d_name) == ".."))
                    {

                        HandleFolder(path + "/" + fl->d_name);
                    }
                }
                else if (fl->d_type == DT_REG)
                {
                    HandleFile(path + "/" + fl->d_name);
                }
            }
            closedir(folder);
        }

    }


   void  HandleFile(string pathFile)
   {

        struct stat fileInfo;
        stat(pathFile.c_str(), &fileInfo);
        long interval = fileInfo.st_size/step;
        myMap[interval]++;
        if(myMap[interval]>maxCountFiles)
        {
            maxCountFiles = myMap[interval];
        }
   }

   map<long, long> Handle(long *max)
   {
        myMap.clear();
        HandleFolder(currentPath);

        *max = maxCountFiles;
        return myMap;
   }
};


int main()
{
    string path = "/home/kub/CLionProjects/Lab1.2_Phil/";
    long step=4096;
    long maxCount;
    Conductor conductor (path, step);
    map<long,long>fileIntervals = conductor.Handle(&maxCount);
    printf("| %33s | %15s | %s\n","Interval             ","Count Files  ", "Percent files ");
    for (auto item :fileIntervals)
    {
        printf("| %15lu - %-15lu | %15lu |",item.first * step,((item.first + 1)* step - 1) ,item.second);
        printf(" %-100s \n", (string(ceil(item.second*100.0/maxCount),'|')).c_str());
    }

    return 0;
}
