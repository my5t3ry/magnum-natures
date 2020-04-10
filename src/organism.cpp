#include "organism.hpp"

#include <random>

Organism::Organism(Rectangle r, DNA d) {
    rect    = r;
    myDNA   = d;

    if(rect.x == 0 && rect.y == 0){
        rect.x = getRandom(BOUNDS);
        rect.y = getRandom(BOUNDS);
    }

    hunger          = 50;
    health          = myDNA.maxHealth/2;
    gender          = rand() % 2;
    age             = 0;
    pregnancyTime   = 0;
    able            = false;
    pregnancyReady  = false;
    pregnate        = false;
    hasTarget       = false;
    wander          = false;
}

void Organism::Behavior() {
    this->Priority();

    if (!hasTarget)
        this->setTarget();
    else
        this->checkTarget();

    this->Action();

    if (pregnate) {
        pregnancyTime++;
        if (pregnancyTime > myDNA.expectedPregnancyTime)
            pregnancyReady = true;
    }

    age++;
    if (age > myDNA.expectedAge)
        health = 0;

    hunger++;
    if (starving)
        health -= 1;
    if (able)
        if (health < myDNA.maxHealth)
            health += 1;
}

void Organism::Priority() {

    hungry = false;
    starving = false;
    able = true;
    if (hunger > myDNA.hungryAmount) {
        starving = false;
        hungry = true;
        able = false;
    }
    if (hunger >= myDNA.starveAmount) {
        hungry = true;
        starving = true;
        able = false;
    }
}

void Organism::setTarget() {
    std::shuffle(nearMe.begin(), nearMe.end(), std::mt19937(std::random_device()()));

    for (auto & it : nearMe) {
        if ((it->getType() == myDNA.eatType && hungry) || (it->getType() == CORPSE_TYPE && starving)) {
            target = it;
            hasTarget = true;
            wander = false;
            break;
        }
        if (it->getType() == myDNA.type && able && it->getGender() != gender) {
            target = it;
            hasTarget = true;
            wander = false;
            break;
        }
    }

    if (!hasTarget && !wander) {
        wander = true;
        Rectangle tmp(getRandom(BOUNDS), getRandom(BOUNDS), 0, 0);
        wTarget = tmp;
    }
}

void Organism::checkTarget() {
    for (auto & it : nearMe)
        if (target == it)
            return;

    hasTarget = false;
}

void Organism::Action() {
    if (hasTarget) {
        if (Distance(rect, target->getRectangle()) < myDNA.reach) {
            if ((target->getType() == myDNA.eatType) || (target->getType() == CORPSE_TYPE)) {
                target->takeBite(myDNA.bite);
                hunger -= myDNA.bite;
                if (target->getHealth() <= 0)
                    hasTarget = false;
            } else if (target->getType() == myDNA.type) {
                if (target->getGender() != gender) {
                    target->passDNA(myDNA);
                }
                hasTarget = false;
            }
        } else
            moveTowards(target->getRectangle());
    } else if (wander) {
        if (Distance(rect, wTarget) < myDNA.reach)
            wander = false;
        else
            moveTowards(wTarget);
    }
}

void Organism::moveTowards(Rectangle t) {
    if (rect.x == t.x) {
        if (rect.y < t.y)
            rect.y += myDNA.speed;
        else
            rect.y -= myDNA.speed;
    } else if (rect.y == t.y) {
        if (rect.x < t.x)
            rect.x += myDNA.speed;
        else
            rect.x -= myDNA.speed;
    } else if (rect.x < t.x) {
        if (rect.y < t.y) {
            rect.x += myDNA.speed;
            rect.y += myDNA.speed;
        } else {
            rect.x += myDNA.speed;
            rect.y -= myDNA.speed;
        }
    } else if (rect.x > t.x) {
        if (rect.y < t.y) {
            rect.x -= myDNA.speed;
            rect.y += myDNA.speed;
        } else {
            rect.x -= myDNA.speed;
            rect.y -= myDNA.speed;
        }
    }
}

void Organism::passDNA(DNA d) {
    if (!pregnate) {
        pregnate = true;
        pregnancyTime = 0;
        childsDNA = myDNA.combine(d);
    }
}

void Organism::grow() {
    if (health <= myDNA.maxHealth)
        health += myDNA.growAmount;
}



void Organism::takeBite(int bite) {
    health -= bite;
}
