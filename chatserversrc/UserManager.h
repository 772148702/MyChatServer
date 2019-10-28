#pragma once
#include <stdint.h>
#include <string>
#include <list>
#include <mutex>
#include <set>
#include <atomic>

using namespace std;
#define GROUPID_BOUBDARY 0xFFFFFFFF

#define DEFAULT_TEAMNAME "My Friends"

enum FRIEND_OPERATION
{
    FRIEND_OPERATION_ADD,
    FRIEND_OPERATION_DELETE
};

struct FriendInfo
{
    int32_t friendid;
    string markname;
    string teamname;
};

struct User
{
    int32_t userid;
    string username;
    string password;
    string nickname;
    int32_t facetype;
    string customface;
    string custofacefmt;
    int32_t gender;
    int32_t birthday;
    string  signature;
    string  address;
    string  phonenumber;
    string mail;
    string teaminfo;
    int32_t ownerid;
    list<FriendInfo> friends;
};

class UserManager final
{
    public:
        UserManager();
        ~UserManager();
        bool Init(const char* dbServer,const char* dbuserName,const char* dbPassword,const char* dbName);

        UserManager(const UserManager& rhs) = delete;
        UserManager& operator=(const UserManager& rhs) = delete;

        bool AddUser(User& u);
        bool MakeFriendRelationshipInDB(int32_t smallUserid,int32_t greaterUserid);
        bool ReleaseFriendRelationshipInDBAndMemory(int32_t smallUserid, int32_t greaterUserid);
    bool UpdateUserRelationshipInMemory(int32_t userid, int32_t target, FRIEND_OPERATION operation);
    bool AddFriendToUser(int32_t userid, int32_t friendid);
    bool DeleteFriendToUser(int32_t userid, int32_t friendid);

    bool IsFriend(int32_t userid, int32_t friendid);
    
    //TODO: 锟斤拷锟洁都锟角革拷锟斤拷锟矫伙拷锟斤拷息锟侥接口ｏ拷锟斤拷锟斤拷锟斤拷锟皆匡拷锟斤拷统一锟斤拷锟斤拷
    bool UpdateUserInfoInDb(int32_t userid, const User& newuserinfo);
    bool ModifyUserPassword(int32_t userid, const std::string& newpassword);
    //锟斤拷锟节达拷锟斤拷锟斤拷菘锟斤拷械锟侥筹拷锟斤拷没锟斤拷姆锟斤拷锟斤拷锟较拷某锟斤拷碌锟絥ewteaminfo
    bool UpdateUserTeamInfoInDbAndMemory(int32_t userid, const std::string& newteaminfo);
    bool DeleteTeam(int32_t userid, const std::string& deletedteamname);
    bool ModifyTeamName(int32_t userid, const std::string& newteamname, const std::string& oldteamname);
    
    //锟斤拷锟斤拷锟矫伙拷锟斤拷锟窖憋拷注锟斤拷
    bool UpdateMarknameInDb(int32_t userid, int32_t friendid, const std::string& newmarkname);
    //锟狡讹拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    bool MoveFriendToOtherTeam(int32_t userid, int32_t friendid, const std::string& newteamname);

    bool AddGroup(const char* groupname, int32_t ownerid, int32_t& groupid);

    //锟斤拷锟斤拷锟斤拷息锟斤拷锟�
    bool SaveChatMsgToDb(int32_t senderid, int32_t targetid, const std::string& chatmsg);

    //TODO: 锟斤拷锟矫伙拷越锟斤拷越锟洁，锟斤拷锟斤拷锟斤拷越锟斤拷越锟斤拷锟绞憋拷锟斤拷锟斤拷系锟叫的猴拷锟斤拷效锟绞革拷锟斤拷
    bool GetUserInfoByUsername(const std::string& username, User& u);
    bool GetUserInfoByUserId(int32_t userid, User& u);
    bool GetUserInfoByUserId(int32_t userid, User*& u);
    bool GetFriendInfoByUserId(int32_t userid, std::list<User>& friends);
    //锟斤拷取锟斤拷锟窖的憋拷注锟斤拷
    bool GetFriendMarknameByUserId(int32_t userid1, int32_t friendid, std::string& markname);
    bool GetTeamInfoByUserId(int32_t userid, std::string& teaminfo);

private:
    bool LoadUsersFromDb();
    bool LoadRelationshipFromDb(int32_t userid, std::list<FriendInfo>& r);

private:
    std::atomic_int     m_baseUserId{ 0 };        //m_baseUserId, 取锟斤拷锟捷匡拷锟斤拷锟斤拷userid锟斤拷锟街碉拷锟斤拷锟斤拷锟斤拷没锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟较碉拷锟斤拷
    std::atomic<int>    m_baseGroupId{0x0FFFFFFF};
    list<User>          m_allCachedUsers;
    mutex               m_mutex;

    string              m_strDbServer;
    string              m_strDbUserName;
    string              m_strDbPassword;
    string              m_strDbName;
};


