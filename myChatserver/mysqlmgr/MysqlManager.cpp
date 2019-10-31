//
// Created by lzy on 10/30/19.
//

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
        info.m_strName = "t_user"
        info.m_MapFields["f_id"]= {"f_id","bigint(20) NOT NULL AUTO_INCREMENT COMMENT '自增ID'","bigint(20)" };

    }
}
