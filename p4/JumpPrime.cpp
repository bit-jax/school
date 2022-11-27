#include <iostream>
#include "JumpPrime.h"

// Author: Joan Omley
// Filename: jumpPrime.cpp
// Version: v1
// Description: Implementation of the JumpPrime class.

// Implementation invariant: When object is created or when a number jumps, the closest prime numbers before and after currentNum are calculated
//                           with primeUp() and primeDown() and assigned to nextPrime and prevPrime. The difference between the two numbers is
//                           then calculated by getRange() anJumpPrime::d assigned to primeRange. After a number of queries equal to primeRange, currentNum jumps
//                           up or down, depending on whether up() or down() was the last query made. The distance jumped is equal to primeRange. After
//                           the jump, numJumps increments, numQuerries resets, and the process repeats. After 3 jumps, the object deactivates and cannot
//                           be querried again until the object is revived or reset. Revive() reactivates the object and sets the jumps and queries back to 0.
//                           Calling revive on an active object kills it. It cannot be revived and can only be reset. Reset() returns the object to its original
//                           state at construction.

JumpPrime::JumpPrime(int encap)
{
    // if a number below 1000 is given, assigns a default value.
    if (encap >= 100)
    {
        encapsulated = encap;
        currentNum = encap;
    }
    else
    {
        encapsulated = 4242;
        currentNum = 4242;
    }
    numQueries = 0;
    // status is set to active
    activeStatus = true;
    // object starts alive
    isDead = false;
    // the number of jumps set to 0
    numJumps = 0;
    // the next prime is calculated and saved
    nextPrime = primeUp();
    // the previous prime is calculated and saved
    prevPrime = primeDown();
    // the range between the next and previous primes is calculated and saved
    primeRange = nextPrime - prevPrime;
};

// makes a deep copy by copying all values of copied object
JumpPrime::JumpPrime(JumpPrime& j) {
    encapsulated = j.encapsulated;
    numQueries = j.numQueries;
    currentNum = j.currentNum;
    activeStatus = j.activeStatus;
    isDead = j.isDead;
    numJumps = j.numJumps;
    primeRange = j.primeRange;
    nextPrime = j.nextPrime;
    prevPrime = j.prevPrime;
}

// adds currentNum of two objects together and makes that the currentNum value of the first
void JumpPrime::operator += (JumpPrime &j) {
    currentNum += j.currentNum;
    getRange();
    nextPrime = primeUp();
    prevPrime = primeDown();
};

// increments currentNum and adjusts range and nextPrim and prevPrime as necessary
void JumpPrime::operator ++() {
    currentNum++;
    getRange();
    nextPrime = primeUp();
    prevPrime = primeDown();
}

// returns true if two objects currentNum is the same
bool JumpPrime::operator == (JumpPrime &j) {
     return (currentNum == j.currentNum);
}

// returns true if two objects currentNum are not the same
bool JumpPrime::operator != (JumpPrime &j) {
    return (currentNum != j.currentNum);
}

// returns true if currentNum of first object is less than currentNum of the second
bool JumpPrime::operator < (JumpPrime &j) {
    return (currentNum < j.currentNum);
}

// returns true if currentNum of first object is greater than currentNum of the second
bool JumpPrime::operator > (JumpPrime &j) {
    return (currentNum > j.currentNum);
}

// returns true if currentNum of first object is less or equal to currentNum of the second
bool JumpPrime::operator <= (JumpPrime &j) {
    return (currentNum <= j.currentNum);
}

