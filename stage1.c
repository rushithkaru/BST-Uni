#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "head.h"
#define DATA_POINTS 18
#define MAX_BUFF 256
#define MAX_STRING 128

/*Function to read in data from the file */
struct data* data_read(int arg, char **argv, struct data *parent){
  /*Definintions*/
    parent = NULL;
    char *line = NULL;
    size_t lineBufferLength = 0;
    char *filename = NULL;
    filename = argv[1];
    struct data *temp = NULL;
    int n = 0,i,k = 0,j;
    char *temp_s = NULL;

    /*Opening of file with the taxi data*/
    FILE *p = fopen(filename,"r");
    assert(p != NULL);

    while(getline(&line,&lineBufferLength,p)>0){
    /*Creating a temporary struct of type data in order to store data for
    each line*/
    temp = (struct data*) malloc(sizeof(struct data));
    assert(temp);
      k = 0;
      /*Looping for the correct number of data points in order to find the
      length each specific field in the struct (using the get_length function)*/
        for(j = 0;j<DATA_POINTS;j++){
        n = get_length(&(line[k]));
        /*Creating a temporary string of size n+1 to store each field in the tem
poraray
        struct*/
        temp_s = (char *) malloc((n+1)*sizeof(char));
                 for(i=0;i<n;i++,k++){
                    temp_s[i] = line[k];
                  }
        temp_s[i] = '\0';
        /*Adding the string into the temp struct*/
        create(temp,temp_s,j+1,i);
        k++;
        free(temp_s);
        }
    /*Creating the binary search tree*/
    parent = bst_insert(parent,temp);
    free(temp);

    }

  free(line);
  fclose(p);

return parent;
}

/*FUnction to find the length of each string field from the input CSV file*/
int get_length(char *stri){
int n=0;
int i = 0;
/*Looping until comma or NULL byte is found*/
	while( stri[i] != ',' && stri[i] != '\0'){
    /*Also breaks if there is new line character*/
    if(stri[i] == '\n'){
      break;
    }
	  n++;
    i++;
	}

return n;

}

/*Function to create the temporary struct */
void create(struct data *temp, char *string, int field, int length){
//add all elements of the struct here

    if(field == 1){
      temp->Vendorid = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->Vendorid,string);

    }
    if(field == 2){
      temp->passengercount = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->passengercount,string);

    }
    if(field == 3){
      temp->trip_distance = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->trip_distance,string);
    }
    if(field == 4){
      temp->ratecode = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->ratecode,string);
    }
    if(field == 5){
      temp->store_flag = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->store_flag,string);
    }
    if(field == 6){
      temp->puloc = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->puloc,string);
    }

    if(field == 7){
      temp->doloc = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->doloc,string);
    }
    if(field == 8){
      temp->payment_t = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->payment_t,string);
    }
    if(field == 9){
      temp->fare = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->fare,string);
    }
    if(field == 10){
      temp->extra = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->extra,string);
    }
    if(field == 11){
      temp->mta_tax = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->mta_tax,string);
    }
    if(field == 12){
      temp->tip_tot = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->tip_tot,string);

    }
    if(field == 13){
      temp->tolls = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->tolls,string);
    }
    if(field == 14){
      temp->improv = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->improv,string);
    }
    if(field == 15){
      temp->amount = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->amount,string);
    }
    if(field == 16){
      temp->PUDT = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->PUDT,string);
    }
    if(field == 17){
      temp->Dudt = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->Dudt,string);
    }
    if(field == 18){
      temp->duration = (char*) malloc((length*sizeof(char))+1);
      strcpy(temp->duration,string);
    }
    temp->left = NULL;
    temp->right = NULL;
    temp->next = NULL;
}

/*Recursive binary search tree insertion function*/
struct data* bst_insert(struct data *parent, struct data *temp){
  struct data pass = *temp;
  if(!parent){
    parent = (struct data *) malloc(sizeof(struct data));
    parent->left = NULL;
    parent->right = NULL;
    parent->next = NULL;
    *parent = pass;

    return parent;
  }
/*Comparing the PUdatetime fields to see whether to go left, right or add/create
a linked list at the specific node*/
  else if (strcmp(temp->PUDT,parent->PUDT)<0) {
    parent->left = bst_insert(parent->left,&pass);
  }
  else if (strcmp(temp->PUDT,parent->PUDT)>0){
    parent->right = bst_insert(parent->right,&pass);
  }
  else{
    parent->next = bst_insert(parent->next,&pass);
  }
return parent;


}

