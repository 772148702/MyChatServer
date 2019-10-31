//
// Created by lzy on 10/30/19.
//

#pragma  once
#include "mysqlapi/DatabaseMysql.h"
#include <vector>
#include <map>

struct STableFiled
{
    STableFiled(){}
    STableFiled(std::string strName,std::string strType, std::string strDesc):m_strName(strName),m_strType(strType),m_strDesc(strDesc){}
    std::string m_strName;
    std::string m_strType;
    std::string m_strDesc;
};

struct STableInfo
{
    STableInfo() {}
    STableInfo(std::string strName):m_strName(strName){}
    std::string m_strName;
    std::map<std::string, STableFiled> m_MapFields;
    std::string m_strPriKey;
};


class CMysqlManager {


public:
    CMysqlManager();


public:
    const string &getMStrHost() const;

    const string &getMStrUser() const;

    const string &getMStrPassword() const;

    const string &getMStrDatabase() const;

    const string &getMStrCharacterSet() const;


protected:

    std::shared_ptr<CDatabaseMysql> m_ptrConn;
    std::string m_strHost;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDatabase;
    std::string m_strCharacterSet;
    std::vector<STableInfo>   m_vecTables;

};



