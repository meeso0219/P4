/*
* Author: Changhyun Park
* Date: 5/20/2022
* Revision History: Added PRE/POST CONDITIONS and Invariants (4/4)
*                   Added more about invariants (4/5)
*                   Added Unit Testing (4/5)
*                   Changed public void functions to public bool to determine if it worked or not (4/5)
*                   Created driver (4/5)
*
* Revision History2 (P2):
*                   Separated constructor into two constructor (4/11)
*                   Changed bool to void for revive() and reset() (4/11)
*                   Changed reset to have guard check if flea is permanently deactivated (4/11)
*                   Added const gridFlea& gridFlea::operator=(const gridFlea& src) for deep copying (4/11)
*                   Added #define MAX, MIN, ABS (4/11)
*                   modified the directional logic of the flea. Removed rng (4/12)
*                   Edited class invariant, interface invariant, and implementation invariant (4/13)
*
 * Revision History3 (P4):
 *                  - Created move semantics
 *                  - Corrected copy assignment and constructor
 *                  - Any gridFlea may jump outside grid boundaries, at most once, and the jump cannot be
 *                    more than z squares away from the boundary.
 *
 *
 CLASS INVARIANT:
    - The constructor places the flea as specified by the parameters. If the coordinate
    is out of the grid, the flea is placed at (0, 0). The grid coordinates are described
    as from 0 to grid size. The flea is set to active initially.
    - The constructor sets flea's initial energy as specified by the parameter.
    - If the energy is lower than ENERGETIC_BASE_POINT, energy is set to DEFAULT_ENERGY.
    - If client do not specify any x,y position and energy, initial position is (0,0) and initial energy is DEFAULT_ENERGY
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

// PRECONDITION:    Flea must be in active mode to move
//                  Flea must not be in invalid position to move
void gridFlea::move(int p)
{
    if (checkFleaState((FLEA_STATUS)(STATE_PERMDEACTIVE | STATE_INACTIVE)))
    {
        if (!outSideJump)
            outSideJump = true;
        else
            return;
    }

    if (!checkFleaState(STATE_ENERGERTIC))
        p = DEFAULT_MOVE;

    if (p > currentEnergy)
        p = currentEnergy;

    z = SIZE/2;

    if (outSideJump)
    {
        if (p + currentX > SIZE + z || p + currentY > SIZE + z)
            return;
    }
    if (currentEnergy % 2 == 0)
        moveX(p);
    else
        moveY(p);

    currentEnergy -= p;
    movedCount += p;
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

/*
gridFlea & gridFlea::operator=(const gridFlea& src)
{

    //cout << "deep copy" << endl;
    initialX = src.initialX;
    initialY = src.initialY;
    initialEnergy = src.initialEnergy;

    currentX = src.currentX;
    currentY = src.currentY;
    currentEnergy = src.currentEnergy;

    movedCount = src.movedCount;

    return *this;
}
*/

// POSTCONDITION: return value of the flea
int gridFlea::value()
{
    return reward() * SIZE * change();
}



// POSTCONDITION: return a  gridFlea which has the added value of current x, current y, and
//                movedCount from  other two gridFlea.
gridFlea gridFlea::operator+(const gridFlea& g1)
{
    gridFlea local;
    local.currentX =  this->currentX + g1.currentX;
    local.currentY = this->currentY + g1.currentY;
    local.movedCount =  this->movedCount + g1.movedCount;

    return local;
}

// POSTCONDITION: The value of current x, current y, and movedCount of right side gridFlea
//                will be added to the left side gridFlea.
gridFlea&  gridFlea::operator+=(const gridFlea &rhs)
{
    currentX += rhs.currentX;
    currentY += rhs.currentY;
    movedCount += rhs.movedCount;

    return *this;
}

// PRECONDITION: The right side gridFlea may not have larger value of movedCount than left side gridFlea.
// POSTCONDITION: return a  gridFlea which has the subtracted value of current x, current y, and
//                movedCount from  other two gridFlea.
gridFlea gridFlea::operator-(const gridFlea& rhs) const
{
    gridFlea local;
    local.currentX =  this->currentX - rhs.currentX;
    local.currentY =  this->currentY- rhs.currentY;
    local.movedCount = this->movedCount - rhs.movedCount;

    return local;
}

