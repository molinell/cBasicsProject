#ifndef _DATABASE_
#define _DATABASE_

#include <stdio.h>

/**
 * @brief Structure for containing name and medals of a nation
 * 
 */
typedef struct nation_st
{
    char* name; //name of the nation
    int gold; //medals
    int silver;
    int bronze;
} Nation;

/**
 * @brief Structure for the database containing the nations
 * 
 */
typedef struct medalsDB_st
{
    Nation *nations; //array of nations
    int len; //lenght of database
} MedalsDB;



/**
 * @brief Adds a nation to the database
 * 
 * @param name the name of the nation
 * @param db the database to add to
 * @return 0 on failure, 1 on success
 */
int addNation(char* name, MedalsDB *db);

/**
 * @brief Adds / updates medals to a nation
 * 
 * Sets the medal count to zero if the amount medals to be removed 
 * is greater than the amount of medals in the database
 * 
 * @param name the nation
 * @param gold amount of gold medals
 * @param silver amount of silver medals
 * @param bronze amount of bronze medals
 * @param db the database to use
 * @return 0 on failure, 1 on success
 */
int addMedals(char* name, int gold, int silver, int bronze, MedalsDB* db);

/**
 * @brief Prints the database in the order determined by \ref compare
 * 
 * @param db the database which should be printed
 * @param stream the output stream to print to (e.g stdout, text file)
 */
int printDB(MedalsDB *db, FILE *stream);

/**
 * @brief Loads a database from file
 * 
 * @param src the name / path of the file to read from
 * @param db the database which to load into
 * @return 0 on failure, 1 on success
 */
int loadDB(char* src, MedalsDB *db);

/**
 * @brief Saves a database to file
 * 
 * @param src the name of the file to write to
 * @param db the database which is to be saved
 * @return 0 on failure, 1 on success
 */
int saveDB(char* src, MedalsDB *db);

/**
 * @brief Used to sort the database
 * 
 * sorts by:
 *  1. gold medals
 *  2. silver medals
 *  3. bronze medals
 * 
 * Applied using qsort
 * 
 * @param a Nation to be compared
 * @param b Nation to be compared
 * @return the order
 */
int compare(const void *a, const void *b);

/**
 * @brief Helper function to initialise a nations values ("constructor")
 * 
 * @param nat The nation to be initialised
 * @param name Name of the nation
 * 
 * The number of medals:
 *      @param gold 
 *      @param silver 
 *      @param bronze 
 * 
 * @return 0 on failure, 1 on success
 */
int initialiseNation(Nation *nat, char* name, int gold, int silver, int bronze);

/**
 * @brief Frees all memory allocated to the database
 * 
 * @param db the database to be freed
 */
void freeDB(MedalsDB *db);

#endif //! _DATABSE_
