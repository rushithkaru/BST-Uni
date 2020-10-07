#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "head.h"
#define DATA_POINTS 18
#define MAX_BUFF 256
#define MAX_STRING 128



struct data* data_read(int arg, char **argv, struct data *parent){
    char *line = NULL;
    size_t lineBufferLength = MAX_BUFF;

    char *filename;

    filename = argv[1];

    FILE *p = fopen(filename,"r");
    assert(p != NULL);
    struct data *temp;

    int n,i,k,j;
    char *temp_s;


    while(getline(&line,&lineBufferLength,p)>0){

    temp = (struct data*) malloc(sizeof(struct data));
    assert(temp);
      k = 0;
        for(j = 0;j<DATA_POINTS;j++){
                /* Read the line. */
        n = get_length(&(line[k]));
        temp_s = (char *) malloc((n+1)*sizeof(char));

                 for(i=0;i<n;i++,k++){
                    temp_s[i] = line[k];
                  }
        temp_s[i] = '\0';
        create(temp,temp_s,j+1,i);
        k++;

        free(temp_s);
        }

    parent = bst_insert(parent,temp);

    }

  fclose(p);
  free(temp);
return parent;
}


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

void search(struct data *parent,char *key,char **argv){
  size_t lineBufferLength = MAX_STRING;
  char *new_key;

    while((getline(&key,&lineBufferLength,stdin)>0)){
      new_key = (char *) malloc(strlen(key)*sizeof(char));
      newline_rem(key,new_key);
      bst_search(parent,new_key,argv[2]);
      free(new_key);
    }
}

void newline_rem(char *key,char *new_key){

  int i;
    for(i=0;i<strlen(key)-1;i++){
      new_key[i] = key[i];
    }
    new_key[i] = '\0';

}


void bst_search(struct data *parent,char *key,char *outfile){
  static int comparisons = 0;
  int test = 1;
  /*  printf("%d \n",comparisons);
    printf("%s and %s  %d\n",parent->PUDT,key,strncmp(parent->PUDT,key,strlen(pa
rent->PUDT)));
    printf("%lu and %lu\n",strlen(parent->PUDT),strlen(key));*/
    if(parent == NULL){
      test = 0;

      printf("%s --> %d\n",key,comparisons);
      file_out(outfile,parent,test,key);
      return;
    }
    if(!strncmp(parent->PUDT,key,strlen(parent->PUDT))){
      comparisons++;
      output(parent->PUDT,comparisons);
      file_out(outfile,parent,test,key);
        while(parent->next){
          //comparisons++;
          parent = parent->next;
          file_out(outfile,parent,test,key);
        }
        comparisons = 0;
        return;
    }

    if(strncmp(parent->PUDT,key,strlen(parent->PUDT))<0){
      comparisons++;
      return bst_search(parent->right,key,outfile);
    }
    else{
      comparisons++;
      return bst_search(parent->left,key,outfile);
    }

}

void output(char *key, int comparisons){
  printf("%s --> %d\n",key,comparisons);
}

void file_out(char *file, struct data *node,int test, char *key){
  FILE *outfile = fopen(file,"a");
  assert(outfile != NULL);
if (test){
  fprintf(
    outfile,"%s --> VendorID: %s || passenger count: %s || trip distance: %s \n|
| RatecodeID: %s || store and fwd flag: %s || PULocationID: %s ||DOLocationID: %
s \n|| payment type: %s || fare amount: %s || extra: %s || mta tax: %s \n|| tip
amount: %s || tolls amount: %s || improvement surcharge: %s || total amount: %s
\n|| PUdatetime: %s ||  DOdatetime: %s || trip duration: %s ||\n",
   node->PUDT,node->Vendorid,node->passengercount,
     node->trip_distance,node->ratecode,node->store_flag,
   node->puloc,node->doloc,node->payment_t,node->fare,node->extra,
   node->mta_tax,node->tip_tot,node->tolls,node->improv,
   node->amount,node->PUDT,node->Dudt,node->duration);
 }
 else{
   fprintf(outfile,"%s--> NOTFOUND\n",key);
 }
 fclose(outfile);
}

void free_parent(struct data *parent){

  if(!parent){
    return;
  }


  free_parent(parent->left);
  free_parent(parent->right);
  free_parent(parent->next);
  free(parent);


}

void create(struct data *temp, char *string, int field, int length){
//add all elements of the struct here

    if(field == 1){
      temp->Vendorid = (char*) malloc(length*sizeof(char));
      strcpy(temp->Vendorid,string);
    }
    if(field == 2){
      temp->passengercount = (char*) malloc(length*sizeof(char));
      strcpy(temp->passengercount,string);
    }
    if(field == 3){
      temp->trip_distance = (char*) malloc(length*sizeof(char));
      strcpy(temp->trip_distance,string);
    }
    if(field == 4){
      temp->ratecode = (char*) malloc(length*sizeof(char));
      strcpy(temp->ratecode,string);
    }
    if(field == 5){
      temp->store_flag = (char*) malloc(length*sizeof(char));
      strcpy(temp->store_flag,string);
    }
    if(field == 6){
      temp->puloc = (char*) malloc(length*sizeof(char));
      strcpy(temp->puloc,string);
    }

    if(field == 7){
      temp->doloc = (char*) malloc(length*sizeof(char));
      strcpy(temp->doloc,string);
    }
    if(field == 8){
      temp->payment_t = (char*) malloc(length*sizeof(char));
      strcpy(temp->payment_t,string);
    }
    if(field == 9){
      temp->fare = (char*) malloc(length*sizeof(char));
      strcpy(temp->fare,string);
    }
    if(field == 10){
      temp->extra = (char*) malloc(length*sizeof(char));
      strcpy(temp->extra,string);
    }
    if(field == 11){
      temp->mta_tax = (char*) malloc(length*sizeof(char));
      strcpy(temp->mta_tax,string);
    }
    if(field == 12){
      temp->tip_tot = (char*) malloc(length*sizeof(char));
      strcpy(temp->tip_tot,string);
    }
    if(field == 13){
      temp->tolls = (char*) malloc(length*sizeof(char));
      strcpy(temp->tolls,string);
    }
    if(field == 14){
      temp->improv = (char*) malloc(length*sizeof(char));
      strcpy(temp->improv,string);
    }
    if(field == 15){
      temp->amount = (char*) malloc(length*sizeof(char));
      strcpy(temp->amount,string);
    }
    if(field == 16){
      temp->PUDT = (char*) malloc(length*sizeof(char));
      strcpy(temp->PUDT,string);
    }
    if(field == 17){
      temp->Dudt = (char*) malloc(length*sizeof(char));
      strcpy(temp->Dudt,string);
    }
    if(field == 18){
      temp->duration = (char*) malloc(length*sizeof(char));
      strcpy(temp->duration,string);
    }

}

int get_length(char *stri){
int n=0;
int i = 0;
	while( stri[i] != ',' && stri[i] != '\0'){
	  n++;
    i++;
	}

return n;

}
