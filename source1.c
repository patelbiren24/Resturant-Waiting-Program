#include "header.h"

//Function used in the base file that will call addToList function
void doAdd (LIST* l, boolean debugMode){
 
 int size = getPosInt();  /* get group size from input */

 if (size < 1){
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

 /* get group name from input */
 char *name = getName();
 boolean check;
 if (NULL == name){
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

 printf ("Adding group \"%s\" of size %d\n", name, size);

 // add code to perform this operation here
 check = doesNameExist(l, name); //first check for duplicate name
 
  if(check == FALSE){
    addToList(l, name, size, YES, debugMode); //add to list with YES in restauraunt status
  }
 
 else{
    printf("Error: group name already exists in queue\n"); //if duplicate name print error
 }
}

// Add group to queue but as a called ahead group
void doCallAhead (LIST *l, boolean debugMode){
 
 int size = getPosInt();  /* get group size from input */
 boolean check;
 
 if (size < 1){
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

 /* get group name from input */
 char *name = getName();
 if (NULL == name){
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

 printf ("Call-ahead group \"%s\" of size %d\n", name, size);

 check = doesNameExist(l, name ); // Check for duplicate name
  if(check == FALSE){
    addToList(l, name, size, NO, debugMode); // Add to list with a NO in restauraunt status
  }
 else{
    printf("Error: group name already exists in queue\n"); //print error for duplicate name
 }

}

// Will change a call ahead groups status to in the restauraunt
void doWaiting (LIST *l, boolean debugMode){

 char *name = getName();  /* get group name from input */
 boolean check;
 if (NULL == name){
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
  }

 printf ("Waiting group \"%s\" is now in the restaurant\n", name);

 // add code to perform this operation here
 check =  doesNameExist(l, name); //make sure theyre on the list
 if(check == TRUE){
     updateStatus(l, name, debugMode); //change from NO to YES
     return;
  }
 else{
     printf("Error:  group name not part of the queue\n");
     return;
 }
}


// Function that will seat the groups calling the retrieveAndRemove function
void doRetrieve (LIST *l, boolean debugMode){
 /* get table size from input */
 int size = getPosInt();
 char *name;
 if (size < 1){
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
  }
 
 clearToEoln();
 
 printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

 // add code to perform this operation here
 name = retrieveAndRemove(l,size, debugMode); //Find first group that fits at the table 
 if(name != NULL){
    printf("Seating group %s\n", name); //print what group were seating
    free(name); //make sure to free that name array since were never using it again
  }
 else{
    printf("ERROR: No group in queue with size that will fit at table\n");    
 }
}


// Print sizes and names of the groups that are ahead of the group with the query
void doList (LIST *l, boolean debugMode){
 /* get group name from input */
 char *name = getName();
 boolean check;
 if (NULL == name){
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
  }

 printf ("Group \"%s\" is behind the following groups\n", name);

 // add code to perform this operation here
 check = doesNameExist(l, name); //check if name is even in list
  if(check == TRUE){
     int count = countGroupsAhead(l, name, debugMode); //count the groups
     printf("There are %d groups ahead of group %s\n", count, name); //print how many groups are ahead 
     displayGroupSizeAhead(l, name, count); //print the sizes of the group
  }
 else{
    printf("ERROR: name not in the queue\n");
 }

}

// Print the content of the queue, will print everyone that is in queue. Sizes and status and names
void doDisplay (LIST *l){
 clearToEoln();
 printf ("Display information about all groups\n");

 // add code to perform this operation here
  if(!(listIsEmpty(l))){  //Check if the list is empty first
     printf("Queue is empty!\n");
     return;
  }
 displayListInformation(l);  //Otherwise display the list information
}
