/*
* Author: Changhyun Park
* Date: 5/20/2022
*
* CLASS INVARIANT:
*                 - The constructor encapsulates some number of internally generated, distinct gridFlea objects.
*                   It systematically generates different values for subobject gridFlea.
*
*                 - inFest object revive all inactivated gridFleas when more than half of its gridFleas are deactivated.
*
*                 - Each inFest object manages its gridFleas. For example, if inFest object moves p, all its subobject gridFleas
                    move p as well.
                  - if client specify size to less than or equal to 1, the number of subobject will be 1.

* Interface Invariant:
 *                  -
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "inFest.h"
#include <memory>
#include <vector>


/*
void testHeterogeneous(grid& mainGrid)
{
    vector<inFest*> heterogeneous;

    heterogeneous.push_back(new inFest(mainGrid));
    heterogeneous.push_back(new gridFlea(mainGrid));

    for (robot* oneRobot: heterogeneous){
        oneRobot->move();
        cout << typeid(*oneRobot).name() << endl;
        cout << "countMoves: " << oneRobot->getCountMoves() << endl;
    }

}
 */


void testCopyConstructor(inFest& inFestTest)
{
    cout << endl;
    cout << "Testing Copy Constructor" << endl;
    shared_ptr<inFest> r1 (new inFest(inFestTest));
    r1->move(2);
    inFest* r2 = new inFest(*r1);
    cout << "r1 maximum value: " << r1->value(VALUE_MAXIMUM) << endl;
    cout << "r2 maximum value: " << r2->value(VALUE_MAXIMUM) << endl;

    r2->move(1);
    cout << "r2 moved" << endl;
    cout << "r1 maximum value: " << r1->value(VALUE_MAXIMUM) << endl;
    cout << "r2 maximum value: " << r2->value(VALUE_MAXIMUM) << endl;
    r2->move(3);
    cout << "r1 maximum value: " << r1->value(VALUE_MAXIMUM) << endl;
    cout << "r2 maximum value: " << r2->value(VALUE_MAXIMUM) << endl;

}

void testAssignmentOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing Overloaded Assignment Operator" << endl;
    shared_ptr<inFest> inFest1 = make_shared<inFest>(inFestTest);
    inFest1->move(1);
    shared_ptr<inFest> inFest2 (inFest1);
    cout << "inFest1 maximum value: " << inFest1->value(VALUE_MAXIMUM) << endl;
    cout << "inFest2 maximum value: " << inFest2->value(VALUE_MAXIMUM) << endl;
}

void testLessThanOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing < Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14

    cout << "inFest1 < inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) < inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 < *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14

    cout << "flea1 < flea2, expected: " << (flea1->value() < flea2->value())
         << ", actual: " << (*flea1 < *flea2) << endl;
}

void testGreaterThanOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing > Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14

    cout << "inFest1 > inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) > inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 > *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14

    cout << "flea1 > flea2, expected: " << (flea1->value() > flea2->value())
         << ", actual: " << (*flea1 > *flea2) << endl;
}

void testGreaterThanOrEqualToOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing >= Operator" << endl;

    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14

    cout << "inFest1 >= inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) >= inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 >= *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14

    cout << "flea1 >= flea2, expected: " << (flea1->value() >= flea2->value())
         << ", actual: " << (*flea1 >= *flea2) << endl;
}

void testLessThanOrEqualToOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing <= Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14

    cout << "inFest1 <= inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) <= inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 <= *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14

    cout << "flea1 <= flea2, expected: " << (flea1->value() <= flea2->value())
         << ", actual: " << (*flea1 <= *flea2) << endl;
}

void testEqualEqualOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing == Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14
    inFest2->move(10);

    cout << "inFest1 == inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) == inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 == *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14

    cout << "flea1 == flea2, expected: " << (flea1->value() == flea2->value())
         << ", actual: " << (*flea1 == *flea2) << endl;
}

void testNotEqualOperator(gridFlea& fleaTest, inFest& inFestTest)
{
    cout << endl;
    cout << "Testing != Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14
    inFest2->move(20);

    cout << "inFest1 != inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) != inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 != *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest); // since c++14
    flea2->move(20);

    cout << "flea1 != flea2, expected: " << (flea1->value() != flea2->value())
         << ", actual: " << (*flea1 != *flea2) << endl;
}

