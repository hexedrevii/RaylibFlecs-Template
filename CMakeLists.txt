cmake_minimum_required(VERSION 3.18)

project("RaylibFlecs" LANGUAGES C)

include(FetchContent)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
  message(STATUS "Raylib not found! Building.")

  FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG master
    GIT_SHALLOW TRUE
  )

  FetchContent_MakeAvailable(raylib)
endif()

find_package(flecs QUIET)
if (NOT flecs_FOUND)
  message(STATUS "Flecs not found! Building.")
  FetchContent_Declare(
    flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs
    GIT_TAG master
    GIT_SHALLOW TRUE
  )

  FetchContent_MakeAvailable(flecs)
endif()

add_executable(${PROJECT_NAME}
  src/main.c

  src/rlflecs.h
  src/rlflecs.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
  src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  raylib
  flecs
)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
  COMMENT "Copying assets to output directory..."
)
