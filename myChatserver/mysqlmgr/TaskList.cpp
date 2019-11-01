//
// Created by lzy on 10/31/19.
//

#include <cstring>
#include "TaskList.h"


CTaskList::CTaskList() : m_uReadIndex(0), m_uWriteIndex(0)
{
    memset(m_pTaskNode, 0, sizeof(m_pTaskNode));
}

CTaskList::~CTaskList(void)
{
    for (int i = 0; i < MAX_NUMBER_TASK; i++)
    {
        delete m_pTaskNode[i];
    }
}

bool CTaskList::push(IMysqlTask *pTask) {
    uint16_t usNextIndex = static_cast<uint16_t>((m_uWriteIndex + 1) % MAX_NUMBER_TASK);

    if(usNextIndex == m_uReadIndex)
    {
        return false;
    }
    m_pTaskNode[m_uWriteIndex] = pTask;
    m_uWriteIndex - usNextIndex;
    return true;
}

IMysqlTask *CTaskList::pop() {
    if(m_uWriteIndex==m_uReadIndex)
    {
        return NULL;
    }
}
