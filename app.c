#include <engine.h>
#include <renderer/window.h>
#include <components/rect.h>
#include <components/color.h>

static window_t window;

int main(void){
   static id_t sqr1;
   static id_t sqr2;
   
   SDL_Rect *r;
   
   InitRenderer();
   
   if (!CreateWindow(&window, "ecs test", 500, 400)){
      return 1;
   }
   
   Register(&sqr1); /* Ask the system to give us a mapping of our entity and register it. */
   Register(&sqr2);
   
   /* Add components here. */
   Rect_Add(sqr1, 10, 10, 69, 69);
   Color_Add(sqr1, 161, 255, 130);
   
   Rect_Add(sqr2, 10, 10, 20, 69);
   Color_Add(sqr2, 0, 0, 255);
   
   while (window.active){
      r = Rect_Get(sqr1); /* Make them move so i know if i messed up the map implementation. */
      r->x += 1;
      
      r = Rect_Get(sqr2);
      r->y += 1;
      r->x += 1;
      
      BeginRender(&window);
      /* In real : Use group component that handles global lists. (eg. renderables) */
      RenderEntity(&window, sqr1);
      RenderEntity(&window, sqr2);
      FinishRender(&window);
      
      SDL_Delay(33); /* Sleep the main thread for 33ms (about 60 fps), saves some CPU. */
      WindowPoll(&window);
   }
   
   Unregister(sqr1); /* Unregister our entities and let the components release their data. */
   Unregister(sqr2);
   
   FreeWindow(&window);
   FreeECS(); /* Hypothetical free function, if something where to be on the heap. */
   
   return 0;
}

/* This example application doesn't do much, just 2 moving squares of different sizes
   It simply showcases the API. */
