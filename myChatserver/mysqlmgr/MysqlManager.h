//
// Created by lzy on 10/30/19.
//

#pragma  once
#include "mysqlapi/DatabaseMysql.h"
#include <vector>
#include <map>
#include <memory>

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
    std::map<std::string, STableFiled> m_mapField;
    std::string m_strPriKey;
};


class CMysqlManager {


public:
    CMysqlManager();

    virtual ~CMysqlManager();

    bool Init(const char* host, const char* user, const char* pwd, const char* dbname);

public:
    const string &getMStrHost() const;

    const string &getMStrUser() const;

    const string &getMStrPassword() const;

    const string &getMStrDatabase() const;

    const string &getMStrCharacterSet() const;

    bool _IsDBExist();
    bool _CreateDB();
    bool _CheckTable(const STableInfo& table);
    bool _CreateTable(const STableInfo& table);
    bool _UpdateTable(const STableInfo& table);
protected:

    std::shared_ptr<CDatabaseMysql> m_ptrConn;
    std::string m_strHost;
    std::string m_strUser;
    std::string m_strPassword;
    std::string m_strDatabase;
    std::string m_strCharacterSet;
    std::vector<STableInfo>   m_vecTables;

};



