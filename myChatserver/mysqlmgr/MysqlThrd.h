//
// Created by lzy on 10/31/19.
//

#ifndef SERVER_MYSQLTHRD_H
#define SERVER_MYSQLTHRD_H

#include <condition_variable>
#include <bits/unique_ptr.h>
#include <thread>
#include <mysqlapi/DatabaseMysql.h>
#include <mutex>
#include "TaskList.h"

class CMysqlThrd {
public:
    CMysqlThrd(void);
    virtual ~CMysqlThrd();

    void run();
    bool start(const std::string &host, const std::string &user,const std::string& password,const std::string& dbname);
    void stop();

    bool addTask(IMysqlTask* pTask) {
        return m_oTask.push(pTask);
    }

    IMysqlTask* getReplyTask(void) {
        return m_oReplyTask.pop();
    }

protected:
    bool init();
    void mainLoop();
    void uninit();

private:
    bool m_bTerminal;
    std::unique_ptr<std::thread> m_pThread;
    bool m_bStart;
    CDatabaseMysql* m_poConn;
    CTaskList   m_oTask;
    CTaskList   m_oReplyTask;

    std::mutex  m_mu;
    std::condition_variable m_cond;

};


#endif //SERVER_MYSQLTHRD_H
