#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

ulong hash_func(char *arKey)
{
    register ulong hash = 5381;
    int      nKeyLength = strlen(arKey);

    for (; nKeyLength >= 8; nKeyLength -= 8) {
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
        hash = ((hash << 5) + hash) + *arKey++;
    }
    switch (nKeyLength) {
        case 7: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 6: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 5: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 4: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 3: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 2: hash = ((hash << 5) + hash) + *arKey++; /* fallthrough... */
        case 1: hash = ((hash << 5) + hash) + *arKey++; break;
        case 0: break;
        default:
                break;
    }
    return hash;
}

#define CONNECT_TO_BUCKET_DLLIST(element, list_head) do{    \
    (element)->pNext = (list_head);                         \
    (element)->pLast = NULL;                                \
    if ((element)->pNext) {                                 \
        (element)->pNext->pLast = (element);                \
    }                                                       \
}while(0);

#define CONNECT_TO_GLOBAL_DLLIST(element, ht)    do{        \
    (element)->pListLast = (ht)->pListTail;                 \
    (ht)->pListTail = (element);                            \
    (element)->pListNext = NULL;                            \
    if ((element)->pListLast != NULL) {                     \
        (element)->pListLast->pListNext = (element);        \
    }                                                       \
    if (!(ht)->pListHead) {                                 \
        (ht)->pListHead = (element);                        \
    }                                                       \
    if ((ht)->pInternalPointer == NULL) {                   \
        (ht)->pInternalPointer = (element);                 \
    }                                                       \
}while(0);


int hash_init(HashTable *ht, uint nSize)
{
    uint i = 3;
    if (nSize >= 0x80000000) {
        ht->nTableSize = 0x80000000;
    } else {
        while ((1U << i) < nSize) {
            i++;
        }
        ht->nTableSize = 1 << i;
    }
    ht->arBuckets = (Bucket **) malloc(ht->nTableSize * sizeof(Bucket *));
    memset(ht->arBuckets,0,ht->nTableSize);
    ht->nTableMask = ht->nTableSize - 1;                        
    ht->pListHead = NULL;
    ht->pListTail = NULL;
    ht->pInternalPointer = NULL;
    ht->nNumOfElements = 0;
    return SUCCESS;
}

void hash_free(HashTable *ht)
{
    Bucket *p, *q;
    p = ht->pListHead;
    while (p != NULL) {
        q = p;
        p = p->pListNext;
        free(q->pData);
        free(q->arKey);
        free(q);
        q = NULL;
    }
    if (ht->nTableMask) {
        free(ht->arBuckets);
        ht->arBuckets = NULL;
    }
    free(ht);
    ht = NULL;
}

int hash_add(HashTable *ht, char *arKey, void *pData, int nDataSize)
{
    ulong h;
    uint nIndex;
    Bucket *p;
    void * pDataCopy = NULL;
    char * pKeyCopy  = NULL;
    int keyLength = strlen((char*)arKey);
    if (keyLength <= 0)
        return FAILURE;

    h = hash_func(arKey);
    nIndex = h & ht->nTableMask;
    p = ht->arBuckets[nIndex];
    pDataCopy = (void *)malloc(sizeof(nDataSize));
    memcpy(pDataCopy,pData,nDataSize);
    while (p != NULL) {
        if (p->arKey == arKey || ((p->keyLength == keyLength) && !memcmp(p->arKey, arKey, keyLength))) {
            free(p->pData);
            p->pData = pDataCopy;
            p->dataLength = nDataSize;
            return SUCCESS;
        }
        p = p->pNext;
    }
    p = (Bucket *) malloc(sizeof(Bucket));
    if (!p) {
        return FAILURE;
    }
    pKeyCopy = (char*) malloc(sizeof(keyLength));
    memcpy(pKeyCopy,arKey,keyLength);
    p->h = h;
    p->arKey = pKeyCopy;
    p->keyLength = keyLength;
    p->pData = pDataCopy;
    p->dataLength = nDataSize;
    CONNECT_TO_BUCKET_DLLIST(p, ht->arBuckets[nIndex]);
    CONNECT_TO_GLOBAL_DLLIST(p, ht);
    ht->arBuckets[nIndex] = p;
    ht->nNumOfElements++;
    return SUCCESS;
}

int hash_del(HashTable *ht, char *arKey)
{
    ulong h;
    uint nIndex;
    Bucket *p;
    int keyLength = strlen(arKey);
    if (keyLength <= 0)
        return FAILURE;

    h = hash_func(arKey);
    nIndex = h & ht->nTableMask;
    p = ht->arBuckets[nIndex];
    while (p != NULL) {
        if (p->arKey == arKey || ((p->keyLength == keyLength) && !memcmp(p->arKey, arKey, keyLength))) {
            if (p == ht->arBuckets[nIndex]) {
                ht->arBuckets[nIndex] = p->pNext;
            } else {
                p->pLast->pNext = p->pNext;
            }
            if (p->pNext) {
                p->pNext->pLast = p->pLast;
            }
            if (p->pListLast != NULL) {
                p->pListLast->pListNext = p->pListNext;
            } else { 
                ht->pListHead = p->pListNext;
            }
            if (p->pListNext != NULL) {
                p->pListNext->pListLast = p->pListLast;
            } else {
                ht->pListTail = p->pListLast;
            }
            if (ht->pInternalPointer == p) {
                ht->pInternalPointer = p->pListNext;
            }
            free(p->pData);
            free(p->arKey);
            free(p);
            p = NULL;
            ht->nNumOfElements--;
            return SUCCESS;
        }
        p = p->pNext;
    }
    return FAILURE;
}


int hash_find(HashTable *ht, char *arKey, void **pData)
{
    ulong h;
    uint nIndex;
    Bucket *p;
    int keyLength = strlen(arKey);
    if (keyLength<=0)
        return FAILURE;

    h = hash_func(arKey);
    nIndex = h & ht->nTableMask;
    p = ht->arBuckets[nIndex];
    while (p != NULL) {
        if (p->arKey == arKey || ((p->keyLength == keyLength) && !memcmp(p->arKey, arKey, keyLength))) {
            *pData = malloc(p->dataLength);
            memcpy(*pData,p->pData,p->dataLength);
            return SUCCESS;
        }
        p = p->pNext;
    }
    return FAILURE;
}

int hash_exists(HashTable *ht, char *arKey)
{
    ulong h;
    uint nIndex;
    Bucket *p;
    int keyLength = strlen(arKey);
    if (keyLength<=0)
        return FAILURE;

    h = hash_func(arKey);
    nIndex = h & ht->nTableMask;

    p = ht->arBuckets[nIndex];
    while (p != NULL) {
        if (p->arKey == arKey || ((p->keyLength == keyLength) && !memcmp(p->arKey, arKey, keyLength))) {
            return EXISTS;
        }
        p = p->pNext;
    }
    return NOTEXISTS;
}

int hash_num_elements(HashTable *ht)
{
    return ht->nNumOfElements;
}

