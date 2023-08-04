#include <stdio.h>
#include <sqlite3.h>

int main(void) {
    sqlite3 *db;
    char *errmsg=NULL;
    char **result=NULL;
    int row = 0, column = 0;
    
    // 打开数据库
    if(sqlite3_open("test.db", &db) != SQLITE_OK) {
        fprintf(stderr, "__%d__ : ", __LINE__);
        perror("sqlite3_open");
        sqlite3_close(db);
        return -1;
    }

    // 执行查询语句
    char *sql = "SELECT *FROM Students;";
    if(sqlite3_get_table(db, sql, &result, &row, &column, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "__%d__ : %s\n", __LINE__, errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return -1;
    }

    // 输出查询结果
    printf("Query return %d rows and %d columns\n", row, column);
    for(int i = 0; i <= row; i++) {
        for(int j = 0; j < column; j++) {
            printf("%s\t", result[i * column + j]);
        }
        printf("\n");
    }

    sqlite3_free_table(result);
    sqlite3_close(db);
    return 0;

}
