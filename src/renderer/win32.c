#include <dwmapi.h>
#include <SDL3/SDL.h>

int w32FixWindowLook(SDL_Window *w){
   HWND             wind;
   SDL_PropertiesID prop;
   
   prop = SDL_GetWindowProperties(w);
   wind = SDL_GetPointerProperty(prop, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
   
   if (!wind) return 0;
   
   { /* Corner preference */
      DWM_WINDOW_CORNER_PREFERENCE pref = DWMWCP_DONOTROUND;
      if (DwmSetWindowAttribute(wind, DWMWA_WINDOW_CORNER_PREFERENCE, &pref, sizeof(pref))){
         return 0;
      }
   }
   
   { /* Caption color */
      COLORREF pref = 0x00181818;
      if (DwmSetWindowAttribute(wind, DWMWA_CAPTION_COLOR, &pref, sizeof(pref))){
         return 0;
      }
   }
   
   { /* Border color */
      COLORREF pref = 0x00252525;
      if (DwmSetWindowAttribute(wind, DWMWA_BORDER_COLOR, &pref, sizeof(pref))){
         return 0;
      }
   }
   
   { /* Title color */
      COLORREF pref = 0x00FFFFFF;
      if (DwmSetWindowAttribute(wind, DWMWA_TEXT_COLOR, &pref, sizeof(pref))){
         return 0;
      }
   }
   
   return 1;
}
