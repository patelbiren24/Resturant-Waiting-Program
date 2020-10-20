/* 
 * Header file for the program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list LIST; //Deine list struct as LIST
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean; //enums

LIST* list_create(); //create an empty lit
void lst_free(LIST *l); //free memory of list
void addToList(LIST *l, char *name, int size, boolean status,boolean debugMode); //add group to list
boolean doesNameExist(LIST *l, char *name); //check if name exists
boolean updateStatus(LIST *l, char *name, boolean debugMode); //update call ahead groups to in restauraunt
char* retrieveAndRemove(LIST *l, int tablesize, boolean debugMode); //seat groups
int countGroupsAhead(LIST *l, char* name, boolean debugMode); //count groups ahead of group asking for info
void displayGroupSizeAhead(LIST *l, char* name, int count); //print the groups sizes too
void displayListInformation(LIST* l); //print all the information in the queue
boolean listIsEmpty(LIST *l); //check if the queue is empty
void doAdd(LIST *l, boolean debugMode);  //calls addToList
void doCallAhead(LIST *l, boolean debugMode); //calls addToList but as a call ahead group
void doWaiting(LIST *l, boolean debugMode); //change call ahead group
void doRetrieve(LIST *l, boolean debugMode); //calls retrieveAndRemove
void doList(LIST* l, boolean debugMode); //calls displayGroupSizeAhead and displayListInformation
void doDisplay(LIST* l); //calls displayListInformation
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printComands();
