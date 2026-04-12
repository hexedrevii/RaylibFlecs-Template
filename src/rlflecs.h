#ifndef WFLECS_H
#define WFLECS_H

#include <flecs.h>

extern ECS_DECLARE(PreDraw);
extern ECS_DECLARE(OnDraw);
extern ECS_DECLARE(PostDraw);

void init_raylib_compat(ecs_world_t* world);

#endif
