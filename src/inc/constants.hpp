#ifndef constants_h
#define constants_h
#define GL_GLEXT_PROTOTYPES
#define GLM_ENABLE_EXPERIMENTAL

#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// General
const int HERBAVORES = 520;
const int CARNIVORES = 35;
const int PLANTS = 9000;
const int WINDOW_X = 1600;
const int WINDOW_Y = 1600;
const float BOUNDS_X = 320;
const float BOUNDS_Y = 320;
const float MAX_WANDERING_DISTANCE = 40;

// Types
const int HERBAVORE_TYPE = 1;
const int CARNIVORE_TYPE = 2;
const int PLANT_TYPE = 3;
const int CORPSE_TYPE = 4;

// Creature stats
const int CREATURE_MAX_HEALTH = 100;
const int CREATURE_BEST_SENSE = 4;
const int CREATURE_BITE = 5;
const int CREATURE_EXP_PREG_TIME = 1000;
const int CREATURE_EXP_AGE = 10000;
const int CREATURE_HUNGRY_AMOUNT = 50;
const int CREATURE_STARVE_AMOUNT = 90;
const float CREATURE_SPEED = .35;
const float CREATURE_REACH = 1.3;
const float CREATURE_MUTATION_PERCENT = .25;
const float CREATURE_MUTATION_CHANCE = .05;

// Plant Stats
const int PLANT_MAX_HEALTH = 200;
const int PLANT_GROW_AMOUNT = 2;

// Corpse Stats
const int CORPSE_MAX_HEALTH = 400;
const int CORPSE_DECAY_AMOUNT = -1;

// Opengl
const int NUM_SHADERS = 3;
const int NUM_UNIFORMS = 3;
const float SIDES = 5;

// Quadtree
const int MAX_OBJECTS = 40;
const int MAX_LEVELS = 6;

// Camera
const float MOVE_AMOUNT = 2.5;

#endif
