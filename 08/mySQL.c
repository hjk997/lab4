/*MySQL 서버 및 클라이언트 프로그램을 설치하고 익숙해지도록 사용해 본다.*/
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    MYSQL_RES* res;
    char fields;
    MYSQL mysql;
    MYSQL_ROW row;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "1895", NULL, 0, (char *)NULL, 0))
    {
        printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        exit(1);
    }
    if (mysql_query(&mysql, "use TEST")) { 
        printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql)); 
        exit(1); 
    } 
    if (mysql_query(&mysql, "select * from student")) { 
        printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql)); 
        exit(1); 
    } 
    res = mysql_use_result(&mysql);
    fields = mysql_num_fields(res);
    printf("Total student is as follows.\n");
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; ++i) {
            printf("%12s ", row[i]);
        }
        printf("\n");
    } 
    mysql_close(&mysql);
    return 0;
}
