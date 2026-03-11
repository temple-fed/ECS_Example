#include <ecs/component.h>
#include <ecs/map.h>

#include <components/color.h>

#define B_CNT (128)
#define B_LNG (16)
#define SIZE  (B_CNT * B_LNG)

static id_t      ids[SIZE];
static color_t   data[SIZE];
static mapinfo_t map = MAPINFO(color_t, B_CNT, B_LNG, ids, data);

static id_t self;

static void _Unreg(void){return;}

color_t *Color_Add(id_t id, int r, int g, int b){
   color_t *c;
   
   EnsureComponent(&self, Color_Rmv, _Unreg);
   EntityAdd(id, self);
   
   c = MapReserve(&map, id);
   c->color[0] = r;
   c->color[1] = g;
   c->color[2] = b;
   
   EntityAdd(id, self);
   
   return c;
}

void Color_Rmv(id_t id){
   MapRelease(&map, id);
   EntityRmv(id, self);
   return;
}

color_t *Color_Get(id_t id){
   return MapGet(&map, id);
}
