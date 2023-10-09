#ifndef DIRECTION_H
#define DIRECTION_H

#include<iostream>

using std::cout;

/*!
 *\namespace for various classes.
 */
namespace esi {


/**
 * @brief Enumeration representing the Eight possible directions
 * of a marble or a column(two or three marbles).
 */

enum class Direction{

    EAST,
    WEST,
    NORTHWEST,
    NORTHEAST,
    SOUTHWEST,
    SOUTHEAST,
};
/**
 * @brief operator << overloaded insertion operator.
 * @param out the output stream.
 * @param direction the direction to inject  in the output stream.
 * @return the output stream.
 */

/**
 * @brief to_string builds a string reprensatation of a direction.
 * @param color the color to get the string for.
 * @return
 */
inline std::string to_string(Direction color);

std::string to_string(Direction color) {
    std::string result;
    switch (color) {
    case Direction::EAST:
        result = "EAST";
        break;
    case Direction::WEST:
        result = "WEST";
        break;
    case Direction::NORTHEAST:
        result = "NORTHEAST";
        break;
    case Direction::NORTHWEST:
        result = "NORTHWEST";
        break;
    case Direction::SOUTHEAST:
        result = "SOUTHEAST";
        break;
    case Direction::SOUTHWEST:
        result = "SOUTHWEST";
        break;
    }
    return result;
}

}//namespace esi


#endif // DIRECTION_H
