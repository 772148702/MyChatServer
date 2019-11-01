//
// Created by lzy on 10/31/19.
//

#ifndef SERVER_MYSQLTASK_H
#define SERVER_MYSQLTASK_H

enum EMysqlError {
    EME_ERROR = -1,
    EME_OK,
    EME_NOT_EXSIT,
    EME_EXIST
};

class CDatabaseMysql;

class IMysqlTask {
public:
    IMysqlTask(void);

    virtual ~IMysqlTask();

public:
    virtual  void execute(CDatabaseMysql* pConn) = 0;
    virtual  void reply() = 0;
    virtual void  release() {
        delete  this;
    }
};


#endif //SERVER_MYSQLTASK_H
