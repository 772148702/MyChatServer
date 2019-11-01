//
// Created by lzy on 10/31/19.
//

#include <myChatserver/chatserversrc/UserManager.h>
#include <base/Singleton.h>
#include <myChatserver/mysqlmgr/MysqlManager.h>
#include "gtest/gtest.h"



TEST(UserManagerAdd,UNITTEST)
{
    UserManager u;
    Singleton<CMysqlManager>::Instance().Init("127.0.0.1", "root", "root", "test");
    ASSERT_TRUE(u.init("127.0.0.1","root","root","test"));
    User user;

    user.username="fds";
    user.nickname="dsds";
    user.password="123";
    ASSERT_TRUE(u.addUser(user));
    ASSERT_TRUE(u.addUser(user));
    ASSERT_TRUE(u.addUser(user));
}

TEST(UserManagerFind,UNITTEST)
{
    UserManager u;
    Singleton<CMysqlManager>::Instance().Init("127.0.0.1", "root", "root", "test");
    ASSERT_TRUE(u.init("127.0.0.1","root","root","test"));
    User user;
    user.userid=1;
    user.password = "21231";

    u.getUserInfoByUserId(1,user);
    printf("\n%d %s %s %s\n",user.userid,user.username.c_str(),user.nickname.c_str(),user.password.c_str());
    cout<<"\n"<<user.username<<user.nickname;
}