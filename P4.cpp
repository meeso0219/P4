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
        inFestTmp[i] = inFest(i+1,i+5,i+300,1);
    }
    inFestTmp[0].move(10);
    cout << "moved 1" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 2" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 3" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 4" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 5" << endl;
    cout << endl;
    inFestTmp[0].move(30);
    cout << "moved 6" << endl;
    cout << endl;

    inFestTmp[0].move(10);
    cout << "moved 7" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 8" << endl;
    cout << endl;
    inFestTmp[0].move(10);
    cout << "moved 9" << endl;
    cout << endl;
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






