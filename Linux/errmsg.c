#include <stdio.h>
#include <sqlite3.h>
int callback();

int main(int argc, char* argv[]) {
    sqlite3 *db;
    char *errmsg = NULL;
    
    // 打开数据库
    int rc = sqlite3_open("test.db", &db);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    // 创建表格
    char *sql = "CREATE TABLE IF NOT EXISTS Students("
                "ID INT PRIMARY KEY NOT NULL,"
                "NAME TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    
    // 插入数据
    sql = "INSERT INTO Students (ID, NAME) VALUES (1, 'Alice');";
    rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    
    // 查询数据
    sql = "SELECT * FROM Students;";
    rc = sqlite3_exec(db, sql, callback, NULL, &errmsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    
    sqlite3_close(db);
    return 0;
}

int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
