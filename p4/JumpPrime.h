
#ifndef P2_JUMPPRIME_H
#define P2_JUMPPRIME_H
#include <string>

using namespace std;

// Author: Joan Omley
// Filename: jumpPrime.h
// Version: v1
// Description: This class takes a number at construction and calculates the closest previous and next prime numbers.
//              The prime numbers can be viewed by the client, but after a certain number of queries, the number will jump
//              a new number. After a number of jumps, the object will be deactivated. Methods to revive, kill, and reset
//              the object are also provided.

class JumpPrime {
// Class invariant: This object encapsulates a number, which becomes the number to be evaluated at construction (currentNum).
    //                  This number can change after a certain number of queries are run, but can be reset to the original by calling reset().
    //                  The next and previous closest prime numbers from currentNum are calculated and can be queried by the client.
    //                  After the number of queries equals the difference between the next prime and previous prime are reached, currentNum jumps.
    //                  The distance it jumps is the difference between the next and previous primes. After the jump, the new next and previous primes
    //                  are calculated and the number of queries resets. After 3 jumps, the object will deactivate. Calling revive will reactivate it.
    //                  Calling revive on an active object permanently deactivates (kills) the object.


    // Interface invariant: The client creates an object with the encapsulated number as the only parameter. The client can view the next and previous
    //                      primes. They can also revive() inactive objects, reset() any object, or kill an active object (calling revive() on an active object.
    //                      Assumes the client encapsulates a number of at least 4 digits.
    //                      A return value of 0 or 1 from an up() or down() call means the object is dead or inactive respectively.
public:
    JumpPrime(int);
    JumpPrime(JumpPrime &j);
    int up();
    int down();
    void revive();
    void reset();
    void operator += (JumpPrime &j);
    void operator ++ ();
    bool operator == (JumpPrime &j);
    bool operator != (JumpPrime &j);
    bool operator < (JumpPrime &j);
    bool operator > (JumpPrime &j);
    bool operator >= (JumpPrime &j);
    bool operator <= (JumpPrime &j);

private:
    // this is the original encapsulated number used during object creation
    int encapsulated;
    // the number of times the nearest primes has been calculated
    int numQueries;
    // this is the current number being queried. starts as the encapsulated number
    int currentNum;
    // numbers become inactive after a number of queries. this tracks if it has been deactivated or not
    bool activeStatus;
    // dead number is inactive and cannot be revived
    bool isDead;
    // number of times a currentNum has jumped
    int numJumps;
    // range between the next and previous primes
    int primeRange;
    // the next closest prime number
    int nextPrime;
    // the previous closest prime number
    int prevPrime;
    int primeUp();
    int primeDown();
    int jumpUp();
    int jumpDown();
    int turnOff();
    int getRange();
    bool checkPrime(int);
};

#endif //P2_JUMPPRIME_H