void testGridFleaPlus(gridFlea& fleaTest)
{
    cout << endl;
    cout << "Testing gridFlea ++" << endl;
    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(1);
    cout << "BEFORE flea1 value: "<< flea1->value() << endl;

    ++*flea1;
    cout << "AFTER ++flea1, flea1 value: "<< flea1->value() << endl;

    //*flea1++;
    cout << "AFTER flea1++, flea1 value: "<< flea1->value() << endl;

    cout << endl;
    cout << "Testing gridFlea + int" << endl;
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest);
    flea2->move(10);
    cout << "BEFORE flea2 value: "<< flea2->value() << endl;
    *flea2+2;
    cout << "AFTER flea2 value: "<< flea2->value() << endl;
    *flea2+5;
    cout << "AFTER flea2 value: "<< flea2->value() << endl;

    cout << endl;
    cout << "Testing gridFlea += int" << endl;
    unique_ptr<gridFlea> flea3 = make_unique<gridFlea>(fleaTest); // since c++14
    flea3->move(1);
    cout << "BEFORE flea3 value: "<< flea3->value() << endl;
    *flea3 += 3;
    cout << "AFTER flea3 value: "<< flea3->value() << endl;

    cout << endl;
    cout << "Testing gridFlea += gridFlea" << endl;
    unique_ptr<gridFlea> flea4 = make_unique<gridFlea>(fleaTest); // since c++14
    flea4->move(1);
    cout << "flea4 value: "<< flea4->value() << endl;

    unique_ptr<gridFlea> flea5 = make_unique<gridFlea>(fleaTest); // since c++14
    flea5->move(3);
    cout << "flea5 value: "<< flea5->value() << endl;

    *flea4 += *flea5;
    cout << "flea4 value AFTER flea4 += flea5: " << flea4->value() << endl;

    cout << endl;
    cout << "Testing gridFlea + gridFlea" << endl;
    unique_ptr<gridFlea> flea6 = make_unique<gridFlea>(fleaTest); // since c++14
    flea6->move(1);

    unique_ptr<gridFlea> flea7 = make_unique<gridFlea>(fleaTest); // since c++14
    flea7->move(3);

    unique_ptr<gridFlea> flea8 = make_unique<gridFlea>(*flea6 + *flea7);

    cout << "flea6 value: " << flea6->value() << endl;
    cout << "flea7 value: " << flea7->value() << endl;
    cout << "flea8 = flea6 + flea7 value: " << flea8->value() << endl;
}


void testGridFleaMinus(gridFlea& fleaTest)
{
    // gridFlea-- and --gridFlea
    cout << endl;
    cout << "Testing gridFlea --" << endl;
    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(fleaTest); // since c++14
    flea1->move(1);
    cout << "BEFORE flea1 value: "<< flea1->value() << endl;

    --*flea1;
    cout << "AFTER --flea1, flea1 value: "<< flea1->value() << endl;

    //*flea1--;
    cout << "AFTER flea1--, flea1 value: "<< flea1->value() << endl;

    cout << endl;
    cout << "Testing gridFlea - int" << endl;
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(fleaTest);
    flea2->move(10);
    cout << "BEFORE flea2 value: "<< flea2->value() << endl;
    *flea2-2;
    cout << "AFTER flea2 value: "<< flea2->value() << endl;
    *flea2-5;
    cout << "AFTER flea2 value: "<< flea2->value() << endl;

    cout << endl;
    cout << "Testing gridFlea -= int" << endl;
    unique_ptr<gridFlea> flea3 = make_unique<gridFlea>(fleaTest);
    flea3->move(10);
    cout << "BEFORE flea3 value: "<< flea3->value() << endl;
    *flea3-=2;
    cout << "AFTER flea3 value: "<< flea3->value() << endl;
    *flea3-=5;
    cout << "AFTER flea3 value: "<< flea3->value() << endl;

    cout << endl;
    cout << "Testing Object -= Object" << endl;
    unique_ptr<gridFlea> flea4 = make_unique<gridFlea>(fleaTest);
    flea4->move(1);
    cout << "flea4 value: "<< flea4->value() << endl;

    unique_ptr<gridFlea> flea5 = make_unique<gridFlea>(fleaTest);
    flea5->move(3);
    cout << "flea5 value: "<< flea5->value() << endl;

    *flea4 -= *flea5;
    cout << "flea4 value AFTER flea4 -= flea5: " << flea4->value() << endl;

    cout << endl;
    cout << "Testing gridFlea - gridFlea" << endl;
    unique_ptr<gridFlea> flea6 = make_unique<gridFlea>(fleaTest);
    flea6->move(1);

    unique_ptr<gridFlea> flea7 = make_unique<gridFlea>(fleaTest);
    flea7->move(3);

    unique_ptr<gridFlea> flea8 = make_unique<gridFlea>(*flea6 - *flea7);

    cout << "flea6 value: " << flea6->value() << endl;
    cout << "flea7 value: " << flea7->value() << endl;
    cout << "flea8 = flea6 - flea7 value: " << flea8->value() << endl;
}


