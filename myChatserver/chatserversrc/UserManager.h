//
// Created by lzy on 10/31/19.
//

#ifndef SERVER_USERMANAGER_H
#define SERVER_USERMANAGER_H

#include <cstdint>
#include <string>
#include <list>
#include <atomic>
#include <ostream>

#define GROUPID_BOUBDARY   0x0FFFFFFF

#define DEFAULT_TEAMNAME  "My Friends"
using namespace std;

enum FRIEND_OPERATION
{
    FRIEND_OPERATION_ADD,
    FRIEND_OPERATION_DELETE
};

struct  FriendInfo
{
    int32_t friendid;
    string markname;
    string teamname;
};

struct User
{
    int32_t  userid;
    string   username;
    string   password;
    string   nickname;

    string teaminfo;
    int32_t  ownerid;
    list<FriendInfo> friends;


};

class UserManager final{

public:
    UserManager();

    virtual ~UserManager();

    bool init(const char* dbServer, const char* dbUserName, const char* dbPassword, const char* dbName);
    UserManager(const UserManager& rhs) = delete;
    UserManager& operator=(const UserManager& rhs) = delete;

    bool addUser(User& u);
    bool getUserInfoByUserId(int32_t userid, User& u);
    bool LoadUsersFromDb();

private:
    std::atomic_int    m_baseUserId{0};
    std::atomic<int>   m_baseGroupId{0x0FFFFFFF};

    string m_strDbServer;
    string m_strDbUserName;
    string m_strDbPassword;
    string m_strDbName;
};


#endif //SERVER_USERMANAGER_H
