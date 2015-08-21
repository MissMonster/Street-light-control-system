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
struct Data_Param    //���ݿ��������
{
    string db_name;    //���ݿ���
    string tab_name;    //����
    string col_name;    //����
    string select_exp;    //ѡ����ʽ
    string where_def;    //ѡ���޶�����
    string insert_val;    //����ֵ
    string set_exp;    //�������ݿ����ݵı��ʽ
	Data_Param(string db_name,string tab_name,string where,string select_exp)
	{
		this->db_name = db_name;
		this->tab_name = tab_name;
		this->where_def = where;
		this->select_exp = select_exp;
	}
};

struct Database_Param    //���ݿ����
{
    string host;    //������
    string user;    //�û���
    string password;    //����
    string db;    //���ݿ���
    unsigned int port;    //�˿ڣ�һ��Ϊ0
    const char* unix_socket;    //�׽��֣�һ��ΪNULL
    unsigned int client_flag;    //һ��Ϊ0
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
    string GetState();    //������״̬
    string GetServerInfo();    //��������Ϣ
    int GetProtocolInfo();    //Э����Ϣ
    string GetHostInfo();    //������Ϣ
    string GetClientInfo();    //�ͻ�����Ϣ
    string GetFieldName(int FieldNum);
    bool IsEnd();    //�Ƿ����
    void SeekData(int offset);    //����ָ������
    unsigned int GetFieldNum();        //�õ��ֶ���
    bool ConnectDB(Database_Param* p);    //�������ݿ�
    MYSQL_ROW GetRecord();    //�õ������һ����¼��
    my_ulonglong GetRowNum();    //�õ���¼��
    bool SelectDB(Data_Param* para);    //ѡ�����ݿ�
    bool UpdateRecord(Data_Param* para);    //���¼�¼
    bool SelectRecord(Data_Param* para);    //ѡ���¼
    bool SelectRecord_1(Data_Param* para);    //ѡ���¼
    bool InsertRecord(Data_Param* para);    //�����¼
    bool DelRecord(Data_Param* para);        //ɾ����¼
    bool SelectAll(Data_Param* para);        //ѡ�����м�¼
	bool executeSQL(CString strSQL);
    string OutErrors();        //���������Ϣ
    bool MysqlEx(MYSQL* mysql, string str); 
	bool FindSave(string str);    //���Ҳ���������
	int getInsertID();
    CMysql();
    virtual ~CMysql();
private:
    
private:
    MYSQL mysql;    //���ݿ����Ӿ��
    MYSQL_FIELD* field;    //�ֶ���Ϣ���ṹ�壩
public:
    MYSQL_RES* query;    //�����
    MYSQL_ROW row;    //��¼��
};

#endif
#endif // !defined(AFX_MYSQL_H__77BD4C2E_CBED_4EBE_A66C_5DC890A41F5D__INCLUDED_)
