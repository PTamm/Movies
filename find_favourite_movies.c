#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char *argv[]){
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc;
    int col;
    char *sql_stmt;


    rc = sqlite3_open(argv[1], &db);

    if (rc){
        fprintf(stderr,"Can't open database: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sql_stmt = "select title from movies;";

    rc = sqlite3_prepare_v2(db,sql_stmt,-1,&stmt,0);

    if (rc != SQLITE_OK){
        fprintf(stderr,"Preparation failed: %s\n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    /*
        Now we print the output ...
    */

    while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        for (col = 0; col < sqlite3_column_count(stmt); col++){
            printf("%s",sqlite3_column_text(stmt,col));
        }
        printf("\n");
    }

    sqlite3_finalize(stmt);

    return 0;
}
