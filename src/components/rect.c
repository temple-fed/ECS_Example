#include <ecs/component.h>
#include <ecs/map.h>

#include <components/rect.h>

#define B_CNT (128)
#define B_LNG (16)
#define SIZE  (B_CNT * B_LNG)

static id_t      ids[SIZE];
static SDL_Rect  data[SIZE];
static mapinfo_t map = MAPINFO(SDL_Rect, B_CNT, B_LNG, ids, data);

static id_t self;

static void _Unreg(void){return;}

SDL_Rect *Rect_Add(id_t id, int x, int y, int w, int h){
   SDL_Rect *r;
   
   EnsureComponent(&self, Rect_Rmv, _Unreg);
   
   r = MapReserve(&map, id);
   r->x = x;
   r->y = y;
   r->w = w;
   r->h = h;
   
   return r;
}

void Rect_Rmv(id_t id){
   MapRelease(&map, id);
   return;
}

SDL_Rect *Rect_Get(id_t id){
   return MapGet(&map, id);
}
