/*
* Author: Changhyun Park
* Date: 5/19/2022
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
#include "inFest.h"

inFest::inFest()
{
    gridFleasSize = 0;
}

// PRECONDITION: client must specify four parameters.
// POSTCONDITION: infest object get some number of distinct gridFlea objects
inFest::inFest(int initX, int initY, int initEnergy, int size)
{
    cout << " infest constructor" << endl;
    gridFleasSize = size - 1;

    if (gridFleasSize <= 0) // if size is smaller than 0 or equal to 0, set to 1
        gridFleasSize = 1;

    gridFleas = new gridFlea * [gridFleasSize];

    for (int i = 0; i < gridFleasSize; i++) {
        gridFleas[i] = new gridFlea(initX + i, initY + i, initEnergy + i);
    }
}

// copy constructor
inFest::inFest(const inFest& src)
{
    cout << "copy constructor" << endl;
    this->gridFleasSize = src.gridFleasSize;
    this->gridFleas = new gridFlea * [gridFleasSize];

    for (int i = 0; i < gridFleasSize; i++)
    {
        this->gridFleas[i] = src.gridFleas[i];
    }
}

// copy assignment
const inFest& inFest::operator=(const inFest& src)
{
    cout << "copy assignment" << endl;
    // check self assignment
    if (&src == this)
        return *this;

    cout << "inFest copy assignment delete part" << endl;
    // delete part
    if (this->gridFleasSize != 0) {
        for (int i = 0; i < gridFleasSize; i++)
            delete[] * (gridFleas + i);
        delete[] gridFleas;
    }

    cout << "inFest copy assignment copy part" << endl;
    //copy part
    this->gridFleasSize = src.gridFleasSize;
    this->gridFleas = new gridFlea * [gridFleasSize];

    for (int i = 0; i < gridFleasSize; i++) {
        this->gridFleas[i] = new gridFlea(src.gridFleas[i]);
    }

    return *this;
}


//move constructor
inFest::inFest(inFest &&src)
{
    cout << "move constructor" << endl;
    gridFleasSize = src.gridFleasSize;
    gridFleas = src.gridFleas;

    src.gridFleasSize = 0;
    src.gridFleas = nullptr;
    cout << "move constructor ended" << endl;
}


// move assignment
inFest &inFest::operator=(inFest &&src)
{
    cout << "move assignment" << endl;
    // self assignment detection
    if (this == &src)
        return *this;

    swap(gridFleasSize,src.gridFleasSize);
    swap(gridFleas,src.gridFleas);
    cout << "move assignment swapped" << endl;
    return *this;
}

// destructor
inFest::~inFest()
{
    cout << "inFest destructor called" << endl;
    for (int i = 0; i < gridFleasSize; i++)
        delete[] * (gridFleas + i);
    delete[] gridFleas;
}

// PRECONDITION: gridFlea must not died more than half
// POSTCONDITION: return true if more than half died
bool inFest::isMoreThanHalfDied()
{
    int AliveFleaCount = 0;
    for (int i = 0; i < gridFleasSize; i++)
    {
        if (gridFleas[i]->isAlive())
            AliveFleaCount++;
    }

    return (AliveFleaCount < (gridFleasSize / 2));
}

// POSTCONDITION: subobject gridFleas move p squares
//                if more than half fleas are dead, revive them
void inFest::move(int p)
{
    for (int i = 0; i < gridFleasSize; i++)
    {
        gridFleas[i]->move(p);
    }

    if (isMoreThanHalfDied())
        reviveAll();
}

// PRE CONDITION: flea must not died
// POST CONDITION: inacitivated fleas are activated with their initial energy.
void inFest::reviveAll()
{
    for (int i = 0; i < gridFleasSize; i++)
        gridFleas[i]->revive();
}

// POSTCONDITION: return Maximum value of gridFlea or minimum value of gridFlea.
int inFest::value(VALUE_TYPE type)
{
    int max = INT_MIN;
    int min = INT_MAX;

    for (int i = 0; i < gridFleasSize; i++) {

        int currentValue = gridFleas[i]->value();

        max = MAX(currentValue, max);
        min = MIN(currentValue, min);
    }

    switch (type)
    {
        case VALUE_MAXIMUM: return max;
        case VALUE_MINIMUM: return min;
        default:    return 0;
    }
}


inFest inFest::operator+(const inFest &rhs)
{
    int index;
    int num = this->gridFleasSize + rhs.gridFleasSize;

    inFest newObj = inFest(0,0,0,num);


    for (int i = 0; i < this->gridFleasSize; i++)
    {
        newObj.gridFleas[i] = this->gridFleas[i];
        index++;
    }

    for (int k = index; k < num; k++)
        newObj.gridFleas[k] = rhs.gridFleas[k];


    return newObj;
}

inFest& inFest::operator+=(const inFest &rhs)
{


    return *this;
}
/*
inFest inFest::operator+(const gridFlea &rhs)
{
    inFest newObj = inFest(0,0,0,this->gridFleasSize+1);

    for (int i = 0; i < this->gridFleasSize; i++)
        newObj.gridFleas[i] = this->gridFleas[i];

    newObj.gridFleas[gridFleasSize] = (gridFlea *) rhs;



    return newObj;
}
*/


// compare values
bool inFest:: operator==(inFest &rhs)
{
    return value(VALUE_MAXIMUM) == rhs.value((VALUE_MAXIMUM));
}

bool inFest:: operator!=(inFest &rhs)
{
    return value(VALUE_MAXIMUM) != rhs.value(VALUE_MAXIMUM);
}

bool inFest:: operator<(inFest &rhs)
{
    return value(VALUE_MAXIMUM) < rhs.value(VALUE_MAXIMUM);
}

bool inFest:: operator>(inFest &rhs)
{
    return value(VALUE_MAXIMUM) > rhs.value(VALUE_MAXIMUM);
}

bool inFest:: operator<=(inFest &rhs)
{
    return value(VALUE_MAXIMUM) <= rhs.value(VALUE_MAXIMUM);
}

bool inFest:: operator>=(inFest &rhs)
{
    return value(VALUE_MAXIMUM) >= rhs.value(VALUE_MAXIMUM);
}



/* Implementation Invariant:
*  - INT_MIN and INT_MAX are defined to compare minimum value and maximum value
*  - enum VALUE_TYPE is for custom data type for value method.
*  - isMoreThanHalfDied is a helper method to determine whether revive all or not.
*  - value method to return Maximum value of subobject gridflea or minimum value of subobject gridflea depend on parameter"type"
*/