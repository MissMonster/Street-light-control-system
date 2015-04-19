// Mysql.h: interface for the Mysql class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQL_H__490AFEB2_0AAD_4908_B3D0_8579C04B93A7__INCLUDED_)
#define AFX_MYSQL_H__490AFEB2_0AAD_4908_B3D0_8579C04B93A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef CMYSQL_H
#define CMYCQL_H

#include <winsock.h>
#include "mysql/mysql.h"
#include <sstream>
#include <string>

using std::string;
struct Data_Param    //数据库操作参数
{
    string db_name;    //数据库名
    string tab_name;    //表名
    string col_name;    //列名
    string select_exp;    //选择表达式
    string where_def;    //选择限定条件
    string insert_val;    //插入值
    string set_exp;    //更新数据库内容的表达式
	Data_Param(string db_name,string tab_name,string where,string select_exp)
	{
		this->db_name = db_name;
		this->tab_name = tab_name;
		this->where_def = where;
		this->select_exp = select_exp;
	}
};

struct Database_Param    //数据库参数
{
    string host;    //主机名
    string user;    //用户名
    string password;    //密码
    string db;    //数据库名
    unsigned int port;    //端口，一般为0
    const char* unix_socket;    //套接字，一般为NULL
    unsigned int client_flag;    //一般为0
    Database_Param(string host, string user, string password, string db, unsigned int port, const char* unix_socket, unsigned int client_flag)
    {
        this->host = host;
        this->user = user;
        this->password = password;
        this->db = db;
        this->port = port;
        this->unix_socket = unix_socket;
        this->client_flag = client_flag;
    }
};

class CMysql
{
public:
    string GetState();    //服务器状态
    string GetServerInfo();    //服务器信息
    int GetProtocolInfo();    //协议信息
    string GetHostInfo();    //主机信息
    string GetClientInfo();    //客户机信息
    string GetFieldName(int FieldNum);
    bool IsEnd();    //是否最后
    void SeekData(int offset);    //查找指定数据
    unsigned int GetFieldNum();        //得到字段数
    bool ConnectDB(Database_Param* p);    //连接数据库
    MYSQL_ROW GetRecord();    //得到结果（一个记录）
    my_ulonglong GetRowNum();    //得到记录数
    bool SelectDB(Data_Param* para);    //选择数据库
    bool UpdateRecord(Data_Param* para);    //更新记录
    bool SelectRecord(Data_Param* para);    //选择记录
    bool SelectRecord_1(Data_Param* para);    //选择记录
    bool InsertRecord(Data_Param* para);    //插入记录
    bool DelRecord(Data_Param* para);        //删除记录
    bool SelectAll(Data_Param* para);        //选择所有记录
	bool executeSQL(CString strSQL);
    string OutErrors();        //输出错误信息
    bool MysqlEx(MYSQL* mysql, string str); 
	bool FindSave(string str);    //查找并保存结果集
	int getInsertID();
    CMysql();
    virtual ~CMysql();
private:
    
private:
    MYSQL mysql;    //数据库链接句柄
    MYSQL_FIELD* field;    //字段信息（结构体）
public:
    MYSQL_RES* query;    //结果集
    MYSQL_ROW row;    //记录集
};

#endif
#endif // !defined(AFX_MYSQL_H__77BD4C2E_CBED_4EBE_A66C_5DC890A41F5D__INCLUDED_)
