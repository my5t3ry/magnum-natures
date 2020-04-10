#include "list.hpp"

List::List() {
    int i;
    DNA d = DNA(HERBAVORE_TYPE);
    Rectangle tmp;
    for (i = 0; i < HERBAVORES; i++) {
        Organism X(tmp, d);
        organisms.push_back(X);
    }

    d = DNA(CARNIVORE_TYPE);
    for (i = 0; i < CARNIVORES; i++) {
        Organism X(tmp, d);
        organisms.push_back(X);
    }

    d = DNA(PLANT_TYPE);
    for (i = 0; i < PLANTS; i++) {
        Organism X(tmp, d);
        organisms.push_back(X);
    }

    Rectangle R1 = Rectangle(0, 0, BOUNDS_X * 2, BOUNDS_Y * 2);
    tree = Quadtree(0, R1);
}

void List::Remove() {
    for (std::list<Organism>::iterator it = organisms.begin(); it != organisms.end(); it++)
        if (it->getHealth() <= 0) {
            if (it->getType() == PLANT_TYPE or it->getType() == CORPSE_TYPE)
                organisms.erase(it--);
            else {
                DNA d = DNA(CORPSE_TYPE);
                Organism X(it->getRectangle(), d);
                organisms.push_back(X);
                organisms.erase(it--);
            }
        }
}

void List::Behavior() {
    for (auto it = organisms.begin(); it != organisms.end(); it++) {
        if (it->getType() == PLANT_TYPE or it->getType() == CORPSE_TYPE)
            it->grow();
        else {
            std::vector<Organism *> near = getNear(*it);
            it->giveNearMe(near);
            it->Behavior();

            if (it->getPregnancyReady()) {
                Organism X(it->getRectangle(), it->getChildsDNA());
                organisms.push_back(X);
                it->hadPregnancy();
            }
        }
    }
}

std::list<Organism> List::GetCarnivors() {
    std::list<Organism> result;
    std::copy_if(organisms.begin(), organisms.end(), std::back_inserter(result), [](Organism val) {
        return (val.getType() == CARNIVORE_TYPE);
    });
    return result;
}

void List::Place() {
    tree.clear();
    for (auto it = organisms.begin(); it != organisms.end(); it++)
        tree.insert(&(*it));;
}

std::vector<Organism *> List::getNear(Organism c) {
    std::vector<Organism *> near;
    near = tree.retrieve(near, c.getRectangle());

    for (auto it = near.begin(); it != near.end(); it++)
        if (c.getBestSense() < Distance(c.getRectangle(), (*it)->getRectangle()))
            near.erase(it--);

    return near;
}

std::list<Organism> List::GetHerbavors() {
    std::list<Organism> result;
    std::copy_if(organisms.begin(), organisms.end(), std::back_inserter(result), [](Organism val) {
        return (val.getType() == HERBAVORE_TYPE);
    });
    return result;
}

std::list<Organism> List::GetPlants() {
    std::list<Organism> result;
    std::copy_if(organisms.begin(), organisms.end(), std::back_inserter(result), [](Organism val) {
        return (val.getType() == PLANT_TYPE);
    });
    return result;
}


std::list<Organism> List::GetCorpses() {
    std::list<Organism> result;
    std::copy_if(organisms.begin(), organisms.end(), std::back_inserter(result), [](Organism val) {
        return (val.getType() == CORPSE_TYPE);
    });
    return result;
}
