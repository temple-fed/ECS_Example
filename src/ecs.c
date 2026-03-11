#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/map.h>

#define MAX_CMP_PER_ENT (128)
#define BUCKET_CNT      (128)
#define BUCKET_LNG      (32)
#define SIZE            (BUCKET_CNT * BUCKET_LNG)

typedef struct {
   id_t   ids[MAX_CMP_PER_ENT]; /* In a real imp : dynamic insert/removal arraylist (since the list is small). */
   size_t cnt;
} entinfo_t;

typedef struct {
   remove_ft rmv;
   unreg_ft  unr;
} cmpinfo_t;

static id_t      entids[SIZE];
static entinfo_t ents[SIZE];
static mapinfo_t entmap = MAPINFO(entinfo_t, BUCKET_CNT, BUCKET_LNG, entids, ents);

static id_t      cmpids[SIZE];
static cmpinfo_t cmps[SIZE];
static mapinfo_t cmpmap = MAPINFO(cmpinfo_t, BUCKET_CNT, BUCKET_LNG, cmpids, cmps);

/* -- Entity -- */

void Register(id_t *id){
   MapReserveNew(&entmap, id);
   return;
}

void Unregister(id_t id){
   size_t     i   = 0;
   entinfo_t *ent = MapGet(&entmap, id);
   cmpinfo_t *cmp;
   
   /* Notify all of the entity's components to release it's mapping. */
   while (i < ent->cnt){
      cmp = MapGet(&cmpmap, ent->ids[i]);
      cmp->rmv(id);
      i ++;
   }
   
   MapRelease(&entmap, id); /* Release from system map. */
   return;
}

/* -- Component -- */

int ComponentExists(id_t id){
   return id != 0 && MapGet(&cmpmap, id) != NULL; /* 0 ID is nonexistant. */
}

void RegisterComponent(id_t *id, remove_ft rmv, unreg_ft unr){
   cmpinfo_t *cmp = MapReserveNew(&cmpmap, id);
   
   cmp->rmv = rmv;
   cmp->unr = unr;
   
   return;
}

void UnregisterComponent(id_t id){
   cmpinfo_t *cmp = MapGet(&cmpmap, id);
   
   cmp->unr();
   MapRelease(&cmpmap, id);
   
   return;
}

void EnsureComponent(id_t *id, remove_ft rmv, unreg_ft unr){
   if (!ComponentExists(*id)){
      RegisterComponent(id, rmv, unr);
   }
   
   return;
}

void EntityAdd(id_t ent, id_t cmp){
   entinfo_t *entinf = MapGet(&entmap, ent);
   
   entinf->ids[entinf->cnt] = cmp;
   entinf->cnt ++;
   
   return;
}

/* --- Misc --- */

void FreeECS(void){
   /* loop or something here */
   return;
}
