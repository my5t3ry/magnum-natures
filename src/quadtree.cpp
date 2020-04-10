#include "quadtree.hpp"


Quadtree::Quadtree() {}

Quadtree::Quadtree(int pLevel, Rectangle pBounds) {
    level = pLevel;
    bounds = pBounds;
    isNull = false;
    nodes = new Quadtree[4];
    rect.x = pBounds.x * 1.01;
    rect.y = pBounds.y * 1.05;}

void Quadtree::clear() {
    objects.clear();

    for (int i = 0; i < 4; i++)
        if (!nodes[i].isNull) {
            nodes[i].objects.clear();
            nodes[i].clear();
        }

    delete[] nodes;
    if (level == 0)
        nodes = new Quadtree[4];
}

void Quadtree::split() {
    float subWidth = (bounds.w / 2);
    float subHeight = (bounds.h / 2);
    float x = bounds.x;
    float y = bounds.y;


    Rectangle R0(x + subWidth / 2, y + subHeight / 2, subWidth, subHeight);
    Rectangle R1(x - subWidth / 2, y + subHeight / 2, subWidth, subHeight);
    Rectangle R2(x - subWidth / 2, y - subHeight / 2, subWidth, subHeight);
    Rectangle R3(x + subWidth / 2, y - subHeight / 2, subWidth, subHeight);

    Quadtree Q0(level + 1, R0);
    Quadtree Q1(level + 1, R1);
    Quadtree Q2(level + 1, R2);
    Quadtree Q3(level + 1, R3);

    nodes[0] = Q0;
    nodes[1] = Q1;
    nodes[2] = Q2;
    nodes[3] = Q3;
}

int Quadtree::getIndex(Rectangle object) {
    int index = -1;

    bool topQuadrant = (object.y > bounds.y);
    bool bottomQuadrant = (object.y < bounds.y);

    if (object.x < bounds.x) {
        if (topQuadrant)
            index = 1;
        else if (bottomQuadrant)
            index = 2;
    } else if (object.x > bounds.x) {
        if (topQuadrant)
            index = 0;
        else if (bottomQuadrant)
            index = 3;
    }

    return index;
}

void Quadtree::insert(Organism *iter) {
    if (!nodes[0].isNull) {
        int index = getIndex((*iter).getRectangle());
        if (index != -1) {
            nodes[index].insert(iter);
            return;
        }
    }

    objects.emplace_back(iter);

    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        if (nodes[0].isNull)
            split();

        int index;
        for (auto it = objects.begin(); it != objects.end(); it++) {
            index = getIndex((*it)->getRectangle());
            if (index != -1) {
                nodes[index].insert(*it);
                objects.erase(it--);
            }
        }
    }
}

std::vector<Rectangle> Quadtree::Draw() {
    std::vector<Rectangle> retdat;
    int i;
    for (i = 0; i < 4; i++) {
        if (!nodes[i].isNull) {
            std::vector<Rectangle> temp = nodes[i].Draw();
            retdat.insert(retdat.end(), temp.begin(), temp.end());
        }
    }
    if (!nodes[0].isNull)
        retdat.emplace_back(nodes[0].rect);
    if (!nodes[1].isNull)
        retdat.emplace_back(nodes[1].rect);
    if (!nodes[2].isNull)
        retdat.emplace_back(nodes[2].rect);
    if (!nodes[3].isNull)
        retdat.emplace_back(nodes[3].rect);
    retdat.emplace_back(rect);
    return retdat;
}

std::vector<Organism *> Quadtree::retrieve(std::vector<Organism *> returnObjects, Rectangle obj) {
    int index = getIndex(obj);
    if (index != -1 && !nodes[0].isNull)
        returnObjects = nodes[index].retrieve(returnObjects, obj);

    for (auto &object : objects)
        returnObjects.emplace_back(object);

    return returnObjects;
}
