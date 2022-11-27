#include "DuelingJP.h"
#include <vector>
#include <memory>
#include <algorithm>

// Author: Joan Omley
// Filename: DuelingJP.cpp
// Version: v1
// Description: Implementation for DuelingJP class

// Implementation invariant:  Object is initialized with a vector of shared pointers to JumpPrime objects. Each item
//                  of the vector is saved to a Holder struct along with the values returned from up() and down() calls.
//                  The Holder is then placed in the vector jPrimeObjs. Calls can be made to find the number of
//                  collisions() or inversions() of all JumpPrime objects, and all JumpPrime functions can be called on
//                  all objects as well.

// constructor
// Preconditions: JumpPrime object required for creation
DuelingJP::DuelingJP(vector<shared_ptr<JumpPrime>> jpVec) {
    jPrimeObjs = new Holder[jpVec.size()];
    lenJPrimeObjs = jpVec.size();
    for (int i = 0; i < jpVec.size();i++) {
        // for each object in jpVec, it is added to a Holder and up() and down() values are added as well
        struct Holder jp = {jpVec.at(i),jpVec.at(i)->up(),jpVec.at(i)->down()};
        jPrimeObjs[i]= jp;
    }
}

// copy constructor
// Preconditions: JumpPrime object required for creation
DuelingJP::DuelingJP(DuelingJP &djp) {
    for (int i = 0; i < djp.lenJPrimeObjs;i++) {
        struct Holder jp = {shared_ptr<JumpPrime>(djp.jPrimeObjs[i].jPrime),djp.jPrimeObjs[i].up,djp.jPrimeObjs[i].down};
        jPrimeObjs[i] = jp;
    }
}

// adds a new jumpprime object to jPrimeObjs
void DuelingJP:: operator += (shared_ptr<JumpPrime> j) {
    Holder* temp = new Holder[lenJPrimeObjs+1];
    for (int i = 0; i < lenJPrimeObjs; i++) {
        temp[i] = jPrimeObjs[i];
    }
    struct Holder jp = {j,j->up(),j->down()};
    temp[lenJPrimeObjs] = jp;
    jPrimeObjs = temp;
    delete[] temp;
}

// adds j.jPrimeObjs to jPrimeObjs
void DuelingJP::operator+=(shared_ptr<DuelingJP> j) {
    Holder* temp = new Holder[lenJPrimeObjs];
    for (int i = 0; i < lenJPrimeObjs; i++) {
        temp [i] = jPrimeObjs[i];
    }
    int y = 0;
    for (int i = lenJPrimeObjs; i < (lenJPrimeObjs + j->lenJPrimeObjs); i++) {
        temp[i] = j->jPrimeObjs[y];
        y++;
    }
    lenJPrimeObjs += j->lenJPrimeObjs;
    jPrimeObjs = temp;
    delete[] temp;
}

// shows current num and the up and down values for each JumpPrime object
string DuelingJP::showVectors() {
    string vecs = "";
    for (int i = 0; i < lenJPrimeObjs;i++) {
        vecs += "up: " + to_string(jPrimeObjs[i].up) + " " + "down: " + to_string(jPrimeObjs[i].down) + "\n";
    }
    return vecs;
}

// counts the number of collisions of all objects.
int DuelingJP::collisions() {
    // vector to hold numbers that have already been evaluated so they don't get counted twice
    vector<int> nums;
    // number of collisions
    int numCount = 0;
    // loops through each Holder and compares its up value with all other Holder's up values.
    for (int i = 0; i < lenJPrimeObjs; i++) {
        // looks in nums to see if the number has already been evaluated
        if (find(nums.begin(),nums.end(),jPrimeObjs[i].up) == nums.end()) {
            // if not found in nums loops through remaining unevaluated Holders
            for (int j = i+1; j < lenJPrimeObjs; j++) {
                // if it matches, increments counter
                if (jPrimeObjs[i].up == jPrimeObjs[j].up) {
                    numCount++;
                }
            }
            // the number is pushed to nums to not get counted again
            nums.push_back(jPrimeObjs[i].up);
        }
    }
    // nums is cleared to reuse to check for down values
    nums.clear();
    // code functions just like checking for up values
    for (int i = 0; i < lenJPrimeObjs; i++) {
        if (find(nums.begin(),nums.end(),jPrimeObjs[i].down) == nums.end()) {
            for (int j = i+1; j < lenJPrimeObjs; j++) {
                if (jPrimeObjs[i].down == jPrimeObjs[j].down) {
                    numCount++;
                }
            }
            nums.push_back(jPrimeObjs[i].down);
        }
    }
    // memory is cleared by swapping nums to an unnamed temp vector that will disapear
    vector<int>().swap(nums);
    return numCount;
}

// counts the number of inversions of all JumpPrime objects
int DuelingJP::inversions() {
    // vector for up values and one for down values
    vector<int> numsUp;
    vector<int> numsDown;

    // used for loops
    const int numObjs = lenJPrimeObjs;
    // number of inversions
    int numCount = 0;
    // fills both vectors with up and down values
    for (int i = 0; i < numObjs; i++) {
        numsUp.push_back(jPrimeObjs[i].up);
        numsDown.push_back(jPrimeObjs[i].down);
    }
    // compares each up value to each down value and increments count if there's a match
    for (int i = 0; i < numObjs; i++) {
        for (int j = 0; j < numObjs; j++) {
            if (numsDown[j] == numsUp[i]){
                numCount++;
            }
        }
    }
    // clears memory for both vectors
    vector<int>().swap(numsUp);
    vector<int>().swap(numsDown);
    return numCount;
}

// calls up() for each JumpPrime object in each Holder
int DuelingJP::allUp() {
    for (int i = 0; i < lenJPrimeObjs; i++) {
        jPrimeObjs[i].up = jPrimeObjs[i].jPrime->up();
    }
    return 0;
}

// calls down() for each JumpPrime object in each Holder
int DuelingJP::allDown() {
    for (int i = 0; i < lenJPrimeObjs; i++) {
        jPrimeObjs[i].down = jPrimeObjs[i].jPrime->down();
    }
    return 0;
}

// calls reset on all JumpPrime objects
void DuelingJP::resetAll() {
    for (int i = 0; i < lenJPrimeObjs; i++) {
        jPrimeObjs[i].jPrime->reset();
    }
}

// calls revive on all JumpPrime objects
void DuelingJP::reviveAll() {
    for (int i = 0; i < lenJPrimeObjs; i++) {
        jPrimeObjs[i].jPrime->revive();
    }
}