#ifndef HASH_TABLE
#define HASH_TABLE

#define ulong unsigned long
#define uint  unsigned int

#define SUCCESS      0
#define EXISTS       1
#define FAILURE     -1
#define NOTEXISTS   -2

#define reset(ht)       ((ht)->pInternalPointer = (ht)->pListHead)
#define next(ht)        ((ht)->pInternalPointer = (ht)->pInternalPointer->pListNext)
#define isnotend(ht)    ((ht)->pInternalPointer != NULL)
#define key(ht)         ((ht)->pInternalPointer->arKey)
#define value(ht)       ((ht)->pInternalPointer->pData)
#define foreach(k,v,ht) for (reset(ht); isnotend(ht)&&(k=key(ht))&&(v=value(ht)); next(ht))


typedef struct bucket {
    ulong  h;
    char  *arKey;
    int    keyLength;
    void  *pData;
    int    dataLength;
    struct bucket *pListNext;
    struct bucket *pListLast;
    struct bucket *pNext;
    struct bucket *pLast;
} Bucket;

typedef struct _hashtable {
    uint    nTableSize;
    uint    nTableMask;
    uint    nNumOfElements;
    Bucket *pInternalPointer;    
    Bucket *pListHead;
    Bucket *pListTail;
    Bucket **arBuckets;
} HashTable;

int hash_init(HashTable *ht, uint nSize);
void hash_free(HashTable *ht);

int hash_add(HashTable *ht, char *arKey, void *pData, int nDataSize);
int hash_del(HashTable *ht, char *arKey);
int hash_find(HashTable *ht, char *arKey, void **pData);
int hash_exists(HashTable *ht, char *arKey);
int hash_num_elements(HashTable *ht);

#endif
