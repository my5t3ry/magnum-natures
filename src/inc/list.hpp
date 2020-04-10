#ifndef list_h
#define list_h

#include <list>
#include <vector>

#include "constants.hpp"
#include "organism.hpp"
#include "quadtree.hpp"

class List {
public:
    List();

    void Behavior();

    void Place();

    void Remove();

    std::vector<Organism *> getNear(Organism o);

    std::list<Organism> organisms;

    Quadtree tree;

    std::list<Organism> GetCarnivors();

    std::list<Organism> GetHerbavors();

    std::list<Organism> GetCorpses();

    std::list<Organism> GetPlants();
};

#endif