// returns true if currentNum of first object is greator than or equal to currentNum of the second
bool JumpPrime::operator >= (JumpPrime &j) {
    return (currentNum >= j.currentNum);
}
// Returns the closest prime number greater than currentNum. Counts as a query. If query limit is reached, currentNum
// increases by an amount equal to primeRange and numQuerries resets. If object is inactive or dead, return 1 or 0 respectively.
// Preconditions: The object must be active and not dead.
int JumpPrime::up()
{
    if (isDead)
    {
        return 0;
    }
    if (!activeStatus)
    {
        return 1;
    }

    if (numQueries <= primeRange)
    {
        numQueries++;
    }
    else
    {
        jumpUp();
    }

    return nextPrime;
}
// Returns the closest prime number less than currentNum. Counts as a query. If query limit is reached, currentNum
// decreases by an amount equal to primeRange and numQuerries resets. If object is inactive or dead, return 1 or 0 respectively.
// Preconditions: The object must be active and not dead.
int JumpPrime::down()
{
    if (isDead)
    {
        return 0;
    }
    if (!activeStatus)
    {
        return 1;
    }
    if (numQueries <= primeRange)
    {
        numQueries++;
        return  prevPrime;
    }
    else
    {
        jumpDown();
        return prevPrime;
    }
}
// Makes an inactive object active if used on an inactive object. Sets numQueries and numJumps back to 0. If used on an
// active object, deactivates it permanently and can no longer be revived and can only be reset().
// Preconditions: Object must be inactive and not dead to reactivate. Object must be alive to kill it.
void JumpPrime::revive()
{

    if (activeStatus)
    {
        isDead = true;
    }

    else
    {
        activeStatus = true;
        numQueries = 0;
        numJumps = 0;
    }
}
// Resets the object to its original state at construction. Resets currentNum to original encapsulated number,
// numJumps and numQuerries are set to 0, and nextPrime, prevPrime, and primeRange are recalculated.
void JumpPrime::reset()
{
    currentNum = encapsulated;
    numJumps = 0;
    numQueries = 0;
    nextPrime = primeUp();
    prevPrime = primeDown();
    getRange();
    activeStatus = true;
}

// Checks if currentNum is prime or not.
bool JumpPrime::checkPrime(int checkNum)
{
    if (checkNum == 2 | checkNum == 0 | checkNum == 1)
        return true;
    for (int i = 2; i <= checkNum/2; i++)
    {
        if (checkNum % i == 0)
        {
            return false;
        }
    }
    return true;
}
// Gets the difference between nextPrime and prevPrime
int JumpPrime::getRange()
{
    primeRange = primeUp() - primeDown();
    return 0;
}
// Calculates the closest prime number above currentNum and saves it as nextPrime.
int JumpPrime::primeUp()
{

    if (checkPrime(currentNum))
    {
        return currentNum;
    }

    for (int i = currentNum + 1; i <= 100000; i++)
    {
        if (checkPrime(i))
        {
            return i;
        }
    }
    return 0;
}
// Calculates the closest prime number below currentNum and saves it as prevPrime.
int JumpPrime::primeDown()
{

    if (checkPrime(currentNum))
    {
        return currentNum;
    }

    for (int i = currentNum - 1; i > 0; i--)
    {
        if (checkPrime(i))
        {
            return i;
        }
    }
    return 0;
}
// Increases currentNum by an amount equal to primeRange. Makes calls to primeUp(), primeDown(), and getRange() to reasign their values to match with
// the new currentNum. However, if there have been more than two jumps, it deactives the object.
// Preconditions: Must have been less than two jumps already otherwise the object will be deactivated.
int JumpPrime::jumpUp()
{
    if (numJumps >= 2)
    {
        turnOff();
        return 0;
    }
    if (nextPrime == prevPrime)
    {
        currentNum++;
    }
    getRange();
    currentNum += primeRange;
    nextPrime = primeUp();
    prevPrime = primeDown();
    getRange();
    numQueries = 0;
    numJumps++;
    return 0;
}
// Decreases currentNum by an amount equal to primeRange. Makes calls to primeUp(), primeDown(), and getRange() to reasign their values to match with
// the new currentNum. However, if there have been more than two jumps, it deactives the object.
// Preconditions: Must have been less than two jumps already otherwise the object will be deactivated.
int JumpPrime::jumpDown()
{
    if (numJumps >= 2)
    {
        turnOff();
        return 0;
    }
    if (nextPrime == prevPrime)
    {
        currentNum++;
    }
    currentNum -= primeRange;
    numQueries = 0;
    nextPrime = primeUp();
    prevPrime = primeDown();
    getRange();
    numQueries = 0;
    numJumps++;
    return 0;
}
// Deactivates the object.
int JumpPrime::turnOff()
{
    activeStatus = false;
    return 0;
}
