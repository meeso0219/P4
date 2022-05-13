/*
* Author: Changhyun Park
* Date: 5/19/2022
* Revision History: Added PRE/POST CONDITIONS and Invariants (4/4)
*                   Added more about invariants (4/5)
*                   Added Unit Testing (4/5)
*                   Changed public void functions to public bool to determine if it worked or not (4/5)
*                   Created driver (4/5)
*
* Revision History2:
*                   Separated constructor into two constructor (4/11)
*                   Changed bool to void for revive() and reset() (4/11)
*                   Changed reset to have guard check if flea is permanently deactivated (4/11)
*                   Added const gridFlea& gridFlea::operator=(const gridFlea& src) for deep copying (4/11)
*                   Added #define MAX, MIN, ABS (4/11)
*                   modified the directional logic of the flea. Removed rng (4/12)
*                   Edited class invariant, interface invariant, and implementation invariant (4/13)
*
 CLASS INVARIANT:
 - The constructor places the flea as specified by the parameters. If the coordinate
    is out of the grid, the flea is placed at (0, 0). The grid coordinates are described
    as from 0 to grid size. The flea is set to active initially.
    The constructor sets flea's initial enery as specified by the parameter.
    If the energy is lower than ENERGETIC_BASE_POINT, energy is set to DEFAULT_ENERGY.
    If client do not specify any x,y position and energy, initial position is (0,0) and initial energy is DEFAULT_ENERGY
*/

#include "gridFlea.h"

// PRECONDITION: the initial coordinates must be inside of the range
// POSTCONDITION: set the flea's initial position and initial energy by parameters
gridFlea::gridFlea(int initX, int initY, int initEnergy)
{

    if (initX < 0 || initX > SIZE)
        initX = 0;

    if (initY < 0 || initY > SIZE)
        initY = 0;

    if (initEnergy < ENERGETIC_BASE_POINT)
        initEnergy = DEFAULT_ENERGY;

    initialX = initX;
    initialY = initY;
    initialEnergy = initEnergy;

    resetPosition();
    resetEnergy();
}

// POSTCONDITION: if client does not specify the initial values, x is 0 y is 0 and energy is 10
gridFlea::gridFlea()
{
    initialX = 0;
    initialY = 0;
    initialEnergy = DEFAULT_ENERGY;

    resetPosition();
    resetEnergy();
}

gridFlea::gridFlea(const gridFlea* src)
{
    initialX = src->initialX;
    initialY = src->initialY;
    initialEnergy = src->initialEnergy;

    currentX = src->currentX;
    currentY = src->currentY;
    currentEnergy = src->currentEnergy;

    movedCount = src->movedCount;
}


// POST CONDITION: flea's move count and position is set to initial which is (0,0)
void gridFlea::resetPosition()
{
    movedCount = 0;
    currentX = initialX;
    currentY = initialY;
}

// POST CONDITION: flea's energy is set to its initial energy
void gridFlea::resetEnergy()
{
    currentEnergy = initialEnergy;
}

// POSTCONDTION: return false if flea's position is out of the bound
//               return true if flea is inside of the range
bool gridFlea::IsVaildPosition()
{
    if (currentX < LOWERXBOUND || currentX > UPPERXBOUND ||
        currentY < LOWERYBOUND || currentY > UPPERYBOUND)
        return false;

    return true;
}

bool gridFlea::checkFleaState(FLEA_STATUS state)
{
    return state & getFleaState();
}

// POSTCONDITION: return value that represent flea state
int gridFlea::getFleaState()
{
    int state = STATE_NONE;

    if (!IsVaildPosition())
        state |= STATE_PERMDEACTIVE;

    if (currentEnergy == 0)
        state |= STATE_INACTIVE;

    if (currentEnergy >= ENERGETIC_BASE_POINT)
        state |= STATE_ENERGERTIC;
    else
        state |= STATE_NORMAL;


    return (FLEA_STATUS)state;
}

