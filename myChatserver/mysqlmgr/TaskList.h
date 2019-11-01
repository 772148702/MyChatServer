//
// Created by lzy on 10/31/19.
//

#ifndef SERVER_TASKLIST_H
#define SERVER_TASKLIST_H

#include <cstdint>
#include "MysqlTask.h"

#define  MAX_NUMBER_TASK 1000

class CTaskList {
public:
    CTaskList(void);
    virtual  ~CTaskList();
    bool push(IMysqlTask *pTask);
    IMysqlTask* pop();

private:
    uint16_t  m_uReadIndex;
    uint16_t  m_uWriteIndex;
    IMysqlTask* m_pTaskNode[MAX_NUMBER_TASK];
};


#endif //SERVER_TASKLIST_H
