//
// Created by lzy on 10/31/19.
//

#include <memory>
#include <sstream>

#include "mysqlapi/DatabaseMysql.h"
#include "base/AsyncLog.h"
#include "UserManager.h"
#define  SQL_LENGTH 256
void getUserFrompRow(int32_t userid, User& user,Field* pRow)
{
    user.userid = userid;
    user.username = pRow[0].GetString();
    user.nickname = pRow[1].GetString();
    user.password = pRow[2].GetString();
}

bool UserManager::getMysqlDatabasePtr( std::unique_ptr<CDatabaseMysql>& pConn,string functionName)
{
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGE("UserManager::%s failed, please check params: dbserver: %s, , dbusername: %s, dbpassword: %s, dbname: %s",functionName.c_str(),m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    return true;
}
UserManager::UserManager() {}

UserManager::~UserManager() {

}

bool UserManager::init(const char *dbServer, const char *dbUserName, const char *dbPassword, const char *dbName) {
     m_strDbServer = dbServer;
     m_strDbName = dbName;
     m_strDbUserName = dbUserName;
     m_strDbPassword = dbPassword;
     m_ptrListUsers.reset(new list<User>());
     loadUsersFromDb();
     return true;

}

bool UserManager::addUser(User u) {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGE("UserManager::AddUser failed, please check params: dbserver: %s, , dbusername: %s, dbpassword: %s, dbname: %s", m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    ++m_baseUserId;

    char sql[256] = {0};
    snprintf(sql,256,"INSERT INTO t_user(f_user_id,f_username,f_nickname,f_password,f_register_time)  VALUES(%d, '%s', '%s', '%s', NOW())"
    ,m_baseUserId.load(), u.username.c_str(), u.nickname.c_str(), u.password.c_str());
    printf("%s\n",sql);
    if(!pConn->Execute(sql))
    {
        LOGW("insert user error,sql %s",sql);
        return false;
    }
    u.userid = m_baseUserId;

    m_ptrListUsers->push_back(u);
    return true;
}

bool UserManager::getUserInfoByUserIdInMemory(int32_t userid, User &u) {
    list<User> ListUser = *(m_ptrListUsers);
    for (auto user: ListUser)
    {
        if(userid==user.userid)
        {
            u= user;
            return true;
        }
    }
    return false;
}

bool UserManager::loadUsersFromDb() {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGF("UserManager::LoadUsersFromDb failed, please check params: dbserver: %s, dbusername: %s, , dbpassword: %s, dbname: %s",
             m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    QueryResult* pResult = pConn->Query("SELECT f_user_id, f_username,f_nickname,f_password  FROM t_user ORDER BY  f_user_id DESC");
    if (NULL == pResult)
    {
        LOGI("UserManager::_Query error, dbname: %s", m_strDbName.c_str());
        return false;
    }

    string teaminfo;
    while (true)
    {
        Field* pRow = pResult->Fetch();
        if (pRow == NULL)
            break;

        User u;
        u.userid = pRow[0].GetInt32();
        u.username = pRow[1].GetString();
        u.nickname = pRow[2].GetString();
        u.password = pRow[3].GetString();
        loadFriendInfoFromDb(u.userid,u.friends);
        m_ptrListUsers->push_back(std::move(u));
        LOGI("userid: %d, username: %s, password: %s, nickname: %s, signature: %s", u.userid, u.username.c_str(), u.password.c_str(), u.nickname.c_str());


        if (u.userid < GROUPID_BOUBDARY && u.userid > m_baseUserId)
            m_baseUserId = u.userid;

        if (u.userid > GROUPID_BOUBDARY && u.userid > m_baseGroupId)
            m_baseGroupId = u.userid;

        if (!pResult->NextRow())
        {
            break;
        }
    }

    LOGI("current base userid: %d, current base group id: %d", m_baseUserId.load(), m_baseGroupId.load());

    pResult->EndQuery();

    delete pResult;

    return true;
}

bool UserManager::getUserInfoByUserIdInDb(int32_t userid, User &u) {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        return false;
    }
    stringstream ss;
    ss<<"select  f_username, f_nickname, f_password from t_user where f_user_id = "<< userid;
    const char* sql = ss.str().c_str();
    printf("%s",sql);
    QueryResult* pResult = pConn->Query(sql);

    Field* pRow = pResult->Fetch();
    if(pRow==NULL)
    {
        LOGE("UserManager::getUserInfoByUserId find user with userid=%d failed",userid);
        return false;
    }
    getUserFrompRow(userid,u,pRow);

    return true;
}

bool UserManager::addFriendInfoDb(int32_t smallUserid, int32_t bigUserid, string smallMarkName, string biMarkName, string smallTeamName,string bigTeamName) {
//    stringstream ss;
//    std::unique_ptr<CDatabaseMysql> pConn;
//    if(!getMysqlDatabasePtr(pConn,"addFriendDb"))
//    {
//        return false;
//    }
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {

        LOGF("UserManager::addFriendInfoDb failed, please check params: dbserver: %s, dbusername: %s, , dbpassword: %s, dbname: %s",
             m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    char sql[256];
    snprintf(sql,256,"INSERT INTO t_user_relationship(f_user_id1,f_user_id2,f_user1_markname,f_user2_markname,f_user1_teamname,f_user2_teamname) Values(%d,%d,'%s','%s','%s','%s')",smallUserid,bigUserid,
             smallMarkName.c_str(),biMarkName.c_str(),smallTeamName.c_str(),bigTeamName.c_str());
    printf("%s\n",sql);

    if(!pConn->Execute(sql)) {
        LOGE("UserManager::addFriendDb %s",sql);
        return false;
    }
    return true;
}

bool
UserManager::updateFriendInfo(int32_t smallUserid, int32_t bigUserid, string markname, string teamname, bool isSwap) {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGF("UserManager::updateFriendInfo failed, please check params: dbserver: %s, dbusername: %s, , dbpassword: %s, dbname: %s",
             m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    char sql[SQL_LENGTH];
    if(!isSwap)
    {
        snprintf(sql,SQL_LENGTH,"UPDATE t_user_relationship SET f_user1_markname='%s', f_user1_teamnae='%s' where f_user1_id = %d and f_user2_id=%d"
        ,markname.c_str(),teamname.c_str(),smallUserid,bigUserid);
    } else
    {
        snprintf(sql,SQL_LENGTH,"UPDATE t_user_relationship SET f_user2_markname='%s', f_user2_teamnae='%s' where f_user1_id = %d and f_user2_id=%d"
                ,markname.c_str(),teamname.c_str(),smallUserid,bigUserid);
    }
    if(!pConn->Execute(sql))
    {
        LOGE("UserManager::updateFriendInfo %s",sql);
        return false;
    }
    return true;
}

bool UserManager::getFriendInfo(int32_t userid, list<FriendInfo> &friendsInfo) {
    loadFriendInfoFromDb(userid,friendsInfo);
}

const shared_ptr<std::list<User>> &UserManager::getMPtrListUsers() const {
    return m_ptrListUsers;
}

bool UserManager::loadFriendInfoFromDb(int32_t userid, list<FriendInfo>& r) {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGF("UserManager::loadFriendInfoFromDb failed, please check params: dbserver: %s, dbusername: %s, , dbpassword: %s, dbname: %s",
             m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    char sql[SQL_LENGTH];
    snprintf(sql,SQL_LENGTH,"select f_user_id1, f_user_id2, f_user1_markname, f_user1_teamname, f_user2_name, f_user_teamname from t_user_relationship where "
                            "f_user_id1=%d OR f_user_id2=%d",userid,userid);

    QueryResult* pResult = pConn->Query(sql);

    while(true)
    {
        Field * pRow = pResult->Fetch();
        if(pRow==NULL) break;
        int32_t  userid1 = pRow[0].GetInt32();
        int32_t  userid2 = pRow[1].GetInt32();
        string   user1_markname = pRow[2].GetString();
        string   user1_teamname = pRow[3].GetString();
        string   user2_markname = pRow[4].GetString();
        string   user2_teamname = pRow[5].GetString();
        FriendInfo f;
        if(userid==userid1)
        {
            f.friendid = userid2;
            f.markname = user2_markname;
            f.teamname = user2_teamname;
        } else
        {
            f.friendid = userid1;
            f.markname = user1_markname;
            f.teamname = user1_teamname;
        }
        r.emplace_back(f);
        if(!pResult->NextRow())
        {
            break;
        }
        pRow = pResult->Fetch();
    }
    return true;

}
