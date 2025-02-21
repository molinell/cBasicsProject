#include "database.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int addNation(char* name, MedalsDB *db) {

    if(db->len > 0){ //has entries
        for(int i = 0; i < db->len; i++){
            if(strcmp(name, db->nations[i].name) == 0) {
                printf("ERROR: Nation already exists in database\n");
                return 0;
            }
        }
    }

    Nation *temp = realloc(db->nations, (db->len + 1) * sizeof(Nation));
    if(!temp) {
        printf("ERROR: Failed to add nation\n");
        return 0;
    }
    db->nations = temp;

    if(!initialiseNation(&db->nations[db->len], name, 0, 0, 0)) {
        printf("ERROR: Failed to add nation\n");
        return 0;
    }

    db->len++;

    return 1;
}


int addMedals(char* name, int gold, int silver, int bronze, MedalsDB* db) {

    if(db->len == 0) {
        printf("ERROR: Empty database, add a nation first\n");
        return 0;
    }

    for (int i = 0; i < db->len; i++) {
        if(strcmp(name, db->nations[i].name) == 0) {

                if(db->nations[i].bronze < abs(bronze) && bronze < 0) db->nations[i].bronze = 0; //removing more medals than there are
                else db->nations[i].bronze += bronze;

                if(db->nations[i].silver < abs(silver) && silver < 0) db->nations[i].silver = 0;
                else db->nations[i].silver += silver;

                if(db->nations[i].gold < abs(gold) && gold < 0) db->nations[i].gold = 0;
                else db->nations[i].gold += gold;

                return 1;
        }
    }

    printf("ERROR: Nation not found\n");
    return 0;
}


int printDB(MedalsDB *db, FILE *stream) {
    if(db->len == 0) return 1;

    qsort(db->nations, db->len, sizeof(Nation), compare);

    for(int i = 0; i < db->len; i++) {
        if(fprintf(stream, "%s %d %d %d\n", db->nations[i].name, db->nations[i].gold, db->nations[i].silver, db->nations[i].bronze) < 0){
            return 0;
        }
    }

    return 1;
}

int loadDB(char* src, MedalsDB *db) {
    FILE *f = NULL;
    f = fopen(src, "r");

    if(!f) {
        printf("ERROR: file couldn't be opened\n");
        return 0;
    }

    int retVal = 1;
    MedalsDB tempDB = {NULL, 0};
    char line[500];

    while(fgets(line, 500, f) != NULL) {
        int gold, silver, bronze;
        char name[100];

       if(sscanf(line, "%s %d %d %d", name, &gold, &silver, &bronze) == 4) {
            Nation *newNation = realloc(tempDB.nations, (tempDB.len + 1) * sizeof(Nation));

            if(!newNation) {
                retVal = 0;
                break;
            }
            tempDB.nations = newNation;

            if(!initialiseNation(&tempDB.nations[tempDB.len], name, gold, silver, bronze)) {
                retVal = 0;
                break;
            }

            tempDB.len++;
       }
       else {
            retVal = 0;
            break;
       }
    } 
    fclose(f);

    if(retVal == 0) { //failed to load all nations from file, aborting
        printf("ERROR: failed to load database\n");

        for(int i = 0; i < tempDB.len; i++) free(tempDB.nations[i].name); 
        free(tempDB.nations);
    } 
    else { //replacing existing database with the one from file
        for(int i = 0; i < db->len; i++) {
            free(db->nations[i].name);
        }

        free(db->nations);
        db->nations = tempDB.nations;
        db->len = tempDB.len;
    }
   
    return retVal;
}


int saveDB(char* src, MedalsDB *db) {
    FILE *f = NULL;
    f = fopen(src, "w");

    if(!f){
        printf("ERROR: file couldn't be opened\n");
        fclose(f);
        return 0;
    }

    if(!printDB(db, f)){
        printf("ERROR: writing to file failed");
        fclose(f);
        return 0;
    }

    fclose(f);
    return 1;
}

int compare(const void *a, const void *b) {
    const Nation *nA = (const Nation*) a;
    const Nation *nB = (const Nation*) b;

    if(nA->gold != nB->gold) return (nB->gold - nA->gold );
    if(nA->silver != nB->silver) return (nB->silver - nA->silver);
    if(nA->bronze != nB->bronze) return (nB->bronze - nA->bronze);

    return 0;
}

int initialiseNation(Nation *nat, char* name, int gold, int silver, int bronze){
    
    nat->name = malloc(strlen(name)+1);
    if(!nat->name) return 0;
    strcpy(nat->name, name);

    nat->gold = gold;
    nat->silver = silver;
    nat->bronze = bronze;

    return 1;
}

void freeDB(MedalsDB *db) {
    for(int i = 0; i < db->len; i++){
        free(db->nations[i].name);
    }

    free(db->nations);
    free(db);
}
