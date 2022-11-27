#ifndef P2_DUELINGJP_H
#define P2_DUELINGJP_H
#include "JumpPrime.h"
#include <vector>
#include <memory>

// Author: Joan Omley
// Filename: DuelingJP.h
// Version: v1
// Description: This class holds a number of JumpPrime objects. The number current num in each object can be queried
//              as normal. The up() and down() values can also be compared to count the number of collisions and
//              inversions.

using namespace std;

class DuelingJP {
    // Class invariant : This class encapsulates a vector of structs named Holder. Each holder has a shared pointer of a
    //              JumpPrime object and the values of the next and previous prime numbers of that JumpPrime object's
    //              current number. up() and down() calls can be made to all JumpPrime objects in each Holder in the
    //              vector, and all Holder values will be updated. All up and down values can also be compared to see
    //              the number of collisions and inversions. Collisions are when more than one Holder contains the same
    //              up or down value. Inversions are when an up or down value in a Holder is the same as the opposite
    //              value in another Holder.
    public:
        DuelingJP(vector<shared_ptr<JumpPrime>>);
        DuelingJP(DuelingJP& djp);
        string showVectors();
        int collisions();
        int inversions();
        int allUp();
        int allDown();
        void reviveAll();
        void resetAll();
        void operator += (shared_ptr<JumpPrime>);
        void operator += (shared_ptr<DuelingJP>);
        void operator ++ ();
        bool operator == (DuelingJP &dj);
        bool operator != (DuelingJP &dj);
        bool operator < (DuelingJP &dj);
        bool operator > (DuelingJP &dj);
        bool operator <= (DuelingJP &dj);
        bool operator >= (DuelingJP &dj);
    private:
        // struct to hold a JumpPrime object and that objects current up() and down() values
        struct Holder {
            shared_ptr<JumpPrime> jPrime;
            int up;
            int down;
        };
        // pointer to array that will hold Holder objects
        Holder* jPrimeObjs;
        // size of jPrimObjs. used for constructor and copy constructor
        int lenJPrimeObjs;

};

#endif //P2_DUELINGJP_H
