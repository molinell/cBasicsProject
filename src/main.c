#include "database.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {

    printf("*** Medals Database ***\n");

    MedalsDB *db = malloc(sizeof(MedalsDB));
    if(!db) {
        printf("ERROR: Failed to initialize database");
        return 1;
    }
    
    db->nations = NULL;
    db->len = 0;

    while (1) {   
        char cmd[1000];
        
        if(!fgets(cmd, sizeof(cmd), stdin)) {
            printf("ERROR: Failed to read command");
            continue;
       }

       if(!isalpha(cmd[0]) || !isspace(cmd[1])){
            printf("ERROR: Invalid command format %s", cmd);
            continue;
       }

        switch ((int)cmd[0]) {
            
        case 'A': {
            char name[500];
            if(sscanf(cmd, "%*c %s", name)  == 1) {
                if(addNation(name, db)) printf("SUCCESS\n");
            }
            else printf("ERROR: Invalid argument\n");
            break;
        }

        case 'M': {
            char name[500];
            int bronze, silver, gold;
            if(sscanf(cmd, "%*c %s %d %d %d", name, &gold, &silver, &bronze)  == 4){
                if(addMedals(name, gold, silver, bronze, db)) printf("SUCCESS\n");
            }
            else printf("ERROR: Invalid argument\n");
            break;
        }

        case 'L': {
            if(printDB(db, stdout)){
                printf("SUCCESS\n");
            }
            else printf("ERROR: Printing failed");
            break;
        }

        case 'W': {
            char src[500];
            if(sscanf(cmd, "%*c %s", src)  == 1){
                if(saveDB(src, db)) printf("SUCCESS\n");
            }
            else printf("ERROR: Invalid argument\n");
            break;
        }

        case 'O': {
            char src[500];
            if(sscanf(cmd, "%*c %s", src)  == 1){
                if(loadDB(src, db)) printf("SUCCESS\n");
            }
            else printf("ERROR: Invalid argument\n");
            break;
        }

        case 'Q': {
            freeDB(db);
            printf("SUCCESS\n");
            return 0;
        }

        case 'H': {
            printf("Usage: [CMD] [OPTIONS]\n\n");
            printf("Available commands:\n");
            printf("  A <nation_name>         - Add a new nation to the database.\n");
            printf("  M <nation_name> <gold> <silver> <bronze> - Add medals to a nation, negative values to remove.\n");
            printf("  L                       - List all nations and their medal counts.\n");
            printf("  W <filename>            - Save the database to a file.\n");
            printf("  O <filename>            - Load the database from a file.\n");
            printf("  Q                       - Quit the program.\n");
            printf("  H                       - Display this help message.\n");
            break;
        }

        default:
            printf("ERROR: Invalid command %c\n", cmd[0]);
            break;
        }
    }

    return 0;
}
