#include "header.h"

/* Node struct will be hidden in this file, all function
  calls will be done with the LIST typedef outside of
  this source file.  Even though the functions will be
  accessing information at a NODE level, the user doesnt
  know that. */

typedef struct node{
   char *name;
   int size;
   boolean status;
   struct node* next;
}NODE;


/* List struct here, the prototype is defined in the header file */
struct list{
    NODE* head;
};


/* Create an empty list and return it */
LIST* list_create(){
    LIST *l = (LIST*)malloc(sizeof(LIST));
    l->head = NULL;
    return l;
}



void displayNode(NODE* p); //prototype for displaying a single node


/*  Function that will free groups in the queue if the user
  quits the program before seating everyone.
 */
void lst_free(LIST *l) {

NODE *p = l->head;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p->name);  //make sure to free the char array first
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}


/* Add a group of size x and with name y to the queue.  Also 
  will decide here if the user called ahead or is in the restaurant
 */
void addToList(LIST *l, char *name, int size, boolean status, boolean debugMode){
    NODE *walker = l->head; // pointer to walk through list
    NODE *group = (NODE*)malloc(sizeof(NODE)); //create new node
    group->name = name;
    group->size = size;
    group->status = status;
    group->next = NULL;
    
    if(l->head == NULL){ // Base case if list is originally empty
        l->head = group;
        return;
    }
    
    while(walker != NULL){
        if(walker->next == NULL){ // If the next node is NULL it means were at the end
            if(debugMode == TRUE){ //debugging information
                displayNode(walker);
            }
            walker->next = group; //make the link
            return;
        }
        else{
            if(debugMode == TRUE){
                displayNode(walker); //debugging information
            }
            walker = walker->next; //go to next node on list
        }
    }
}


/* Function that will traverse the queue searching if the name exists
  the function is case sensistive so there is a difference between
  "Biren" and "biren".
 */
boolean doesNameExist(LIST *l,char *name){
    NODE* walker = l->head;
    while(walker != NULL){
        if(strcmp(name, walker->name)==0) //if a match is found
            return TRUE; //return true
        else{
            walker = walker->next; //go to next node
        }
    }
    return FALSE; //never found a match so name isnt in list
}


/* Function that will change a caller's position to being
  in the restauraunt.  will check if the name is already
  in the restauraunt first
 */
boolean updateStatus(LIST *l, char *name, boolean debugMode){
    NODE* walker = l->head;
    
    while(walker != NULL){
        if(strcmp(name, walker->name)==0){
            if(walker->status == YES){ //check if the user is already in the restaurant
                return FALSE;
            }
            else{
                walker->status = YES; //change to in the restaurant
                return TRUE;
            }
        }
        else{
            if(debugMode == TRUE){
                displayNode(walker); //debugging information
            }
            walker = walker->next;
        }
    }
    return FALSE; //somehow manage get to here? then there's an error somewhere
}


/* Function for seating groups at the table, will traverse through the 
  queue and find a group that is IN the restaurant and will fit at
  the table, then it will remove them from the queue and return
  the name of the group were seating.
 */
char* retrieveAndRemove(LIST *l, int tablesize, boolean debugMode){
    NODE* walker = l->head;
    NODE* lagWalker;
    char* returnString;
    
    while(walker != NULL){
      if(walker->status == YES){  
        if(walker->size <= tablesize){
            if(walker == l->head){ //Base case is were seating the group at the front of the queue
                l->head = l->head->next; // next node on list will be head 
                returnString = walker->name;
                free(walker); //free node
                return returnString; //return name
            }
            else{ //otherwise it was some group in the middle of the list so we need a lagging pointer to make the connection
                lagWalker->next = walker->next; //previous node will now link over current node
                returnString = walker->name; 
                free(walker); //free node
                return returnString; //return name
            }

        }
        else{ //current node is larger than what the table can fit go to next node
            if(debugMode == TRUE){
                displayNode(walker);
            } 
           lagWalker = walker; //lagWalker will always be behind one node
           walker = walker->next;
        }
      }
      else{ //current node is not even in the restaurant go next
          if(debugMode == TRUE){
              displayNode(walker);
          }
          lagWalker = walker;
          walker = walker->next;
      }
    }
    returnString = NULL;
    return returnString; //Never found a group so return a NULL
}


/* Function that will count how many groups are ahead of X name
  group. Will only count the groups that are in the restaurant
  so call ahead groups that have not arrived yet are not counted
 */

int countGroupsAhead(LIST* l, char* name, boolean debugMode){
    int count = 0; //initialize count
    NODE* walker = l->head;
    while(walker != NULL){
        if(strcmp(walker->name, name)==0)  //reached group
            return count; //return count
        else{
            if(debugMode == TRUE){
                displayNode(walker);
            }
            if(walker->status == YES){
                count++; //increment count
            }
            walker = walker->next;
        }
    }
    return 0; //if theyre the front of the group no one is ahead 
}


/*  Function that will return the sizes of the group ahead of X
   named group.  Will only return the sizes of the groups that are
   even in the restaurant so people that called ahead but are still
   not in the restaurant are not even counted.
 */

void displayGroupSizeAhead(LIST *l, char* name, int count){
    NODE *walker = l->head;
    if(walker != NULL && count > 0){
        printf("Of sizes: "); //formatting
    }
    while(walker != NULL){
        if(strcmp(walker->name,name)==0){
            printf("\n");
            return; // return 
        }
        else{
            if(walker->status == YES){
                 printf("%d ", walker->size); //print sizes of in restaurant groups
            }
            walker = walker->next;
        }
    }
}


/* Function that will display all the information in the queue.
  Will give the user the status of the groups, the sizes, and the names of the group
 */
void displayListInformation(LIST* l){
    NODE *walker = l->head;
    char status1[] = "IN RESTAURAUNT";
    char status2[] = "NOT IN RESTAURAUNT";
    char *status;
    while(walker != NULL){
        if(walker->status == YES){ //check for groups status
            status = status1;
        }
        else{
            status = status2;
        }
        printf("Group Name: %s", walker->name); //print name
        printf("   Size: %d", walker->size); //size of group
        printf("   Status: %s\n", status); //in restauraunt status
        walker = walker->next;
    }
}


//Function to check if the list is empty, needed for outside of file list checks
boolean listIsEmpty(LIST *l){
    if(l->head == NULL)
        return FALSE;
    else
        return TRUE;
}


//Debugging helper that will display group information at a NODE level
void displayNode(NODE* p){
    char status1[] = "IN RESTAURAUNT";
    char status2[] = "NOT IN RESTAURAUNT";
    char *status;
    if(p->status == YES){
        status = status1;
    }
     else{
        status = status2;
     }
     printf("Group Name: %s", p->name);
     printf("   Size: %d", p->size);
     printf("   Status: %s\n", status);
}
