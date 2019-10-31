//
// Created by lzy on 10/30/19.
//

#include <sstream>
#include <base/AsyncLog.h>
#include "MysqlManager.h"

const string &CMysqlManager::getMStrHost() const {
    return m_strHost;
}

const string &CMysqlManager::getMStrUser() const {
    return m_strUser;
}

const string &CMysqlManager::getMStrPassword() const {
    return m_strPassword;
}

const string &CMysqlManager::getMStrDatabase() const {
    return m_strDatabase;
}

const string &CMysqlManager::getMStrCharacterSet() const {
    return m_strCharacterSet;
}

CMysqlManager::CMysqlManager() {
    m_strCharacterSet = "UTF-8";

    //user table
    {
        STableInfo info;
        info.m_strName = "t_user";
        info.m_mapField["f_id"]= {"f_id","bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)" };
        info.m_mapField["f_user_id"] = { "f_user_id", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
        info.m_mapField["f_username"] = { "f_username", "varchar(64) NOT NULL COMMENT '用户名'", "varchar(64)" };
        info.m_mapField["f_nickname"] = { "f_nickname", "varchar(64) NOT NULL COMMENT '用户昵称'", "varchar(64)" };
        info.m_mapField["f_password"] = { "f_password", "varchar(64) NOT NULL COMMENT '用户密码'", "varchar(64)" };
        info.m_strPriKey = "PRIMARY KEY (f_user_id), INDEX f_user_id (f_user_id), KEY  f_id  ( f_id )";
        m_vecTables.push_back(info);
    }

    {
        STableInfo info;
        info.m_strName = "t_user_relationship";
        info.m_mapField["f_id"] =  { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
        info.m_mapField["f_user_id1"] = { "f_user_id1", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
        info.m_mapField["f_user_id2"] = { "f_user_id2", "bigint(20) NOT NULL COMMENT '用户ID'", "bigint(20)" };
        info.m_mapField["f_user1_teamname"] = { "f_user1_teamname", "VARCHAR(32) NOT NULL DEFAULT 'My Friends' COMMENT '用户2在用户1的好友分组名称'", "VARCHAR(32)" };
        info.m_mapField["f_user2_teamname"] = { "f_user2_teamname", "VARCHAR(32) NOT NULL DEFAULT 'My Friends' COMMENT '用户1在用户2的好友分组名称'", "VARCHAR(32)" };
        info.m_mapField["f_user1_markname"] = { "f_user1_markname", "VARCHAR(32) COMMENT '用户2在用户1的备注名称'", "VARCHAR(32)" };
        info.m_mapField["f_user2_markname"] = { "f_user2_markname", "VARCHAR(32) COMMENT '用户1在用户2的备注名称'", "VARCHAR(32)" };
        info.m_mapField["f_update_time"] = { "f_update_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
        info.m_strPriKey = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
        m_vecTables.push_back(info);
    }
    {
        STableInfo chat;
        chat.m_mapField["f_id"] = { "f_id", "bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'", "bigint(20)" };
        chat.m_mapField["f_senderid"] = { "f_senderid", "bigint(20) NOT NULL COMMENT '发送者id'", "bigint(20)" };
        chat.m_mapField["f_targetid"] = { "f_targetid", "bigint(20) NOT NULL COMMENT '接收者id'", "bigint(20)" };
        chat.m_mapField["f_msgcontent"] = { "f_msgcontent", "BLOB NOT NULL COMMENT '聊天内容'", "BLOB" };
        chat.m_mapField["f_create_time"] = { "f_create_time", "timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间'", "timestamp" };
        chat.m_mapField["f_remark"] = { "f_remark", "varchar(64) NULL COMMENT '备注'", "varchar(64)" };

        chat.m_strPriKey = "PRIMARY KEY (f_id), INDEX f_id (f_id)";
        m_vecTables.push_back(chat);
    }
}

CMysqlManager::~CMysqlManager() {

}

bool CMysqlManager::Init(const char *host, const char *user, const char *pwd, const char *dbname) {

     m_strHost = host;
     m_strUser = user;
     m_strPassword = pwd;
     m_strDatabase = dbname;
     m_ptrConn.reset(new CDatabaseMysql());
     if(!m_ptrConn->Initialize(m_strHost,m_strUser,m_strPassword,""))
     {
         return false;
     }

     if(!_IsDBExist())
     {
         if(!_CreateDB())
         {
             return false;
         }
     }

    m_ptrConn.reset(new CDatabaseMysql());
    if (!m_ptrConn->Initialize(m_strHost, m_strUser, m_strPassword, m_strDatabase))
    {
        //LOG_FATAL << "CMysqlManager::Init failed, please check params(" << m_strHost << ", " << m_strUser
        //	<< ", " << m_strPassword << ", " << m_strDataBase << ")";
        return false;
    }

    for(auto it:m_vecTables)
    {
        if(!_CheckTable(it))
        {
            return false;
        }
    }
    return true;
}

bool CMysqlManager::_IsDBExist() {
    if(m_ptrConn==NULL)
    {
        return false;
    }
     QueryResult* pResult =  m_ptrConn->Query("show databases");
    if(pResult==NULL)
    {
        return false;
    }
    Field * pRow = pResult->Fetch();
    while(pRow!=NULL)
    {
        string name = pRow[0].GetString();
        if(name==m_strDatabase)
        {
            return true;
        }
        if(pResult->NextRow()==NULL)
        {
            break;
        }
        pRow = pResult->Fetch();
    }
    pResult->EndQuery();
    delete pResult;
    return false;
}

bool CMysqlManager::_CreateDB() {
    if(m_ptrConn==NULL)
    {
        return false;
    }
    uint32_t unAffectedCount = 0;
    int nErrno = 0;
    stringstream ss;
    ss<<"create database "<<m_strDatabase;
    if(m_ptrConn->Execute(ss.str().c_str(),unAffectedCount, nErrno))
    {
        if(unAffectedCount==1) return true;
    } else
    {
        return false;
    }
    return false;
}

bool CMysqlManager::_CheckTable(const STableInfo &table) {
    if(m_ptrConn==NULL)
    {
        return false;
    }

    if(table.m_strName.find_first_not_of("\t\n\r")==string::npos)
    {
        return true;
    }

    stringstream ss;
    ss<<"desc "<<table.m_strName;
    QueryResult* pResult = m_ptrConn->Query(ss.str().c_str());
    if(pResult==NULL)
    {
        if(_CreateTable(table))
        {
            return true;
        }
        return false;
    } else
    {
        std::map<std::string,std::string> oldMap;
        Field* pRow = pResult->Fetch();
        while(pRow!=NULL)
        {
            string name = pRow[0].GetString();
            string type = pRow[1].GetString();
            oldMap[name] = type;
            if(pResult->NextRow()==false)
            {
                break;
            }
            pRow = pResult->Fetch();
        }
        pResult->EndQuery();
        delete pResult;
        for(auto it: table.m_mapField)
        {
            STableFiled field = it.second;
            if(oldMap.find(field.m_strName)==oldMap.end())
            {
                stringstream ss;
                ss<<"alter table "<<table.m_strName<<" add column "
                <<field.m_strName<<" "<<field.m_strType;

                string sql =ss.str();
                if(m_ptrConn->Execute(sql.c_str()))
                {
                    return true;
                } else
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool CMysqlManager::_CreateTable(const STableInfo &table) {
        if(table.m_mapField.size()==0)
        {
            return false;
        }
        stringstream ss;
        ss<<"CREATE TABLE IF NOT EXISTS "<<table.m_strName<<" ( ";
        int i=0;
        for(auto it : table.m_mapField)
        {
          if(i!=0)
          {
              ss<<" , ";
              i++;
          }
          STableFiled field = it.second;
          ss<< field.m_strName<<"  "<<field.m_strType;

        }
        if( table.m_strPriKey!="")
        {
            ss<<", "<<table.m_strPriKey;
        }
        ss<<")default charset = utf-8, ENGINE=InnoDB";
        if(m_ptrConn->Execute(ss.str().c_str()))
        {
            return true;
        }

        LOGE("Create table error, sql: %s", ss.str().c_str());
        return false;
}

bool CMysqlManager::_UpdateTable(const STableInfo &table) {
    return false;
}



