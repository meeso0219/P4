/*
* Author: Changhyun Park
* Date: 5/20/2022
*
* CLASS INVARIANT:
*                 - The constructor encapsulates some number of internally generated, distinct gridFlea objects.
*                   It systematically generates different values for subobject gridFlea.
*                 - inFest object revive all inactivated gridFleas when more than half of its gridFleas are deactivated.
*                 - Each inFest object manages its gridFleas. For example, if inFest object moves p, all its subobject gridFleas
                    move p as well.
                  - if client specify size to less than or equal to 1, the number of subobject will be 1.
                  - Client may compare inFest object with inFest object.
                  - Client may add inFest to inFest.
                  - Client may add gridFlea to inFest.
*/
#include <cstring>
#include "inFest.h"

inFest::inFest()
{
    gridFleasSize = 0;
}

// PRECONDITION: client must specify four parameters.
// POSTCONDITION: infest object get some number of distinct gridFlea objects
inFest::inFest(int initX, int initY, int initEnergy, int size)
{
    //cout << " infest constructor" << endl;
    //gridFleasSize = size - 1;

    gridFleasSize = size;
    if (gridFleasSize <= 0) // if size is smaller than 0 or equal to 0, set to 1
        gridFleasSize = 1;

    gridFleas = new gridFlea * [gridFleasSize];

    for (int i = 0; i < gridFleasSize; i++)
        gridFleas[i] = new gridFlea(initX + i, initY + i, initEnergy + i);

}

void inFest::copySem(const inFest& src)
{
    this->gridFleasSize		= src.gridFleasSize;
    this->gridFleas			= new gridFlea * [gridFleasSize];

    for (int i = 0; i < src.gridFleasSize; i++) {
        this->gridFleas[i] = new gridFlea(src.gridFleas[i]);
    }
}

// copy constructor
inFest::inFest(const inFest& src)
{
    cout << "copy constructor" << endl;
    copySem(src);
}

// copy assignment
inFest& inFest::operator=(const inFest& src)
{
    cout << "copy assignment" << endl;
    // check self assignment
    if (&src == this)
        return *this;

    // delete part
    if (this->gridFleasSize != 0) {
        for (int i = 0; i < gridFleasSize; i++)
            delete[] * (gridFleas + i);
        delete[] gridFleas;
    }

    cout << "inFest copy assignment copy part" << endl;
    copySem(src);

    return *this;
}


//move constructor
inFest::inFest(inFest &&src)
{
    gridFleasSize = src.gridFleasSize;
    gridFleas = src.gridFleas;

    src.gridFleasSize = 0;
    src.gridFleas = nullptr;
}


// move assignment
inFest &inFest::operator=(inFest &&src) noexcept
{
    // self assignment detection
    if (this == &src)
        return *this;

    swap(gridFleasSize,src.gridFleasSize);
    swap(gridFleas,src.gridFleas);

    return *this;
}

// destructor
inFest::~inFest()
{
    for (int i = 0; i < gridFleasSize; i++)
        delete[] * (gridFleas + i);
    delete[] gridFleas;
}

// PRECONDITION: gridFlea must not died more than half
// POSTCONDITION: return true if more than half died
bool inFest::isMoreThanHalfDied()
{
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
        gridFleas[i]->move(p);
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

int inFest::getNumOfAliveFlea()
{
    return AliveFleaCount;
}
int inFest::getNumOfFlea()
{
    return gridFleasSize;
}

inFest inFest::operator+(const inFest &rhs)
{
    inFest newObj			= inFest();
    newObj.gridFleasSize	= this->gridFleasSize + rhs.gridFleasSize;
    newObj.gridFleas		= new gridFlea *[newObj.gridFleasSize];

    int index				= 0;

    for (int i = 0; i < this->gridFleasSize; i++)
        newObj.gridFleas[index++] = new gridFlea(this->gridFleas[i]);

    for (int i = 0; i < rhs.gridFleasSize; i++)
        newObj.gridFleas[index++] = new gridFlea(rhs.gridFleas[i]);

    return newObj;
}

inFest& inFest::operator+=(const inFest &rhs)
{
    int newGridFleasSize = this->gridFleasSize + rhs.gridFleasSize;


    gridFlea** tempGridFleas = new gridFlea * [newGridFleasSize];
    //tempGridFleas = new gridFlea * [gridFleasSize+rhs.gridFleasSize];

    memcpy(tempGridFleas, this->gridFleas ,sizeof(gridFlea) * newGridFleasSize);
    memcpy((tempGridFleas + (this->gridFleasSize * sizeof(gridFlea))),
           rhs.gridFleas ,
           sizeof(gridFlea) * gridFleasSize);

    copy(gridFleas,gridFleas + min(gridFleasSize,newGridFleasSize), tempGridFleas);

    // delete part
    if (this->gridFleasSize != 0) {
        for (int i = 0; i < gridFleasSize; i++)
            delete[] * (gridFleas + i);
        delete[] gridFleas;
    }
    this->gridFleas = tempGridFleas;
    this->gridFleasSize = newGridFleasSize;

    //copy(gridFleas,gridFleas + min(gridFleasSize,rhs.gridFleasSize), tempGridFleas);
    //tempGridFleas[gridFleasSize+1] = (gridFlea *) rhs;

    //this = tempGridFleas;
    return *this;
}

// 여기서는 잘댐
inFest inFest::operator+(gridFlea *rhs)
{
    gridFlea** tempGridFleas;
    tempGridFleas = new gridFlea * [gridFleasSize+1];

    copy(gridFleas,gridFleas + min(gridFleasSize,gridFleasSize+1), tempGridFleas);
    tempGridFleas[gridFleasSize+1] = (gridFlea *) rhs;

    return reinterpret_cast<inFest &&>(tempGridFleas);
}


// POSTCONDITION return true if left-side inFest's maximum value is equal to right-side inFest's maximum value
bool inFest:: operator==(inFest &rhs)
{
    return value(VALUE_MAXIMUM) == rhs.value((VALUE_MAXIMUM));
}

// POSTCONDITION: return true if left-side inFest's maximum value is not equal to right-side inFest's maximum value
bool inFest:: operator!=(inFest &rhs)
{
    return value(VALUE_MAXIMUM) != rhs.value(VALUE_MAXIMUM);
}

// POSTCONDITION: return true if left-side inFest's maximum value is smaller than right-side inFest's maximum value
bool inFest:: operator<(inFest &rhs){
    return value(VALUE_MAXIMUM) < rhs.value(VALUE_MAXIMUM);
}

// POSTCONDITION: return true if left-side inFest's maximum value is greater than right-side inFest's maximum value
bool inFest:: operator>(inFest &rhs)
{
    return value(VALUE_MAXIMUM) > rhs.value(VALUE_MAXIMUM);
}

// POSTCONDITION: return true if left-side inFest's maximum is smaller than or equal to right-side inFest's maximum
bool inFest:: operator<=(inFest &rhs)
{
    return value(VALUE_MAXIMUM) <= rhs.value(VALUE_MAXIMUM);
}

// POSTCONDITION: return true if left-side inFest's maximum is greater than or equal to right-side inFest's maximum
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