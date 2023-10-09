#ifndef MOVETYPE_H
#define MOVETYPE_H

#include<iostream>
#include<string>

namespace esi {


/**
 * @brief The MoveType enum represents the two types of moves
 *  for a marble.
 */

enum class MoveType{

    /*! a movement in wich marbles are moved as a column into a free space*/
    INLINE,
    /*!a movement in wich marbles are moved sideways into adjacent free spaces
     *This move cannot be used to push an opponent single marble or column.
    */
    SIDESTEP,

};
}

#endif // MOVETYPE_H
