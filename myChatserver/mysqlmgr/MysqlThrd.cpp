//
// Created by lzy on 10/31/19.
//

#include "MysqlThrd.h"

CMysqlThrd::CMysqlThrd(void) {
    m_bStart = false;
    m_bTerminal = false;
    m_poConn = NULL;
}
CMysqlThrd::~CMysqlThrd() {

}
void CMysqlThrd::run() {
    mainLoop();
    uninit();

    if (NULL != m_pThread)
    {
        m_pThread->join();
    }
}

bool CMysqlThrd::start(const std::string &host, const std::string &user, const std::string &password,
                       const std::string &dbname) {
    m_poConn  = new CDatabaseMysql();
    if(m_poConn==NULL) return false;

    if (m_poConn->Initialize(host, user, password, dbname) == false) return false;

    init();
}

void CMysqlThrd::stop() {
    if(m_bTerminal) {
        return ;
    }
    m_bTerminal = true;
    m_pThread->join();
}

bool CMysqlThrd::init() {
   if(m_bStart)
   {
       return true;
   }

   m_pThread.reset(new std::thread(std::bind(&CMysqlThrd::mainLoop,this)));
   std::unique_lock<std::mutex> lock(m_mu);
   while(m_bStart==false)
   {
       m_cond.wait(lock);
   }
   return true;

}

void CMysqlThrd::mainLoop() {
    m_bStart = true;
    {
        std::unique_lock<std::mutex> lock(m_mu);
        m_cond.notify_all();
    }

    IMysqlTask* pTask;
    while(!m_bTerminal)
    {
        if(NULL!=(pTask=m_oTask.pop()))
        {
            pTask->Execute(m_poConn);
            m_oReplyTask.push(pTask);
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void CMysqlThrd::uninit() {

}
