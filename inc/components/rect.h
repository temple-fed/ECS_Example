#ifndef RECT_COMP_H_
#define RECT_COMP_H_

#include <SDL3/SDL.h>
#include <types.h>

SDL_Rect *Rect_Add(id_t id, int x, int y, int w, int h);
SDL_Rect *Rect_Get(id_t id);
void      Rect_Rmv(id_t id);

#endif /* RECT_COMP_H_ */
