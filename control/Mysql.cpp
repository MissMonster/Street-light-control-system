// Mysql.cpp: implementation of the Mysql class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LampServer.h"
#include "Mysql.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using std::ostringstream;

CMysql::CMysql()
{
    mysql_init(&mysql);
}

CMysql::~CMysql()
{
    mysql_close(&mysql);
}

//Connect to the DB host
bool CMysql::ConnectDB(Database_Param* p)
{
    if(!mysql_real_connect(&mysql,(p->host).c_str(),p->user.c_str(),p->password.c_str(),p->db.c_str(),p->port,p->unix_socket,p->client_flag))
    {
        return false;
    }
	mysql_query(&mysql,"set names gbk");//设置为中文
    return true;
}

//Select DB
bool CMysql::SelectDB(Data_Param* para)
{
    if(mysql_select_db(&mysql,para->db_name.c_str()))
        return false;
    else
        return true;
}

//Get the record and store it int 'row'
MYSQL_ROW CMysql::GetRecord()
{
    return (row=mysql_fetch_row(query));
}

bool CMysql::executeSQL(CString strSQL)
{
	try
	{
		if(mysql_query(&mysql,strSQL))
		{
			return false;
		}
	}
	catch (CException* e)
	{
		return false;
	}

    return true;
}

//A utility to select all the records
bool CMysql::SelectAll(Data_Param* para)
{
    unsigned int i=0;
    ostringstream Ostr;
    Ostr << "select * from " << para->tab_name;
    if(!FindSave(Ostr.str()))
    {
        return false;
    }
    return true;
}

//Seek the row 
void CMysql::SeekData(int offset)
{
    mysql_data_seek(query,offset);
}

//Execute the query and store the results in 'query'
bool CMysql::FindSave(string str)
{
	try
	{
		if(mysql_query(&mysql,str.c_str()))
			return false;
		query=mysql_store_result(&mysql);
		return true;
	}

	catch (...)
	{
		return false;
	}
   
}

//A utility to delete the records
bool CMysql::DelRecord(Data_Param* para)
{
    ostringstream Ostr;
    Ostr << "delete from " << para->tab_name << " where " << para->where_def;
    if(mysql_query(&mysql,Ostr.str().c_str()))
    {
        return false;
    }
    return true;
}

//A utility to insert records
bool CMysql::InsertRecord(Data_Param* para)
{
    ostringstream Ostr;
    Ostr << "insert into " << para->tab_name << " values(" << para->insert_val << ")";
    if(mysql_query(&mysql,Ostr.str().c_str()))
    {
        return false;
    }
    return true;
}

//A utility to select records
bool CMysql::SelectRecord(Data_Param* para)
{
    unsigned int i=0;
    ostringstream Ostr;
    Ostr << "select " << para->select_exp << " from " << para->tab_name << " where " << para->where_def;
    if(!FindSave(Ostr.str()))
    {
        return false;
    }
    return true;
}
bool CMysql::SelectRecord_1(Data_Param* para)
{
    unsigned int i=0;
    ostringstream Ostr;
    Ostr << "select " << para->select_exp << " from " << para->tab_name;
    if(!FindSave(Ostr.str()))
    {
        return false;
    }
    return true;
}

//A utility to update records
bool CMysql::UpdateRecord(Data_Param* para)
{
    ostringstream Ostr;
    Ostr << "update " << para->tab_name << " set " << para->set_exp << " where " << para->where_def;
    if(mysql_query(&mysql,Ostr.str().c_str()))
    {
        return false;
    }
    return true;
}


bool CMysql::IsEnd()
{
    if(mysql_eof(query))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CMysql::getInsertID()
{
	return mysql_insert_id(&mysql);
}
//Get number of rows
my_ulonglong CMysql::GetRowNum()
{
    return (mysql_num_rows(query));
}

unsigned int CMysql::GetFieldNum()
{
    return (mysql_num_fields(query));
}

//Get the name of the FieldNumth Field
string CMysql::GetFieldName(int FieldNum)
{
    field=mysql_fetch_field_direct(query,FieldNum);
    return string(field->name);
}

string CMysql::GetClientInfo()
{
    return string(mysql_get_client_info());
}

string CMysql::GetServerInfo()
{
    return string(mysql_get_server_info(&mysql));
}

string CMysql::GetHostInfo()
{
    return string(mysql_get_host_info(&mysql));
}

int CMysql::GetProtocolInfo()
{
    return mysql_get_proto_info(&mysql);
}

string CMysql::GetState()
{
    string state(mysql_stat(&mysql));
    if(!state.empty())
        return string(OutErrors());
    return state;
}

/*void CMysql::FreeRecord()
{
    mysql_free_result(query);
}*/

string CMysql::OutErrors()
{
    return string(mysql_error(&mysql));
}


bool CMysql::MysqlEx(MYSQL* mysql, string str)
{
    if(!FindSave(str))
    {
        return false;
    }
    return true;
}


