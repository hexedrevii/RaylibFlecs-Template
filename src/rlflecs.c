#include "rlflecs.h"

ECS_DECLARE(PreDraw);
ECS_DECLARE(OnDraw);
ECS_DECLARE(PostDraw);

void init_raylib_compat(ecs_world_t* world) {
  ECS_TAG_DEFINE(world, PreDraw);
  ECS_TAG_DEFINE(world, OnDraw);
  ECS_TAG_DEFINE(world, PostDraw);

  ecs_add_pair(world, PreDraw, EcsDependsOn, EcsPostUpdate);
  ecs_add_pair(world, OnDraw, EcsDependsOn, PreDraw);
  ecs_add_pair(world, PostDraw, EcsDependsOn, OnDraw);
}
