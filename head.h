#ifndef LISTH
#define LISTH


struct data {
	char *Vendorid;
	char *passengercount;
	char *trip_distance;
	char *ratecode;
	char *store_flag;
	char *puloc;
	char *doloc;
	char *payment_t;
	char *fare;
	char *extra;
	char *mta_tax;
	char *tip_tot;
	char *tolls;
	char *improv;
	char *amount;
	char *PUDT;
	char *Dudt;
	char *duration;

	struct data *left;
	struct data *right;
	struct data *next;
};
struct data* data_read(int arg, char **argv, struct data *parent);
int get_length(char *stri);
void create(struct data *temp,char *string, int field, int length);
struct data *new_node(char *string);
struct data* bst_insert(struct data *parent, struct data *temp);
void free_parent(struct data *parent);
void search(struct data *parent,char *key,char **argv);
void bst_search(struct data *parent,char *key,char *outfile);
void output(char *key, int comparisons);
void file_out(char *file, struct data *node,int test,char *key);
void newline_rem(char *key,char *new_key);
void inorder(struct data *parent, char *PULocationID, FILE *p,int *num);
void bst_inorder(struct data *parent,char *output);
void free_temp(struct data *temp);
void print_out(FILE *p,char *PULocationID, char *PUdatetime);
void free_next(struct data *parent);

#endif
