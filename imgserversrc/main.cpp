
#include <iostream>
#include <stdlib.h>

#include "../base/Platform.h"
#include "../base/Singleton.h"
#include "../base/ConfigFileReader.h"
#include "../base/AsyncLog.h"
#include "../net/EventLoop.h"
#include "../fileserversrc/FileManager.h"
#include "../fileserversrc/FileServer.h"

#ifndef WIN32
#include <string.h>
#include "../utils/DaemonRun.h"
#endif 

using namespace net;

#ifdef WIN32
//初始化Windows socket库
NetworkInitializer windowsNetworkInitializer;
#endif

EventLoop g_mainLoop;

#ifndef WIN32
void prog_exit(int signo)
{
    std::cout << "program recv signal [" << signo << "] to exit." << std::endl;

    Singleton<FileServer>::Instance().Uninit();
    g_mainLoop.quit();
}
#endif

int main(int argc, char* argv[])
{
#ifndef WIN32
    //设置信号处理
    signal(SIGCHLD, SIG_DFL);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, prog_exit);
    signal(SIGTERM, prog_exit);


    int ch;
    bool bdaemon = false;
    while ((ch = getopt(argc, argv, "d")) != -1)
    {
        switch (ch)
        {
        case 'd':
            bdaemon = true;
            break;
        }
    }

    if (bdaemon)
        daemon_run();
#endif

#ifdef WIN32
    CConfigFileReader config("../etc/imgserver.conf");
#else
    CConfigFileReader config("etc/imgserver.conf");
#endif

    std::string logFileFullPath;

#ifndef WIN32
    const char* logfilepath = config.GetConfigName("logfiledir");
    if (logfilepath == NULL)
    {
        LOGF("logdir is not set in config file");
        return 1;
    }

    //如果log目录不存在则创建之
    DIR* dp = opendir(logfilepath);
    if (dp == NULL)
    {
        if (mkdir(logfilepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
        {
            LOGF("create base dir error, %s , errno: %d, %s", logfilepath, errno, strerror(errno));
            return 1;
        }
    }
    closedir(dp);

    logFileFullPath = logfilepath;
#endif

    const char* logfilename = config.GetConfigName("logfilename");
    logFileFullPath += logfilename;

    CAsyncLog::Init(logFileFullPath.c_str());

    const char* filecachedir = config.GetConfigName("imgcachedir");
    Singleton<FileManager>::Instance().Init(filecachedir);

    const char* listenip = config.GetConfigName("listenip");
    short listenport = (short)atol(config.GetConfigName("listenport"));
    Singleton<FileServer>::Instance().Init(listenip, listenport, &g_mainLoop, filecachedir);

    LOGI("imgserver initialization complete, now you can use client to connect it.");
    
    g_mainLoop.loop();

    LOGI("exit imgserver.");

    return 0;
}
