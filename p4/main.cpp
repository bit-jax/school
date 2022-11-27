#include <iostream>
#include <string>
#include <memory>
#include "JumpPrime.h"
#include "DuelingJP.h"
using namespace std;
string testUp(JumpPrime);
string testDown();
string testReset();
string testRevive();
int randomNum();

// this calls several functions to test the different capabilites of DueilingJP and JumpClass.
int main() {


    // create two jump prime objects and test comparison functions then test adding t2 to t1
    JumpPrime tjp1(5524);
    JumpPrime tjp2(5520);
    cout << (tjp1 == tjp2) << endl;
    cout << (tjp1 != tjp2) << endl;
    cout << (tjp1 > tjp2) << endl;
    cout << (tjp1 < tjp2) << endl;
    cout << (tjp1 >= tjp2) << endl;
    cout << (tjp1 <= tjp2) << endl;

    tjp1+=tjp2;
    cout << testUp(tjp1);


    // test of DuelingJP

//     create JumpPrime objects to add to a vector to pass to DuelingJP objects
    shared_ptr<JumpPrime> t1(new JumpPrime(5524));
    shared_ptr<JumpPrime> t2(new JumpPrime(5520));
    // unique_ptr created and move()ed to a shared pointer
    unique_ptr<JumpPrime> ut3(new JumpPrime(5526));
    shared_ptr<JumpPrime> t3 (move(ut3));
    shared_ptr<JumpPrime> t4(new JumpPrime(5518));
    // vector created and JumpPrime object pushed to it
    vector<shared_ptr<JumpPrime>> testVec;
    testVec.push_back(move(t1));
    testVec.push_back(move(t2));
    testVec.push_back(move(t3));
    testVec.push_back(move(t4));
//    // DuelingJP object created and copy of it created
    shared_ptr<DuelingJP> d1(new DuelingJP(move(testVec)));
//    shared_ptr<JumpPrime> t5(new JumpPrime(5528));
//    vector<shared_ptr<JumpPrime>> tv2;
//    tv2.push_back(t5);
    shared_ptr<DuelingJP> d2(d1);
//
//    //DuelingJP d2(d1);
////    shared_ptr<DuelingJP> d2(new DuelingJP(move(tv2)));
//    DuelingJP d2(testVec);
//    shared_ptr<DuelingJP> sp2 = d2;
//    d1+=d2;
    
//    shared_ptr<DuelingJP> d2(d1);
//    // up and down primes of each JumpPrime object
    cout << "up and down values of all JumpPrime object encapsulated in d1:" << endl;
    cout << d1->showVectors() << endl;
    cout << "There are " + to_string(d1->inversions()) + " inversions in d1." << endl << endl;

    // This calls d2 and increments all JumpPrime objects and recounts inversions
    cout << "Initial up and down values of all JumpPrime objects encapsulated in d2: " << endl;
    cout << d2->showVectors() << endl;
    for (int i = 0; i < 15 ; i++) {
        d2->allUp();
    }
    cout << "After 15 allUp() calls to d2, all up and down values are now: " << endl;
    cout << d2->showVectors() << endl;
    cout << "d2 now has " << d2->inversions() << " inversions." << endl;

    // Test of JumpPrime

    cout << "\n\n*** testing JumpPrime class ***\n\n";

    cout << "Testing JumpPrime copy constructor. After enough up queries are made to j1 to cause it to jump, j2 \n"
            "j1 is called once to show it has original value and wasn't affected by calls to j1 (is a deep copy\n";
    shared_ptr<JumpPrime> j1(new JumpPrime(3333));
    JumpPrime j2(*j1);
    for (int i = 0; i < 15 ; i++) {
        cout << j1->up() << endl;
    }

    cout << j2.up() << endl;
    cout << testUp(j2);
    cout << testDown();
    cout << testReset();
    cout << testRevive();

    return 0;
}
        // This tests the up() method. It creates an object with a random number and makes 36 up() queries.
        // It should demonstrate how it displays the next prime number, jumps to another number after a number of queries,
        // and then deactivates after 2 jumps.
        string testUp(JumpPrime j)
        {
            int testInt = randomNum();
            string output = "Testing 56 up queries:\n";
            JumpPrime testPrime1(testInt);
            for (int i = 0; i <= 55; i++)
            {
                output += to_string(j.up()) + "\n";
            }
            return output;
        }
        // This tests the down() method. It creates an object with a random number and makes 36 down() queries.
        // It should demonstrate how it displays the previous prime number, jumps to another number after a number of queries,
        // and then deactivates after 2 jumps.
        string testDown()
        {
            int testInt = randomNum();
            string output = "Testing 56 down queries:\n"; ;
            JumpPrime testPrime2(testInt);
            for (int i = 0; i <= 55; i++)
            {
                output += to_string(testPrime2.up()) + "\n";
            };
            return output;
        }
        // This tests the reset() method. After enough queries have been made to deactivate an object,
        // it calls reset() and then another query to show that the object is reactivated
        // and the number has been reset to its original encapsulated value
        string testReset()
        {
            int testInt = randomNum();
            string output = "Testing reset (a '1' indicates object is inactive):\n";
            JumpPrime testPrime3(testInt);
            for (int i = 0; i <= 35; i++)
            {
                output += to_string(testPrime3.up()) + "\n";
            };
//            output += testPrime3.reset() + "\n" + testPrime3.up() + "\n";


            return output;
        }
        // Tests the revive() method. After enough queries have been made to deactive an object, revive() is called
        // and more queries are called to show that the object is active again. Then revive() is called on the active
        // object which kills it. Another query and revive() attempt are made to show that it is dead and cannot be
        // reactivated.
        string testRevive()
        {
            int testInt = randomNum();
            string output = "Testing reviving an inactive object then killing it by calling revive on an active "
                            "object.\nA '1' value indicates object is inactive. A '0' means it is permanently dead\n";
            JumpPrime testPrime4(testInt);
            for (int i = 0; i <= 60; i++)
            {
                output += to_string(testPrime4.up()) + "\n";
            };
//            output += testPrime4.revive() + "\n";
            testPrime4.revive();
            for (int i = 0; i <= 5; i++)
            {
                output += to_string(testPrime4.up()) + "\n";
            };
//            output += testPrime4.revive() + "\n";
            testPrime4.revive();
            output += to_string(testPrime4.down()) + "\n";
            return output;
        }
        // function for generating a random number
        int randomNum()
        {
            srand(time(NULL));
            return 100 + rand() % 9000;
//            Random r = new Random();
//            return r.Next(1000, 9999);
        }