// PRECONDITION: The right side gridFlea may not have larger value of movedCount than left side gridFlea.
// POSTCONDITION: The value of current x, current y, and movedCount of right side gridFlea
//                will be subtracted to the left side gridFlea.
gridFlea&  gridFlea::operator-=(const gridFlea &rhs)
{
    currentX -= rhs.currentX;
    currentY -= rhs.currentY;
    movedCount -= rhs.movedCount;

    return *this;
}

// POSTCONDITION: return a  gridFlea which has the added value of current x, current y, and
//                movedCount by value of rhs.
gridFlea gridFlea::operator+(const int &rhs) const
{
    gridFlea local;
    local.currentX += rhs;
    local.currentY += rhs;
    local.movedCount += rhs;

    return local;
}

// POSTCONDITION: The returned gridFlea's currentX, currentY, and movedCount will be increment by 1.
gridFlea& gridFlea::operator++()
{
    currentX += 1;
    currentY += 1;
    movedCount += 1;

    return *this;
}

// TODO: not working
// POSTCONDITION: returned value is not changed. (post fix)
gridFlea gridFlea::operator++(int x)
{
    gridFlea oldState = *this;
    currentX += 1;
    currentY += 1;
    movedCount += 1;

    return oldState;
}

// PRECONDITION: The gridFlea's movedCount may not zero.
// POSTCONDITION: The returned gridFlea's currentX, currentY, and movedCount will be decremented by 1.
gridFlea& gridFlea::operator--()
{
    currentX -= 1;
    currentY -= 1;
    movedCount -= 1;

    return *this;
}

// TODO: not working
// POSTCONDITION: returned value is not changed. (post fix)
gridFlea gridFlea::operator--(int)
{
    gridFlea oldState = *this;
    currentX -= 1;
    currentY -= 1;
    movedCount -= 1;

    return oldState;
}

gridFlea& gridFlea::operator+=(const int &rhs)
{
    currentX += rhs;
    currentY += rhs;
    movedCount += rhs;

    return *this;
}

gridFlea gridFlea::operator-(const int &rhs) const
{
    gridFlea local;
    local.currentX -= rhs;
    local.currentY -= rhs;
    local.movedCount -= rhs;

    return local;
}

gridFlea& gridFlea::operator-=(const int &rhs)
{
    currentX -= rhs;
    currentY -= rhs;
    movedCount -= rhs;

    return *this;
}

bool gridFlea::operator==(gridFlea &rhs)
{
    if (this->value() == rhs.value())
        return true;
    else
        return false;
}

bool gridFlea::operator!=(gridFlea &rhs)
{
    if (this->value() != rhs.value())
        return true;
    else
        return false;
}

bool gridFlea::operator<(gridFlea &rhs)
{
    if (this->value() < rhs.value())
        return true;
    else
        return false;
}

bool gridFlea::operator>(gridFlea &rhs)
{
    if (this->value() > rhs.value())
        return true;
    else
        return false;
}

bool gridFlea::operator<=(gridFlea &rhs)
{
    if (this->value() <= rhs.value())
        return true;
    else
        return false;
}

bool gridFlea::operator>=(gridFlea &rhs)
{
    if (this->value() >= rhs.value())
        return true;
    else
        return false;
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


// POSTCONDITION: current x axis changes
void gridFlea::moveX(int p)
{
    currentX += p;
}

// POSTCONDITION: current y axis changes
void gridFlea::moveY(int p)
{
    currentY += p;
}

//??????reward?????? is reduced by the number of squares moved.
int gridFlea::reward()
{
    return MAX(DEFAULT_REWARD - movedCount, 1);
}

// POSTCONDITION: return calculated change value
int gridFlea::change()
{
    return ABS((initialX - currentX)) + ABS((initialY - currentY));
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