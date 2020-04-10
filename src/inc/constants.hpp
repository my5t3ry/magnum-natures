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
const int HERBAVORES = 200;
const int CARNIVORES = 45;
const int PLANTS = 3500;
const int WINDOW_X = 1920;
const int WINDOW_Y = 1280;
const float BOUNDS = 30;

// Types
const int HERBAVORE_TYPE = 1;
const int CARNIVORE_TYPE = 2;
const int PLANT_TYPE = 3;
const int CORPSE_TYPE = 4;

// Creature stats
const float CREATURE_MAX_HEALTH = 200;
const int CREATURE_BEST_SENSE = 2;
const int CREATURE_BITE = 5;
const int CREATURE_EXP_PREG_TIME = 1000;
const int CREATURE_EXP_AGE = 10000;
const int CREATURE_HUNGRY_AMOUNT = 50;
const int CREATURE_STARVE_AMOUNT = 90;
const float CREATURE_SPEED = .05;
const float CREATURE_REACH = .4;
const float CREATURE_MUTATION_PERCENT = .25;
const float CREATURE_MUTATION_CHANCE = .08;

// Plant Stats
const int PLANT_MAX_HEALTH = 300;
const int PLANT_GROW_AMOUNT = 4;

// Corpse Stats
const int CORPSE_MAX_HEALTH = 350;
const int CORPSE_DECAY_AMOUNT = -1;

// Opengl
const int NUM_SHADERS = 3;
const int NUM_UNIFORMS = 3;
const float SIDES = 5;

// Quadtree
const int MAX_OBJECTS = 10;
const int MAX_LEVELS = 10;

// Camera
const float MOVE_AMOUNT = .2;

#endif
