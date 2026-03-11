#ifndef MAP_H_
#define MAP_H_

#include <types.h>

/* Fixed sized hashkey map. Revision : 2*/

typedef struct {
   size_t size;    /* sizeof individual elem. */
   size_t bcnt;    /* Bucket count.           */
   size_t blng;    /* Bucket length.          */
   id_t  *ids;     /* Array of IDs.           */
   void  *buff;    /* Buffer of elem data.    */
} mapinfo_t;

#define MAPINFO(s, bcnt, blng, ids, buff) \
   {sizeof(s), bcnt, blng, ids, buff}

id_t GenerateID(void);

void *MapReserveNew(mapinfo_t *map, id_t *id);   /* NULL if can't reserve. */
void *MapReserve(mapinfo_t *map, id_t id);       /* NULL if can't reserve. */
void  MapRelease(mapinfo_t *map, id_t id);

void *MapGet(mapinfo_t *map, id_t id); /* NULL if it doesn't exist in the map. */

#endif /* MAP_H_ */