void testInFestPlus(gridFlea& gridFleaTest,inFest& inFestTest)
{
    cout << endl;
    cout << "Testing inFest + inFest" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(inFestTest); // since c++14
    inFest1->move(3);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(inFestTest); // since c++14
    inFest2->move(5);

    cout << endl;

    cout << "BEFORE Number of total fleas in flea1: " << inFest1->getNumOfFlea() << endl;
    cout << "BEFORE Number of total fleas in flea2: " << inFest2->getNumOfFlea() << endl;

    cout << "inFest3 = inFest1 + inFest2" << endl;
    unique_ptr<inFest> inFest3 = make_unique<inFest>(*inFest1 + *inFest2);
    cout << "Number of inFest3 AFTER: " << inFest3->getNumOfFlea() << endl;


    cout << endl;
    cout << "Testing inFest += inFest" << endl;
    unique_ptr<inFest> inFest6 = make_unique<inFest>(inFestTest); // since c++14
    inFest6->move(3);
    unique_ptr<inFest> inFest7 = make_unique<inFest>(inFestTest); // since c++14
    inFest7->move(5);
    cout << "BEFORE Number of total fleas in inFest6: " << inFest6->getNumOfFlea() << endl;
    cout << "BEFORE Number of total fleas in inFest7: " << inFest7->getNumOfFlea() << endl;
    *inFest6 += *inFest7;
    cout << "inFest6 += inFest7" << endl;
    cout << "AFTER Number of total fleas in inFest6 : " << inFest6->getNumOfFlea() << endl;
    cout << "AFTER Number of total fleas in inFest7 : " << inFest7->getNumOfFlea() << endl;






    /*
    // TODO: inFest + gridFlea
    cout <<"Testing inFest + gridFlea" << endl;
    unique_ptr<inFest> inFest4 = make_unique<inFest>(inFestTest);
    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(gridFleaTest);
    //unique_ptr<inFest> inFest5 = make_unique<inFest>(*inFest4 + *flea1);
    unique_ptr<inFest> inFest5 = *inFest4 + *flea1;
    cout << "AFTER Number of inFest5:t5 " << inFest5->getNumOfFlea() << endl;
    */

    // TODO: inFest ++ gridFlea
}

void testFunctionality(inFest& inFestTest)
{
    inFest inFestTest2 = inFest(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    inFest inFestTest3 = inFest(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    inFest inFestTest4 = inFest(rand() % 10, rand() % 10, rand() % 10, rand() % 10);

    cout << "The number of fleas in inFestTest: "<< inFestTest.getNumOfFlea() << endl;
    cout << "The number of fleas in inFestTest2: "<< inFestTest2.getNumOfFlea() << endl;
    cout << "The number of fleas in inFestTest3: "<< inFestTest3.getNumOfFlea() << endl;
    cout << "The number of fleas in inFestTest4: "<< inFestTest4.getNumOfFlea() << endl;

    vector<inFest*> heterogeneous;

    heterogeneous.push_back(new inFest(inFestTest));
    heterogeneous.push_back(new inFest(inFestTest2));
    heterogeneous.push_back(new inFest(inFestTest3));
    heterogeneous.push_back(new inFest(inFestTest4));

    for (inFest* oneRoot: heterogeneous)
    {
        oneRoot->move(3);
        cout << typeid(*oneRoot).name() << endl;
        cout << "The number of fleas: " << oneRoot->getNumOfFlea() << endl;
        cout << "The number of alive fleas: " << oneRoot->getNumOfAliveFlea() << endl;

        oneRoot->move(5);
        cout << typeid(*oneRoot).name() << endl;
        cout << "The number of fleas: " << oneRoot->getNumOfFlea() << endl;
        cout << "The number of alive fleas: " << oneRoot->getNumOfAliveFlea() << endl;
    }
}

// TODO: DOCUMENTATION, inFest mix type operator
int main(void)
{

    srand((unsigned int)time(NULL));

    inFest inFestTest = inFest(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
    gridFlea gridFleaTest = gridFlea(rand() % 10,rand() % 10,rand() % 10);

    testFunctionality(inFestTest);

    testCopyConstructor(inFestTest);
    cout << " ************************************************* " << endl;
    testAssignmentOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testLessThanOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testGreaterThanOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testGreaterThanOrEqualToOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testLessThanOrEqualToOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testEqualEqualOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    testNotEqualOperator(gridFleaTest, inFestTest);
    cout << " ************************************************* " << endl;
    cout << " ************************************************* " << endl;
    testGridFleaMinus(gridFleaTest);
    cout << " ************************************************* " << endl;
    testGridFleaPlus(gridFleaTest);
    cout << " ************************************************* " << endl;

    cout << " ************************************************* " << endl;
    testInFestPlus(gridFleaTest, inFestTest);


    cout << " ************************************************* " << endl;





    return 0;
}