#include <raylib.h>
#include "rlflecs.h"

typedef struct {
  float x, y;
} Position;

typedef struct {
  const char* text;
  Color colour;
} Text;

void raylib_begin_draw(ecs_iter_t* iter) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
}

void raylib_end_draw(ecs_iter_t* iter) {
  EndDrawing();
}

void text_draw(ecs_iter_t* iter) {
  Position *pos = ecs_field(iter, Position, 0);
  Text *text = ecs_field(iter, Text, 1);

  for (int eid = 0; eid < iter->count; eid++) {
    DrawText(text[eid].text, pos[eid].x - MeasureText(text[eid].text, 32) * 0.5f, pos[eid].y, 32, text[eid].colour);
  }
}

int main(void) {
  InitWindow(800, 600, "Raylib with flecs!");

  ecs_world_t *world = ecs_init();

  init_raylib_compat(world);

  // Declare components for the world
  ECS_COMPONENT(world, Position);
  ECS_COMPONENT(world, Text);

  // Declare systems
  ECS_SYSTEM(world, raylib_begin_draw, PreDraw, 0);
  ECS_SYSTEM(world, raylib_end_draw, PostDraw, 0);

  ECS_SYSTEM(world, text_draw, OnDraw, Position, Text);

  // Create entities
  ecs_insert(world,
    ecs_value(Position, {400.0f, 270.0f}),
    ecs_value(Text, { "Hello, World!", BLACK })
  );

  ecs_insert(world,
    ecs_value(Position, {400.0f, 300.0f}),
    ecs_value(Text, { "These lines are Entities!", RED })
  );

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    if (dt > 0.1f) dt = 0.016f; // Helps with debugging

    if (!ecs_progress(world, dt)) break;
  }

  ecs_fini(world);
  CloseWindow();
}
