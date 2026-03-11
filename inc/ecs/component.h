#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <types.h>

typedef void (*remove_ft)(id_t id);   /* Callback to let the component release memory and mapping. */
typedef void (*unreg_ft)(void);       /* Final unregistry function for entire component.           */

int  ComponentExists(id_t id);

void RegisterComponent(id_t *id, remove_ft rmv, unreg_ft unr);
void UnregisterComponent(id_t id);

/* Takes a pointer to an ID to become the Component's ID, if the ID does not exist, or is 0, an ID is generated and set.
   This function must be called in the relevant 'add' function of the Component's API. */
void EnsureComponent(id_t *id, remove_ft rmv, unreg_ft unr);

void EntityAdd(id_t ent, id_t cmp); /* Adds a mapping between an entity ID and a component ID, that the entity 'owns'. */
void EntityRmv(id_t ent, id_t cmp); /* Removes a mapping between an entity ID and a componet ID. */

#endif /* COMPONENT_H_ EOF */
