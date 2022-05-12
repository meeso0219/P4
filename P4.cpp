/*
* Author: Changhyun Park
* Date: 4/14/2022
*
* CLASS INVARIANT:
*                 - The constructor encapsulates some number of internally generated, distinct gridFlea objects.
*                   It systematically generate different values for subobject gridFlea.
*
*                 - inFest object revive all inactivated gridFleas when more than half of its gridFleas are deactivated.
*
*                 - Each inFest object manages its gridFleas. For example, if inFest object moves p, all its subobject gridFleas
                    move p as well.
                  - if cilent specify size to less than or equal to 1, the number of subobject will be 1.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "inFest.h"


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

void tmpTesting()
{
    cout << "This is TMP testing" << endl;
    inFest inFestTmp[5];

    for (int i = 0; i < 5; i++)
    {
        inFestTmp[i] = inFest(i+1,i+5,i+30,5);
    }
    inFestTmp[0].move(10); // 0 번째는 initX1 initY 5 initEnergy 30 size 5

}

void copyTesting()
{

    inFest Obj2 = inFest(0, 0, 20, 3);
    inFest Obj3 = inFest(5, 5, 20, 3);

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

int main(void)
{

    srand((unsigned int)time(NULL));

    tmpTesting();
    //testing();
    //copyTesting();

    return 0;
}






