#include "global.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int hashcode(char *key)
{
     int temp = 0;
     int i = 0;
     while(key[i] != '\0')
     {
          temp = ((temp<<SHIFT) + key[i]) % SIZE;
          i++;
     }
     return temp;
}

struct symbolNode* new_node(int lineno)
{
     struct symbolNode* newnode = (struct symbolNode*)malloc(sizeof(struct symbolNode));
     newnode->name = NULL;
     newnode->next = NULL;
     newnode->line = lineno;
     return newnode;
}
void insert(char* name, int type)
{
     int key = hashcode(name);
     struct node* current = hash_table[key];
     struct node* newnode = new_node();
     int length = strlen(name);
     int i;
     strcpy(newnode->name, name);
     newnode->type = type;
#ifdef DEBUG
     printf ("new node type: %d\n", newnode->type);
#endif
     if(hash_table[key]==NULL)
          hash_table[key] = newnode;
     else
     {
          newnode->next = hash_table[key]->next;
          hash_table[key]->next = newnode;
     }
}
struct symbol* lookup(char* name)
{
#ifdef DEBUG
     printf ("lookingfor %s\n", name);
#endif
     int key = hashcode(name);
     struct node* current = hash_table[key];
     int i = 0;
     while(current != NULL)
     {
          i++;
          if(strcmp(current->name, name) == 0) /* right node contains the given name */
          {
#ifdef DEBUG
               printf ("find %s, type = %d\n", name, current->type);
#endif
               return current->type;
          }
          current = current->next;
     }
#ifdef DEBUG
     printf ("cannot find %s\n", name);
#endif
     return -1;                 /* cannot find the ID */
}

int typeEqual(int type, int want)
{
     return type==want;
}

void type_error(int lineno)
{
     fprintf(stderr, "type error in line: %d\n", lineno);
}
