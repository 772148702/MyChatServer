
#include "FileManager.h"

#include <string.h>

#include "../base/AsyncLog.h"
#include "../base/Platform.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

bool FileManager::Init(const char* basepath)
{
    m_basepath = basepath;
#ifdef WIN32
    if(!PathFileExisit(basepath))
    {
        LOGE("basepath %s doesnot exist.",basepath);
        if(!CreateDirectoryA(basepath,NULL))
        {
            return false;
        }
    }
    return true;
#else
    DIR * dp = opendir(basepath);
    if(dp==NULL)
    {
        LOGE("open base dir error, errno: %d, %s",errno,strerror(errno));

        if(mkdir(basepath,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)==0)
            return true;
        LOGE("create base dir error, %s , errno: %d, %s", basepath, errno, strerror(errno));
        return false;
    }
    struct dirent* dirp;
    while((dirp=readdir(dp))!=NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        m_listFiles.emplace_back(dirp->d_name);
        LOGI("filename: %s", dirp->d_name);

    }
    closedir(dp);
#endif
    return true;
}

bool FileManager::IsFileExist(const char* filename)
{
     std::lock_guard<std::mutex> guard(m_mtFile);

     for(const auto& iter:m_listFiles)
     {
         if(iter==filename)
         {
             return true;
         }
     }

     std::string filepath = m_basepath;
     filepath +=filename;
     FILE* fp = fopen(filepath.c_str(),"r");
     if(fp!=NULL)
     {
         fclose(fp);
         m_listFiles.emplace_back(filename);
         return true;
     }
     return false;
}

void FileManager::addFile(const char* filename)
{
    std::lock_guard<std::mutex> guard(m_mtFile);
    m_listFiles.emplace_back(filename);
}