// PRECONDITION:    Flea must be in active mode to move
//                  Flea must not be in invalid position to move
void gridFlea::move(int p)
{

    if (checkFleaState((FLEA_STATUS)(STATE_PERMDEACTIVE | STATE_INACTIVE)))
    {
        if (!outSideJump)
        {
            outSideJump = true;
        }
        else
        {
            cout << "not moved" << endl;
            return;
        }
    }
    if ( outSideJump == true)
        cout<< "outside Jump is true" << endl;
    else if (outSideJump == false)
        cout << "outide jump is false" << endl;
    if (!checkFleaState(STATE_ENERGERTIC))
        p = DEFAULT_MOVE;

    if (p > currentEnergy)
        p = currentEnergy;

    cout << "Move current p: " << p << endl;

    z = SIZE/2;
    cout << "z: " << z << endl;
    if (outSideJump == true)
    {
        if (p + currentX > SIZE + z || p + currentY > SIZE + z)
        {
            cout << "gridFlea cannot jump more than " << z << "squares from boundary" << endl;
            cout << "current location is " << currentX << currentY << endl;
            return;
        }

    }
    if (currentEnergy % 2 == 0)
        moveX(p);
    else
        moveY(p);

    currentEnergy -= p;
    movedCount += p;
    cout << "current Energy: " << currentEnergy << endl;

}

// POSTCONDITION: current x axis changes
void gridFlea::moveX(int p)
{
    currentX += p;
    cout << "current X: " << currentX << endl;
}

// POSTCONDITION: current y axis changes
void gridFlea::moveY(int p)
{
    currentY += p;
    cout << "current Y: " << currentY << endl;
}

//��reward�� is reduced by the number of squares moved.
int gridFlea::reward()
{
    return MAX(DEFAULT_REWARD - movedCount, 1);
}

// POSTCONDITION: return calculated change value
int gridFlea::change()
{
    return ABS((initialX - currentX)) + ABS((initialY - currentY));
}

// PRECONDITION: Flea must be not permanantely deactivated
// POSTCONDITION:   Flea status become initial state
void gridFlea::reset()
{
    if (!checkFleaState(STATE_PERMDEACTIVE))
        return;

    resetPosition();
    resetEnergy();
}


// PRECONDITION:    Flea must be in inactive mode and not in out of the boundary.
// POSTCONDTION:    The Flea has initial energy with the same location where the flea became deactivated
void gridFlea::revive()
{
    if (!isAlive()) return;
    if (!checkFleaState(STATE_PERMDEACTIVE)) return;
    //cout << "revived a flea" << endl;
    resetEnergy();
}

// POSTCONDITION: return false if flea is permanently deactivated (which is dead)
bool gridFlea::isAlive()
{
    return !checkFleaState(STATE_PERMDEACTIVE);
}


const gridFlea& gridFlea::operator=(const gridFlea& src)
{

    initialX = src.initialX;
    initialY = src.initialY;
    initialEnergy = src.initialEnergy;

    currentX = src.currentX;
    currentY = src.currentY;
    currentEnergy = src.currentEnergy;

    movedCount = src.movedCount;

    return *this;
}


// POSTCONDITION: return value of the flea
int gridFlea::value()
{
    return reward() * SIZE * change();
}

/* Implementation Invariant:
  1. Minimal details describe internal data structures and dependencies
- deactivated tracks the ability for the client to revive or reset the flea
- Reward starts at 100 for all fleas, and it changes as flea moves.
- SIZE is held constant and represents the size of grid.
  The flea is permanently deactivated if it goes out of range (0 to SIZE)
- The flea can only move when it is active. The flea moves specified number of squares by client.
  But if the flea is not energetic, it moves only 1 square.
- The flea will become un-energetic if its current energy is lower than ENERGETIC_BASE_POINT
  and getFleaState() and getFleaState() will help to track flea's state.

- MAX is defined to determine larger value
- MIN is defined to determine lower value
- ABS is defined to get absolute value

- DEFAULT_SIZE is defined to set size of grid
- DEFAULT_ENERGY is defined to default energy.
- DEFAULT_MOVE is defined to movement when flea is not energetic.
- DEFAULT_REWARD is defined to set default reward
- ENERGETIC_BASE_POINT is defined to represent minimum energy to be energetic.

- enum FLEA_STATUS is to track flea state.

  2. Unnecessary details implied by function prototype
- move() changes the position of the flea. The direction is depend on flea's current energy.
- value() returns the value of the flea
- isValidPosition() is a helper method which returns true if the flea is in the grid
- moveX and move Y are helper method to move along x axis or y axis
- revive() will simply make the flea active again.
- reset() will return the flea to it's initial state, moveCount, position, energy and etc
 */