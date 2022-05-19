/*
* Author: Changhyun Park
* Date: 5/19/2022
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
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "inFest.h"
#include <memory>
#include <vector>





void testing()
{
    cout << "This is testing" << endl;
    inFest inFestMove[5];
    for (int i = 0; i < 5; i++)
    {
        inFestMove[i] = inFest(i + rand() % 8 + 5, i ^ 2, rand() % 80 + 1, rand() % 20 + 1);

        inFestMove[i].move(rand() % 100 + 1);
        cout << "Minimum value: " << inFestMove[i].value(VALUE_MINIMUM) << endl;
        cout << "Maximum value: " << inFestMove[i].value(VALUE_MAXIMUM) << endl;
        cout << endl;
        inFestMove[i].move(rand() % 77 + 1);
        cout << "Minimum value: " << inFestMove[i].value(VALUE_MINIMUM) << endl;
        cout << "Maximum value: " << inFestMove[i].value(VALUE_MAXIMUM) << endl;
        cout << endl;
        inFestMove[i].move(rand() % 66 + 1);
        cout << "Minimum value: " << inFestMove[i].value(VALUE_MINIMUM) << endl;
        cout << "Maximum value: " << inFestMove[i].value(VALUE_MAXIMUM) << endl;
        cout << endl;
    }
}

// TODO: FIX
void testCopyConstructor(inFest& mainGrid)
{
    cout << "Testing Copy Constructor" << endl;
    shared_ptr<inFest> r1 (new inFest(mainGrid));
    r1->move(2);
    inFest* r2 = new inFest(*r1);
    cout << "r1 maximum value: " << r1->value(VALUE_MAXIMUM) << endl;
    cout << "r2 maximum value: " << r2->value(VALUE_MAXIMUM) << endl;
}

void testAssignmentOperator()
{
    cout << "Testing Overloaded Assignment Operator" << endl;
    shared_ptr<inFest> r1 = make_shared<inFest>(0,0,50,3);
    r1->move(1);
    shared_ptr<inFest> r2 (r1);
    cout << "r1 maximum value: " << r1->value(VALUE_MAXIMUM) << endl;
    cout << "r2 maximum value: " << r2->value(VALUE_MAXIMUM) << endl;
}

void testLessThanOperator()
{
    cout << "Testing < Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14

    cout << "inFest1 < inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) < inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 < *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14

    cout << "flea1 < flea2, expected: " << (flea1->value() < flea2->value())
         << ", actual: " << (*flea1 < *flea2) << endl;
}

void testGreaterThanOperator()
{
    cout << "Testing > Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14

    cout << "inFest1 > inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) > inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 > *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14

    cout << "flea1 > flea2, expected: " << (flea1->value() > flea2->value())
         << ", actual: " << (*flea1 > *flea2) << endl;
}

void testGreaterThanOrEqualToOperator()
{
    cout << "Testing >= Operator" << endl;

    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14

    cout << "inFest1 >= inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) >= inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 >= *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14

    cout << "flea1 >= flea2, expected: " << (flea1->value() >= flea2->value())
         << ", actual: " << (*flea1 >= *flea2) << endl;
}

void testLessThanOrEqualToOperator()
{
    cout << "Testing <= Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14

    cout << "inFest1 <= inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) <= inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 <= *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14

    cout << "flea1 <= flea2, expected: " << (flea1->value() <= flea2->value())
         << ", actual: " << (*flea1 <= *flea2) << endl;
}

void testEqualEqualOperator()
{
    cout << "Testing == Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest2->move(10);

    cout << "inFest1 == inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) == inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 == *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14

    cout << "flea1 == flea2, expected: " << (flea1->value() == flea2->value())
         << ", actual: " << (*flea1 == *flea2) << endl;
}

void testNotEqualOperator()
{
    cout << "Testing != Operator" << endl;
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest1->move(10);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(0,0,50,3); // since c++14
    inFest2->move(20);

    cout << "inFest1 != inFest2, expected: " << (inFest1->value(VALUE_MAXIMUM) != inFest2->value(VALUE_MAXIMUM))
         << ", actual: " << (*inFest1 != *inFest2) << endl;

    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);
    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14
    flea2->move(20);

    cout << "flea1 != flea2, expected: " << (flea1->value() != flea2->value())
         << ", actual: " << (*flea1 != *flea2) << endl;
}

void testObjectAddObject()
{
    cout << "Testing Object + Object" << endl;
    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);

    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14
    flea2->move(20);

    unique_ptr<gridFlea> flea3 = make_unique<gridFlea>(*flea1 + *flea2);
}

void testObjectAddObjectShortCut()
{
    cout << "Testing Object += Object" << endl;
    unique_ptr<gridFlea> flea1 = make_unique<gridFlea>(0,0,50); // since c++14
    flea1->move(10);

    unique_ptr<gridFlea> flea2 = make_unique<gridFlea>(0,0,50); // since c++14
    flea2->move(20);

    *flea1 += *flea2;

    flea1->move(3);
}

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

void tmpTesting()
{
    cout << "This is TMP testing" << endl;

    unique_ptr<inFest> inFestTmp[5];
    for (int i = 0; i < 5; i++)
    {
        inFestTmp[i] = make_unique<inFest>(i+1,i+5,i+300,1);
    }
    cout << "b4 move" << endl;
    inFestTmp[0]->move(10);
    cout << "moved 1" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 2" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 3" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 4" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 5" << endl;
    cout << endl;
    inFestTmp[0]->move(30);
    cout << "moved 6" << endl;
    cout << endl;

    inFestTmp[0]->move(10);
    cout << "moved 7" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 8" << endl;
    cout << endl;
    inFestTmp[0]->move(10);
    cout << "moved 9" << endl;
    cout << endl;
}



void fleaOperatorTesting()
{

    gridFlea g1(4,0,50);
    gridFlea g2(10,10,50);
    cout << "g1 value: " << g1.value() << endl;


    cout << "g3 = g1 + g2" << endl;
    gridFlea g3 = g1 + g2;
    g3.move(1);

    cout << "g4 = g2 + g1" << endl;
    gridFlea g4 = g2 + g1;
    g4.move(1);

    cout << "g4 += g3" << endl;
    g4 += g3;
    g4.move(1);
    cout << endl;
    g4.move(1);
    cout << endl;

    cout << "TEsting minus" << endl;
    gridFlea g5 = g4-g2;
    cout << "g5 value: " << g5.value() << endl;
    g5.move(1);
    cout << "g5 value: " << g5.value() << endl;
    cout << endl;
    g5.move(1);
    cout << "g5 value: " << g5.value() << endl;

    cout << endl;
    g5.move(-1);
    cout << "g5 value: " << g5.value() << endl;

    cout << endl;
    g5.move(-1);
    cout << "g5 value: " << g5.value() << endl;

    if(g4==g5)
        cout<<"same" <<endl;
    else
        cout<<"not same" << endl;

    gridFlea g6 = g4;
    cout << "g6 value: " << g6.value() << endl;
    cout << "g4 value: " << g4.value() << endl;
    if(g4==g6)
        cout<<"same" <<endl;
    else
        cout<<"not same" << endl;

    cout << "g6 value: " << g6.value() << endl;

    if(g6==g4)
        cout<<"same" <<endl;
    else
        cout<<"not same" << endl;

    g6.move(1);
    if (g6 < g4)
        cout << "g4 is larger" << endl;
    else if (g6 > g4)
        cout << "g6 is larger" << endl;

    g4.move(2);
    if (g6 < g4)
        cout << "g4 is larger" << endl;
    else if (g6 > g4)
        cout << "g6 is larger" << endl;

    if (g6 <= g4)
        cout << "g4 is larger or g6 and g4 is same" << endl;
    else if (g6 >= g4)
        cout << "g6 is larger or g6 and 64 is same" << endl;

}

void smartptrTest()
{
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,20,2);

    inFest1->move(1);
    cout << endl;
    cout << inFest1->value(VALUE_MAXIMUM) << endl;
}

void copyTesting()
{

    inFest Obj2 = inFest(0, 0, 20, 3);
    inFest Obj3 = inFest(5, 5, 20, 3);
    Obj2 = Obj3;


    cout << "initial values" << endl;
    cout << endl;

    cout << "obj2 min " << Obj2.value(VALUE_MINIMUM) << endl;
    cout << "obj2 max " << Obj2.value(VALUE_MAXIMUM) << endl;
    cout << "obj3 min " << Obj3.value(VALUE_MINIMUM) << endl;
    cout << "obj3 max " << Obj3.value(VALUE_MAXIMUM) << endl;
    cout << endl;

    cout << "Obj3 moved" << endl;
    Obj3.move(1);
    cout << endl;
    cout << "obj2 min " << Obj2.value(VALUE_MINIMUM) << endl;
    cout << "obj2 max " << Obj2.value(VALUE_MAXIMUM) << endl;
    cout << "obj3 min " << Obj3.value(VALUE_MINIMUM) << endl;
    cout << "obj3 max " << Obj3.value(VALUE_MAXIMUM) << endl;
    cout << endl;

    cout << "Obj2 = Obj3 happened here" << endl;
    Obj2 = Obj3;

    cout << "obj2 min " << Obj2.value(VALUE_MINIMUM) << endl;
    cout << "obj2 max " << Obj2.value(VALUE_MAXIMUM) << endl;
    cout << "obj3 min " << Obj3.value(VALUE_MINIMUM) << endl;
    cout << "obj3 max " << Obj3.value(VALUE_MAXIMUM) << endl;
    cout << endl;

    cout << endl;
    cout << "Obj3 moved" << endl;
    Obj3.move(23);
    cout << endl;
    cout << "obj2 min " << Obj2.value(VALUE_MINIMUM) << endl;
    cout << "obj2 max " << Obj2.value(VALUE_MAXIMUM) << endl;
    cout << "obj3 min " << Obj3.value(VALUE_MINIMUM) << endl;
    cout << "obj3 max " << Obj3.value(VALUE_MAXIMUM) << endl;

}

void testInfestComparision()
{
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,20,2);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(1,1,50,3);
    inFest1->move(1);
    cout << endl;
    cout << inFest1->value(VALUE_MAXIMUM) << endl;
    cout << inFest1->value(VALUE_MINIMUM) << endl;
    inFest2->move(1);
    cout << inFest2->value(VALUE_MAXIMUM) << endl;
    cout << inFest2->value(VALUE_MINIMUM) << endl;

    if (*inFest1==*inFest2)
        cout << "They are the same" << endl;
    else
        cout << "They are not the same" << endl;

    // inFest2->move(1);
    //cout << inFest2->value(VALUE_MAXIMUM) << endl;

    if (*inFest1==*inFest2)
        cout << "They are the same" << endl;
    else
        cout << "They are not the same" << endl;
}

void testinFestaddition()
{
    unique_ptr<inFest> inFest1 = make_unique<inFest>(0,0,20,2);
    unique_ptr<inFest> inFest2 = make_unique<inFest>(1,1,50,3);

    unique_ptr<inFest> inFest3 = make_unique<inFest>(*inFest1 + *inFest2);

}

// TODO: Test with RNG, DOCUMENTATION, inFest mix type operator
int main(void)
{


    //srand((unsigned int)time(NULL));
    testAssignmentOperator();
    cout << " ************************************************* " << endl;
    testLessThanOperator();
    cout << " ************************************************* " << endl;
    testGreaterThanOperator();
    cout << " ************************************************* " << endl;
    testGreaterThanOrEqualToOperator();
    cout << " ************************************************* " << endl;
    testLessThanOrEqualToOperator();
    cout << " ************************************************* " << endl;
    testEqualEqualOperator();
    cout << " ************************************************* " << endl;
    testNotEqualOperator();
    cout << " ************************************************* " << endl;
    //tmpTesting();
    //testing();
    //copyTesting();
    //smartptrTest();
    //testinFestaddition();
    // testInfestComparision();




    return 0;
}