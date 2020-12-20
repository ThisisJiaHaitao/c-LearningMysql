//g++ mysql.cc -o test `mysql_config --cflags --libs`

#include<iostream>
#include<string.h>
#include<mysql/mysql.h>
using namespace std;
int main()
{
    MYSQL conn;
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "jia", "jht", "jht", 3306, NULL, 0))
    {
        cout << "connet error" << endl;
    }
    else
    {
        cout << "connet success" << endl;
    }

    //create table
   const char* pQuery="CREATE TABLE IF NOT EXISTS User(ID INT,Name VARCHAR(255),Age INT,PRIMARY KEY(ID))";
    if(mysql_real_query(&conn,pQuery,(uint)strlen(pQuery))!=0)
    {
        const char* pCh=mysql_error(&conn);
        cout<<pCh<<endl;
        return 1;
    }

    //insert data
    const char *query = "INSERT INTO User VALUE(2,'lsm',105)";
    if (mysql_real_query(&conn, query, (uint)strlen(query)))
    {
        cout << "error : " << mysql_error(&conn) << endl;
        return false;
    }

    //get data
    mysql_query(&conn, "set names gbk"); // set encoding format
   const  char *QQuery = "SELECT * FROM User";
    if (mysql_real_query(&conn, QQuery, (uint)strlen(QQuery)))
    {
        const char *pCh = mysql_error(&conn);
        cout << "ERROR : " << pCh << endl;
        return 1;
    }
    MYSQL_RES *res=mysql_store_result(&conn);
    if(res!=NULL)
    {
        unsigned int nCol=mysql_num_fields(res);//return column number
        MYSQL_ROW column;
        while(column=mysql_fetch_row(res))//get the next line
        {
            for(int c=0;c<nCol;c++)
            {
                cout << column[c] <<"  ";
            }
            cout<<endl;
        }
        mysql_free_result(res);
    }

    mysql_close(&conn);
    return 0;

}