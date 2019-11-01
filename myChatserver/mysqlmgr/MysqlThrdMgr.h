//
// Created by lzy on 10/31/19.
//

#ifndef SERVER_MYSQLTHRDMGR_H
#define SERVER_MYSQLTHRDMGR_H


#include <string>
#include "MysqlThrd.h"

#include "MysqlTask.h"

class CMysqlThrdMgr {
public:
    CMysqlThrdMgr(void);
    virtual ~CMysqlThrdMgr();

public:
    bool init(const std::string& host, const std::string& user, const std::string& pwd, const std::string& dbname);
    bool addTask(uint32_t dwHashID, IMysqlTask* poTask);
    bool addTask(IMysqlTask* poTask)
    {
        return m_aoMysqlThreads[m_dwThreadsCount].addTask(poTask);
    }
    inline uint32_t getTableHashID(uint32_t dwHashID) const
    {
        return dwHashID % m_dwThreadsCount;
    }

    bool processReplyTask(int32_t nCount);
    static uint32_t getThreadsCount()
    {
        return m_dwThreadsCount;
    }
protected:
    static  const uint32_t  m_dwThreadsCount=9;
    CMysqlThrd              m_aoMysqlThreads[m_dwThreadsCount+1];

};


#endif //SERVER_MYSQLTHRDMGR_H
