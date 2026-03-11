#include <renderer/window.h>

#include <components/color.h>
#include <components/rect.h>

static _inline
void _SetDrawClr(window_t *window, int r, int g, int b, int a){
   SDL_SetRenderDrawColor(window->renderer, (Uint8) r, (Uint8) g, (Uint8) b, (Uint8) a);
   return;
}

void InitRenderer(void){
   SDL_Init(SDL_INIT_VIDEO);
   return;
}

int CreateWindow(window_t *window, const char *title, size_t sx, size_t sy){
   window->window = SDL_CreateWindow(title, (int) sx, (int) sy, SDL_WINDOW_RESIZABLE);
   if (window->window == NULL) return 0;
   
   window->renderer = SDL_CreateRenderer(window->window, NULL);
   if (window->renderer == NULL){
      SDL_DestroyWindow(window->window);
      return 0;
   }
   
#  ifdef _WIN32
   { /* Make it look nicer on windows */
      extern
      int w32FixWindowLook(SDL_Window *w);
      
      if (!w32FixWindowLook(window->window)){
         FreeWindow(window);
         return 0;
      }
   }
#  endif
   
   window->active = 1;
   
   return 1;
}

void FreeWindow(window_t *window){
   SDL_DestroyWindow(window->window);
   SDL_DestroyRenderer(window->renderer);
   window->active = 0;
   return;
}

void WindowPoll(window_t *window){
   while (SDL_PollEvent(&window->event)){
      if (window->event.type == SDL_EVENT_QUIT){
         window->active = 0;
         return;
      }
   }
   
   return;
}

void BeginRender(window_t *window){
   _SetDrawClr(window, 0, 0, 0, 0);
   SDL_RenderClear(window->renderer);
   return;
}

void FinishRender(window_t *window){
   SDL_RenderPresent(window->renderer);
   return;
}

void Render(window_t *window, color_t *color, SDL_Rect *rect){
   SDL_FRect temp;
   static color_t dbg = {{255, 0, 180}};
   
   if (color == NULL) {
      color = &dbg; /* Purple-pink debug color if no color. */
   }
   
   temp.x = (float) rect->x;
   temp.y = (float) rect->y;
   temp.w = (float) rect->w;
   temp.h = (float) rect->h;
   
   _SetDrawClr(window, color->color[0], color->color[1], color->color[2], 0);
   SDL_RenderFillRect(window->renderer, &temp);
   return;
}

void RenderEntity(window_t *window, id_t id){
   SDL_Rect *rect;
   color_t  *clr;
   
   rect = Rect_Get(id);
   clr  = Color_Get(id);
   
   if (rect == NULL) return;
   
   Render(window, clr, rect);
   
   return;
}
