/*
 Author: Changhyun Park
 Date: 5/19/2022
 Revision History: Added PRE/POST CONDITIONS and Invariants (4/4)
                   Added more about invariants (4/5)
                   Added Unit Testing (4/5)
                   Changed public void functions to public bool to determine if it worked or not (4/5)
                   Created driver (4/5)

 Revision History2:
                  Separated constructor into two constructor (4/11)
                  Changed bool to void for revive() and reset() (4/11)
                   Added const gridFlea& gridFlea::operator=(const gridFlea& src) for deep copying (4/11)
                   Added #define MAX, MIN, ABS (4/11)
                 modified the directional logic of the flea. Removed rng (4/12)

 CLASS INVARIANT:
   - The constructor places the flea as specified by the parameters. If the coordinate
     is out of the grid, the flea is placed at (0, 0). The grid coordinates are described
     as from 0 to grid size. The flea is set to active initially.
   - The constructor sets flea's initial enery as specified by the parameter.
   - If the energy is lower than ENERGETIC_BASE_POINT, energy is set to DEFAULT_ENERGY.
   - If client do not specify any x,y position and energy, initial position is (0,0) and initial energy is DEFAULT_ENERGY

- Invariant details before/after operations:

move() - Flea go to x direction if current energy is even number.
         Flea go to y direction if current energy is odd numbers

value() - State is unchanged.

revive() - Everything except the 'active' state stays the same

reset() - The flea remains in the grid.

isActive() - State is unchanged.

- Type characteristics:

- Flea is always initially active and energetic

- The flea can only move when it is active.

- The flea becomes inactive when its energy is zero.

- The flea can only move 1 square if its current energy is lower then DEFAULT_MOVE

- Value is not very meaningful.

- The flea can move in the positive or negative direction for both the x and y axes.

- A flea that moved out of the grid cannot be revived or reset.

Interface Invariant:


    Postconditions: Flea is in the range of bound, active and energetic
    gridFlea(int initX, int initY)

    Preconditions:  Flea must be active and p != 0
    Postconditions: Flea position changed by p squares or 1 square in either the x or y direction,
                    Flea may be unactive and/or out of the grid
    void move(int p)

    Precondition: Flea must be active
    Postcondition: Flea position changed by p squares along x axis
    void moveX(int p)

    Precondition: Flea must be active
    Postcondition: Flea position changed by p squares along y axis
    void moveY(int p)

    Preconditions: Flea must be active
    int value()

    Preconditions: Flea must be in inactive mode and not in out of the boundary.
    Postconditions: The Flea has initial energy with the same location where the flea became deactivated
    void revive()

    Preconditions: Flea must be not permanantely deactivated and in the range of grid
    Postconditions: Flea returns to its original state (original position, original energy...)
    void reset()

    No condition changes
    bool isActive()

    No condition changes
    IsVaildPosition()

    POSTCONDITION: flea's move count and position is set to initial
    void resetPosition()

    POST CONDITION: flea's energy is set to its initial energy
    void resetEngergy()

    No condition changes
    bool checkFleaState(FLEA_STATUS state)

    No condition changes
    int getFleaState()

    POSTCONDITION: reward is reduced by the number of squares flea moved
                   and return reduced reward.
    int reward()

    POSTCONDITION: return integer that represent how many squares flea moved from its initial position.
    int change()

    No condition changes
    bool isAlive()
*/
#ifndef GRIDFLEA_H
#define GRIDFLEA_H

#pragma once
#define     MAX(a, b) (a>b)?a:b
#define     MIN(a, b) (a<b)?a:b
#define     ABS(x) ((x<0)?(-x):(x))

#define DEFAULT_SIZE          50
#define DEFAULT_ENERGY        10
#define DEFAULT_MOVE          1
#define DEFAULT_REWARD        100
#define ENERGETIC_BASE_POINT  5

#include <iostream>
#include <cstdlib>

using namespace std;

enum FLEA_STATUS
{
    STATE_NONE = 0,
    STATE_PERMDEACTIVE = 1 << 0,
    STATE_INACTIVE = 1 << 1,
    STATE_NORMAL = 1 << 2,
    STATE_ENERGERTIC = 1 << 3

};
class gridFlea
{

private:
    const int   SIZE = DEFAULT_SIZE;
    const int   LOWERXBOUND = 0;
    const int   LOWERYBOUND = 0;
    const int   UPPERXBOUND = SIZE;
    const int   UPPERYBOUND = SIZE;
    int         initialX;
    int         initialY;
    int         initialEnergy;

    int         currentX;
    int         currentY;
    int         currentEnergy;
    int         movedCount;
    unsigned    lastChanceJump;
    bool        outSideJump; // false for not last jumped yet. true for last jumped

    // POST CONDITION: flea's move count and position is set to initial which is (0,0)
    void        resetPosition();

    // POST CONDITION: flea's energy is set to its initial energy
    void        resetEnergy();

    // POSTCONDTION: return false if flea's position is out of the bound
//               return true if flea is inside of the range
    bool        IsVaildPosition();

    bool        checkFleaState(FLEA_STATUS state);

    // POSTCONDITION: return value that represent flea state
    int         getFleaState();

    // POSTCONDITION: current x axis changes
    void        moveX(int p);

    // POSTCONDITION: current y axis changes
    void        moveY(int p);

    //��reward�� is reduced by the number of squares moved.
    int         reward();

    // POSTCONDITION: return calculated change value
    int         change();

public:
    // PRECONDITION: the initial coordinates must be inside of the range
    // POSTCONDITION: set the flea's initial position and initial energy by parameters
    gridFlea(int initX, int initY, int initEnergy);

    // POSTCONDITION: if client does not specify the initial values, x is 0 y is 0 and energy is 10
    gridFlea();

    gridFlea(const gridFlea* src);

    // POSTCONDITION: return value of the flea
    int  value();

    // PRECONDITION:    Flea must be in active mode to move
    //                  Flea must not be in invalid position to move
    void move(int p);

    // PRECONDITION: Flea must be not permanantely deactivated
// POSTCONDITION:   Flea status become initial state
    void reset();

    // PRECONDITION:    Flea must be in inactive mode and not in out of the boundary.
// POSTCONDTION:    The Flea has initial energy with the same location where the flea became deactivated
    void revive();

    // POSTCONDITION: return false if flea is permanently deactivated (which is dead)
    bool isAlive();


    const gridFlea& operator=(const gridFlea& src);
};
#endif
