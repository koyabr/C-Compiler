#define SIZE 101
#define SHIFT 4
#define ID_NAME_SIZE 128
#define INTEGER 1024
struct symbol{
     char* name;                /* variable's name */
     int type;                  /* variable's type */
     int int_value;             /* variable's value if type==INTEGER */
};
