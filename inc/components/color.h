#ifndef COLOR_COMP_H_
#define COLOR_COMP_H_

#include <renderer/color.h>

color_t *Color_Add(id_t id, int r, int g, int b);
void     Color_Rmv(id_t id);
color_t *Color_Get(id_t id);

#endif /* COLOR_COMP_H_ */
