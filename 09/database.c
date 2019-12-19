/*MySQL 서버 및 클라이언트 프로그램을 설치하고 익숙해지도록 사용해 본다.*/
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

char tel[20];
char addr[20];
char buffer[100];



void ent()
{
    printf("\n");
}

void get_data(){
    printf("PHONE-NUMBER : ");
    scanf("%s", tel);
    printf("ADDRESS : ");
    scanf("%s", addr);
}

int main()
{
    MYSQL_RES *res;
    char fields;
    MYSQL mysql;
    MYSQL_ROW row;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "1895", NULL, 0, (char *)NULL, 0))
    {
        printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        exit(1);
    }
    if (mysql_query(&mysql, "use TEST"))
    {
        printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
        exit(1);
    }
    printf("전화번호, 주소 관리 시스템입니다.\n");
    while (1)
    {
        char buf[50];
        int menu;
        printf("1 : 데이터베이스 조회 2 : 데이터 삽입 3 : 데이터 삭제\n");
        printf("메뉴를 입력하세요 : ");
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            ent();
            ent();
            if (mysql_query(&mysql, "select * from manage"))
            {
                printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
                exit(1);
            }
            res = mysql_use_result(&mysql);
            fields = mysql_num_fields(res);
            printf("Total info is as follows.\n");
            while ((row = mysql_fetch_row(res)))
            {
                for (int i = 0; i < fields; ++i)
                {
                    printf("%12s ", row[i]);
                }
                printf("\n");
            }
            ent();
            ent();

            break;
        case 2:
            ent();
            get_data();
            sprintf(buffer, "insert into manage values(\"%s\",\"%s\");", tel, addr);

            if (mysql_query(&mysql, buffer)) {
                    printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
                    exit(1);
                }
                printf("생성이 완료되었습니다.\n");
            ent();
            break;
        case 3:
                ent();
                char tel[20];
                printf("삭제할 전화번호를 입력해 주세요!\n");
                printf("PHONE-NUMBER : ");
                scanf("%s", tel);
                sprintf(buffer, "delete from manage where tel = '%s'", tel);
                if (mysql_query(&mysql, buffer)) {
                    printf("Error %d: %s\n", mysql_errno(&mysql), mysql_error(&mysql));
                    exit(1);
                }
                printf("삭제가 완료되었습니다.\n");
                ent();
                break;
            break;
        default:
            printf("잘못 입력했습니다. 종료합니다.\n\n");
            exit(1);
            break;
        }
    }
    mysql_close(&mysql);
    return 0;
}

/*

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

*/