/*Function to search the binary search tree given a PUdatetime string*/
void search(struct data *parent,char *key,char **argv){
  size_t lineBufferLength = MAX_STRING;
  char *new_key;

 /*Using the getline function to obtain the
  PUdatetime string from stdin*/
    while((getline(&key,&lineBufferLength,stdin)>0)){
      /*Allocating memory for new string
      in order to handle new line characters*/
      new_key = (char *) malloc(strlen(key)*sizeof(char));
      /*Calling function newline_rem to handle new line characters if found*/
      newline_rem(key,new_key);
      bst_search(parent,new_key,argv[2]);
      free(new_key);
    }
    free(key);
}

/*Function to handle new line charcters if found*/
void newline_rem(char *key,char *new_key){
  int i;

  /*Conditional state meant to handle the string if new line charcter is found*/
  if(key[strlen(key)-1] == '\n'){
    for(i=0;i<strlen(key)-1;i++){

      new_key[i] = key[i];
    }
    new_key[i] = '\0';
  }

  /*Conditional statement mean to handle
   the string if new line character not found*/
  else{
    for(i=0;i<strlen(key);i++){

      new_key[i] = key[i];
    }
    new_key[i] = '\0';
  }


}

/*Function that conducts the searching of keys in the BST*/
void bst_search(struct data *parent,char *key,char *outfile){

  /*Initialzing a static integere to count the number of comparisons*/
  static int comparisons = 0;
  /*test used for the output function to check if the key was found*/
  int test = 1;

    if(parent == NULL){
      test = 0;

      printf("%s --> %d\n",key,comparisons);
      file_out(outfile,parent,test,key);
      return;
    }
    /*Checking to see if strcmp return 0*/
    if(!strcmp(parent->PUDT,key)){
      comparisons++;
      output(parent->PUDT,comparisons);
      /*Outputing to the file*/
      file_out(outfile,parent,test,key);
      /*Once a key is found checking for linked list at the node to find the
      duplicate keys*/
        while(parent->next){
          parent = parent->next;
          /*Outputing to the file*/
          file_out(outfile,parent,test,key);
        }
        comparisons = 0;
        return;
    }
    /*Check for whether to go left or right in the search tree*/
    if(strcmp(parent->PUDT,key)<0){
      comparisons++;
      return bst_search(parent->right,key,outfile);
    }
    else{
      comparisons++;
      return bst_search(parent->left,key,outfile);
    }

}

/*Stdout output function*/
void output(char *key, int comparisons){
  printf("%s --> %d\n",key,comparisons);
}

/*Function to output the data to the output file*/
void file_out(char *file, struct data *node,int test, char *key){
  FILE *outfile = fopen(file,"a");
  assert(outfile != NULL);
  /*If test is true then the key was found in the BST*/
if (test){
  fprintf(
    outfile,
"%s --> VendorID: %s || passenger_count: %s || trip_distance: %s || RatecodeID:
%s || store_and_fwd_flag: %s || PULocationID: %s || DOLocationID: %s || payment_
type: %s || fare_amount: %s || extra: %s || mta_tax: %s || tip_amount: %s || tol
ls_amount: %s || improvement_surcharge: %s || total_amount: %s || DOdatetime: %s
 || trip_duration: %s ||\n",
   node->PUDT,node->Vendorid,node->passengercount,
   node->trip_distance,node->ratecode,node->store_flag,
   node->puloc,node->doloc,node->payment_t,node->fare,node->extra,
   node->mta_tax,node->tip_tot,node->tolls,node->improv,
   node->amount,node->Dudt,node->duration);
 }
 /*Printing not found*/
 else{
   fprintf(outfile,"%s --> NOTFOUND\n",key);
 }
 fclose(outfile);
}

/*Function to free the allocated memory for
the creation of the binary search tree*/
void free_parent(struct data *parent){

  if(parent == NULL){
    return;
  }

  free_parent(parent->left);
  /*Calling function to free the fields in the specific node*/
  if(parent){
  free_temp(parent);
}
/*Freeing the linked list in the node if there*/
  free_parent(parent->next);

  free_parent(parent->right);
  free(parent);

}

/*Function to free each field in the node allocated in the create function*/

void free_temp(struct data *temp){
  free(temp->Vendorid);
  free(temp->passengercount);
  free(temp->trip_distance);
  free(temp->ratecode);
  free(temp->store_flag);
  free(temp->puloc);
  free(temp->doloc);
  free(temp->payment_t);
  free(temp->fare);
  free(temp->extra);
  free(temp->mta_tax);
  free(temp->tip_tot);
  free(temp->tolls);
  free(temp->improv);
  free(temp->amount);
  free(temp->PUDT);
  free(temp->Dudt);
  free(temp->duration);
}
