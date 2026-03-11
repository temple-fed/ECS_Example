#ifndef ENTITY_H_
#define ENTITY_H_

#include <types.h>

void Register(id_t *id);
void Unregister(id_t id);

void FreeECS(void);

#endif /* ENTITY_H_ EOF */
