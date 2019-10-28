/** 
 * @desc:   锟届步锟斤拷志锟洁，AsyncLog.h
 * @author: zhangyl
 * @date:   2019.04.13
 */

#ifndef __ASYNC_LOG_H__
#define __ASYNC_LOG_H__

#include <stdio.h>
#include <string>
#include <list>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

//#ifdef LOG_EXPORTS
//#define LOG_API __declspec(dllexport)
//#else
//#define LOG_API __declspec(dllimport)
//#endif

#define LOG_API

enum LOG_LEVEL
{
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,    //锟斤拷锟斤拷业锟斤拷锟斤拷锟�
    LOG_LEVEL_SYSERROR, //锟斤拷锟节硷拷锟斤拷锟斤拷鼙锟斤拷锟斤拷拇锟斤拷锟�
    LOG_LEVEL_FATAL,    //FATAL 锟斤拷锟斤拷锟斤拷锟街撅拷锟斤拷锟斤拷诔锟斤拷锟斤拷锟斤拷锟斤拷志锟斤拷锟剿筹拷
    LOG_LEVEL_CRITICAL  //CRITICAL 锟斤拷志锟斤拷锟斤拷锟斤拷志锟斤拷锟斤拷锟斤拷疲锟斤拷锟斤拷锟斤拷锟斤拷
};


#define LOGT(...)    CAsyncLog::Output(LOG_LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOGD(...)    CAsyncLog::Output(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOGI(...)    CAsyncLog::Output(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOGW(...)    CAsyncLog::Output(LOG_LEVEL_WARNING, __FILE__, __LINE__,__VA_ARGS__)
#define LOGE(...)    CAsyncLog::Output(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGSYSE(...) CAsyncLog::Output(LOG_LEVEL_SYSERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOGF(...)    CAsyncLog::Output(LOG_LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)        //为锟斤拷锟斤拷FATAL锟斤拷锟斤拷锟斤拷锟街撅拷锟斤拷锟斤拷锟絚rash锟斤拷锟津，诧拷取同锟斤拷写锟斤拷志锟侥凤拷锟斤拷
#define LOGC(...)    CAsyncLog::Output(LOG_LEVEL_CRITICAL, __FILE__, __LINE__, __VA_ARGS__)     //锟截硷拷锟斤拷息锟斤拷锟斤拷锟斤拷锟斤拷志锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�

//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷莅锟斤拷亩锟斤拷锟斤拷聘锟绞�
#define LOG_DEBUG_BIN(buf, buflength) CAsyncLog::OutputBinary(buf, buflength)

class LOG_API CAsyncLog
{
public:
    static bool Init(const char* pszLogFileName = nullptr, bool bTruncateLongLine = false, int64_t nRollSize = 10 * 1024 * 1024);
	static void Uninit();

    static void SetLevel(LOG_LEVEL nLevel);
    static bool IsRunning();
	
	//锟斤拷锟斤拷锟斤拷叱锟絀D锟脚猴拷锟斤拷锟节猴拷锟斤拷签锟斤拷锟斤拷锟叫猴拷
	static bool Output(long nLevel, const char* pszFmt, ...);
	//锟斤拷锟斤拷叱锟絀D锟脚猴拷锟斤拷锟节猴拷锟斤拷签锟斤拷锟斤拷锟叫猴拷	
    static bool Output(long nLevel, const char* pszFileName, int nLineNo, const char* pszFmt, ...);

    static bool OutputBinary(unsigned char* buffer, size_t size);

private:
    CAsyncLog() = delete;
    ~CAsyncLog() = delete;

    CAsyncLog(const CAsyncLog& rhs) = delete;
    CAsyncLog& operator=(const CAsyncLog& rhs) = delete;

    static void MakeLinePrefix(long nLevel, std::string& strPrefix);
    static void GetTime(char* pszTime, int nTimeStrLength);
    static bool CreateNewFile(const char* pszLogFileName);
    static bool WriteToFile(const std::string& data);
    //锟矫筹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    static void Crash();

    static const char* ullto4Str(int n);
    static char* FormLog(int& index, char* szbuf, size_t size_buf, unsigned char* buffer, size_t size);

    static void WriteThreadProc();
	
private:
	static bool		                        m_bToFile;			    //锟斤拷志写锟斤拷锟侥硷拷锟斤拷锟斤拷写锟斤拷锟斤拷锟斤拷台  
	static FILE*                            m_hLogFile;
    static std::string                      m_strFileName;          //锟斤拷志锟侥硷拷锟斤拷
    static std::string                      m_strFileNamePID;    //锟侥硷拷锟斤拷锟叫的斤拷锟斤拷id
    static bool                             m_bTruncateLongLog;     //锟斤拷锟斤拷志锟角凤拷囟锟�
    static LOG_LEVEL                        m_nCurrentLevel;        //锟斤拷前锟斤拷志锟斤拷锟斤拷
    static int64_t                          m_nFileRollSize;        //锟斤拷锟斤拷锟斤拷志锟侥硷拷锟斤拷锟斤拷锟斤拷纸锟斤拷锟�
    static int64_t                          m_nCurrentWrittenSize;  //锟窖撅拷写锟斤拷锟斤拷纸锟斤拷锟侥�
    static std::list<std::string>           m_listLinesToWrite;     //锟斤拷写锟斤拷锟斤拷锟街�
    static std::shared_ptr<std::thread>     m_spWriteThread;
    static std::mutex                       m_mutexWrite;
    static std::condition_variable          m_cvWrite;
    static bool                             m_bExit;                //锟剿筹拷锟斤拷志
    static bool                             m_bRunning;             //锟斤拷锟叫憋拷志
};

#endif // !__ASYNC_LOG_H__