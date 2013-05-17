#ifndef HASH_TABLE
#define HASH_TABLE

#define HASH_UPDATE 		(1<<0)
#define HASH_ADD			(1<<1)
#define ulong unsigned long
#define uint  unsigned int
#define SUCCESS 0
#define FAILURE -1
#define foreach(entry, ht) for(entry=ht->pListHead;entry!=NULL;entry = entry->pListNext) 


typedef struct bucket {
	ulong h;
	char *arKey;
    int   keyLength;
	void *pData;
    int   dataLength;
	struct bucket *pListNext;
	struct bucket *pListLast;
	struct bucket *pNext;
	struct bucket *pLast;
} Bucket;

typedef struct _hashtable {
	uint nTableSize;
	uint nTableMask;
	uint nNumOfElements;
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
