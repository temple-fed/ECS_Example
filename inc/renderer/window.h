#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>
#include <types.h>
#include "color.h"

typedef struct {
   SDL_Event     event;
   SDL_Window   *window;
   SDL_Renderer *renderer;
   int           active;
} window_t;

void InitRenderer(void);

int  CreateWindow(window_t *window, const char *title, size_t sx, size_t sy);
void FreeWindow(window_t *window);

void WindowPoll(window_t *window); /* Handles window events. In real: use optional handler callback in window_t */

void BeginRender(window_t *window);
void FinishRender(window_t *window);

void Render(window_t *window, color_t *color, SDL_Rect *rect);
void RenderEntity(window_t *window, id_t id);

#endif /* WINDOW_H_ */
