#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *data, int argc, char** argv, char **azColName) {
    int *recordCount = (int *)data;
    *recordCount = atoi(argv[0]);
    return 0;
}

int main(void) {
    sqlite3* db;
    char *errmsg;
    int rc;

    if(rc = sqlite3_open("test.db", &db)!=SQLITE_OK) {
        fprintf(stderr, "__%d__:Cannot open database!\n", __LINE__);
        return -1;
    }

    char sql[30] = "select count(*) from Students;";
    int recordCount = 0; // 表中的数据数目

    if(sqlite3_exec(db, sql, callback, &recordCount, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "__%d__ : %s", __LINE__, errmsg);
        return -1;
    }
    sqlite3_close(db);
    printf("表中已有%d个数据\n",recordCount);

}
