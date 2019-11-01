//
// Created by lzy on 10/31/19.
//

#include "../../myChatserver/mysqlmgr/MysqlManager.h"
#include "gtest/gtest.h"

TEST(sqlTest,Unitest)
{
    CMysqlManager c;
    c.Init("127.0.0.1","myuser","mypassword","test");

    assert(c._IsDBExist()== true);
    for (auto it:c.getMVecTables())
    {
        printf("%s\n" ,it.m_strName.c_str());
    }


}