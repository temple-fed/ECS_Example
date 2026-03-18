#include <ecs/map.h>
#include <stdlib.h>
#include <string.h>

static uint64_t monostate = 1;

static
void _MapBeginLoop(mapinfo_t *map, id_t id, size_t *bucketposp, void **structbegp){
   *bucketposp = id % map->bcnt;
   *structbegp = (uint8_t *) map->buff + map->size * (*bucketposp);
   return;
}

static
void _MapLoopGet(mapinfo_t *map, size_t index, size_t bucketpos, id_t **idp, void *structbeg, void **structp){
   *idp     = &map->ids[bucketpos + index];
   *structp = (uint8_t *) structbeg + map->size * index;
   return;
}

id_t GenerateID(void){ /* Splitmix64 */
   id_t id;
   
   monostate += 0x9E3779B97F4A7C15ull;
   
   id = monostate;
   id = (id ^ (id >> 30)) * 0xBF58476D1CE4E5B9ull;
   id = (id ^ (id >> 27)) * 0x94D049BB133111EBull;
   id = (id ^ (id >> 32));
   
   return id;
}

void *MapReserveNew(mapinfo_t *map, id_t *id){
   *id = GenerateID();
   return MapReserve(map, *id);
}

void *MapReserve(mapinfo_t *map, id_t id){
   void *sbeg;
   void *s;
   id_t *idp;
   size_t bpos;
   size_t i = 0;
   
   _MapBeginLoop(map, id, &bpos, &sbeg);
   
   while (i < map->blng){
      _MapLoopGet(map, i, bpos, &idp, sbeg, &s);
      
      if (*idp == 0){
         *idp = id;
         return s;
      }
      
      i ++;
   }
   
   return NULL;
}

void MapRelease(mapinfo_t *map, id_t id){
   void *sbeg;
   void *s;
   id_t *idp;
   size_t bpos;
   size_t i = 0;
   
   _MapBeginLoop(map, id, &bpos, &sbeg);
   
   while (i < map->blng){
      _MapLoopGet(map, i, bpos, &idp, sbeg, &s);
      
      if (*idp == id){
         *idp = 0;
         memset(s, 0x0, map->size);
         return;
      }
      
      i ++;
   }
   
   return;
}

void *MapGet(mapinfo_t *map, id_t id){
   void *sbeg;
   void *s;
   id_t *idp;
   size_t bpos;
   size_t i = 0;
   
   _MapBeginLoop(map, id, &bpos, &sbeg);
   
   while (i < map->blng){
      _MapLoopGet(map, i, bpos, &idp, sbeg, &s);
      
      if (*idp == id){
         return s;
      }
      
      i ++;
   }
   
   return NULL;
}
