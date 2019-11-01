//
// Created by lzy on 10/31/19.
//

#include <memory>
#include <sstream>

#include "mysqlapi/DatabaseMysql.h"
#include "base/AsyncLog.h"
#include "UserManager.h"

UserManager::UserManager() {}

UserManager::~UserManager() {

}

bool UserManager::init(const char *dbServer, const char *dbUserName, const char *dbPassword, const char *dbName) {
     m_strDbServer = dbServer;
     m_strDbName = dbName;
     m_strDbUserName = dbUserName;
     m_strDbPassword = dbPassword;
     LoadUsersFromDb();
     return true;

}

bool UserManager::addUser(User &u) {
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
    return true;
}

bool UserManager::getUserInfoByUserId(int32_t userid, User &u) {
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
    u.userid = userid;
    u.username = pRow[0].GetString();
    u.nickname = pRow[1].GetString();
    u.password = pRow[2].GetString();
    return true;
}

bool UserManager::LoadUsersFromDb() {
    std::unique_ptr<CDatabaseMysql> pConn;
    pConn.reset(new CDatabaseMysql());
    if (!pConn->Initialize(m_strDbServer, m_strDbUserName, m_strDbPassword, m_strDbName))
    {
        LOGF("UserManager::LoadUsersFromDb failed, please check params: dbserver: %s, dbusername: %s, , dbpassword: %s, dbname: %s",
             m_strDbServer.c_str(), m_strDbUserName.c_str(), m_strDbPassword.c_str(), m_strDbName.c_str());
        return false;
    }
    QueryResult* pResult = pConn->Query("SELECT f_user_id  FROM t_user ORDER BY  f_user_id DESC");
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

