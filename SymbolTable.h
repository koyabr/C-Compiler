#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
int hashcode(char* key);
struct symbolNode* newSymbolNode();
void insert(char* name, ExpType type);
struct symbolNode* lookup(char* name);
#endif
