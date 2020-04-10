#ifndef organism_h
#define organism_h

#include <vector>
#include <algorithm>

#include "dna.hpp"
#include "rectangle.hpp"
#include "functions.hpp"

class Organism {
public:
    Organism(Rectangle r, DNA d);

    void Behavior();

    void Action();

    void Priority();

    void setTarget();

    void checkTarget();

    void moveTowards(Rectangle r);

    void passDNA(DNA d);

    void giveNearMe(std::vector<Organism *> n) { nearMe = n; };

    void grow();

    void takeBite(int bite);

    void hadPregnancy() { pregnate = pregnancyReady = false; };

    DNA getDNA() { return myDNA; };

    DNA getChildsDNA() { return childsDNA; };

    DNA::Visuals getVisuals() {
        if (getType() == CORPSE_TYPE) {
            return {((float) health / 4.0f / 100.f),
                    0.0f,
                    0.0f};
        }

        if (getType() == PLANT_TYPE) {
            if (health >= 100) {
                return myDNA.appearance;
            } else {
//                return {1.0f - ((float) health / 100.0f),
//                        1.0f - ((float) health / 100.0f),
//                        1.0f - ((float) health / 100.0f)};
                return  {myDNA.appearance.red*((float)(100.0f-health)/100.0f),
                         myDNA.appearance.green*((float)(100.0f-health)/100.0f),
                         myDNA.appearance.blue*((float)(100.0f-health)/100.0f)};
            }
        }

        if (getType() == CARNIVORE_TYPE || getType() == HERBAVORE_TYPE) {
            float vitaliy = ((float) health / 100.0f);
                return {myDNA.appearance.red * vitaliy,
                        myDNA.appearance.green * vitaliy,
                        myDNA.appearance.blue * vitaliy};;
        }
        return {
                myDNA.appearance.red,
                myDNA.appearance.green,
                myDNA.appearance.blue
        };
    };

    Rectangle getRectangle() { return rect; };

    int getHealth() { return health; };

    int getBestSense() { return myDNA.bestSense; };

    int getType() { return myDNA.type; };

    bool getGender() { return gender; };

    bool getPregnancyReady() { return pregnancyReady; };

private:
    Rectangle wTarget;
    Organism *target;
    std::vector<Organism *> nearMe;
    DNA myDNA;
    DNA childsDNA;
    Rectangle rect;

    int health;
    int pregnancyTime;
    int age;
    int hunger;

    bool starving;
    bool gender;
    bool pregnate;
    bool hungry;
    bool pregnancyReady;
    bool able;
    bool hasTarget;
    bool wander;

    void starve();
};

#endif
