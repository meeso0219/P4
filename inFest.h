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

* Invariant details before/after operations:
*                 move() - when move() is invoked, it triggers inFest object's subobject gridFlea to move same number of squares.
*
*                 value() - use two parameter to get maximum value and minimum value. (e.g value(VALUE_MAXIMUM) or value(VALUE_MINUMUM)
*
*                 reviveAll() - all inactivated subobjectts become active
*
* Type characteristics:
*                   Each inFest object encapsulates some number of internally generated, distinct gridFlea objects.
*
*                   Infest object revive inactivated fleas when more than half of its gridFleas are inactive.
*
* Interface Invariant:
*
*                   POSTCONDITION: inFest has (size -1) subobjects and its first subobject has initial value by the parameter.
*                                   remaining subobjects will have different values internally
*                   inFest(int initX, int initY, int initEnergy, int size)
*
*                   POSTCONDITION: subobject gridFleas move p squars
*                   void move(int p)
*
*                   PRECONDITION:
*                   POSTCONDITION:
*                   int  value(VALUE_TYPE type)
*
*                   PRECONDITION: half of inFest object's subobject must be inactiavted but not permanently deactiavated
*                   POSTCONDITION: inactivated fleas will have their initial energy.
*                   void  reviveAll()
*
*/
#ifndef INFEST_H
#define INFEST_H

#pragma once
#include "gridFlea.h"
#define INT_MIN     (-2147483647 - 1)
#define INT_MAX       2147483647


enum VALUE_TYPE
{
    VALUE_MAXIMUM,
    VALUE_MINIMUM

};

class inFest {
private:
    int         gridFleasSize;
    gridFlea** gridFleas;

    // PRECONDITION: gridFlea must not died more than half
    // POSTCONDITION: return true if more than half died
    bool isMoreThanHalfDied();

public:

    inFest();
    inFest(const inFest& src);
    // PRECONDITION: client must specify four parameters.
    // POSTCONDITION: infest object get some number of distinct gridFlea objects
    inFest(int initX, int initY, int initEnergy, int size);

    const inFest& operator=(const inFest& src);

    ~inFest();


    // POSTCONDITION: subobject gridFleas move p squares
    //                if more than half fleas are dead, revive them
    void move(int p);

    // POSTCONDITION: return Maximum value of gridFlea or minimum value of gridFlea.
    int  value(VALUE_TYPE type);

    // PRE CONDITION: flea must not died
    // POST CONDITION: inacitivated fleas are activated with their initial energy.
    void  reviveAll();

    inFest operator+(const inFest &rhs) const; // appends GridFleas from rhs to *this

    inFest &operator+=(const inFest &rhs);

    inFest operator+(const gridFlea &rhs) const;

    inFest &operator+=(const gridFlea &rhs);

    inFest &operator++(); // prefix

    inFest operator++(int x); // postfix

    gridFlea const &operator[](size_t index) const;

    bool operator==(const inFest &rhs) const; // compares (maxValue - minValue) of both

    bool operator!=(const inFest &rhs) const;

    bool operator<(const inFest &rhs) const;

    bool operator>(const inFest &rhs) const;

    bool operator<=(const inFest &rhs) const;

    bool operator>=(const inFest &rhs) const;
};
#endif
