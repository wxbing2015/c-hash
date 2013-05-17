#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

int main(){
    char* key[] = {"nan","nan"};
    char* value[] = {"male","female"};
    int i;
    Bucket * entry = NULL;
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    hash_init(ht,3);
    for (i =0;i<2;i++){
        int datasize = strlen(value[i]);
        hash_add(ht,key[i],value[i],datasize);
    }
    foreach(entry,ht){
        printf("%s:%s\n",(char*)entry->arKey,(char*)entry->pData);
    }
    void* sex = NULL;
    hash_find(ht,"nan", &sex);
    printf("%s\n",(char*)sex);
    free(sex);
    sex = NULL;
    printf("%d\n",hash_num_elements(ht));
    hash_del(ht,"nan");
    printf("%d\n",hash_num_elements(ht));
    hash_free(ht);
    return 0;
}
