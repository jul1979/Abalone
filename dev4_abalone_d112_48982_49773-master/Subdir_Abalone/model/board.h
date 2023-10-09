#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include"hexagon.h"
#include "direction.h"
#include "square.h"
#include <optional>
#include<memory>

class Board
{

private:

std::shared_ptr<vector<Hexagon>*> m_hexagons;
/**
 * @brief createHexagons creates all 61 Hexagons of the Board.
 * It is called in the constructor.
 */
void createHexagons();



public:
/**
 * @brief Board Default constructor.Creates a Board of Hexagon.
 */
Board();
/**
 * @brief countMarblesLeft counts the number of marbles on the Board
 * given a particular player color.
 * @return the number of marbles on the Board for that color.
 */
 unsigned countMarblesLeft(Color);

/**
 * @brief neighbour gets the neighbouring Hexagon in the provided Direction.
 * @param direction the orientation to get the neighbour from.
 * @return the neighbouring Hexagon.
 */
std::optional<Hexagon> neighbour(Hexagon& ,esi::Direction direction);

/**
 * @brief isFree checks if the Hexagon has no marble on it.
 * @return true if it does not have a marble on it false otherwise.
 */
 bool isFree(const Hexagon& );

 /**
 * @brief ~Board the Destructor.
 * prevents memory leaks by releasing ressources.
 */
virtual ~Board();
/**
 * @brief moveMarble displaces a marble from one Hexagon to another.
 * @param origin the  hexagon where to moving marble originated from.
 * @param destination the hexagon where to moving marble goes to.
 */

 /**
  * @brief isInside checks if a position is inside the board.
  * @return true if it is false otherwise.
  */
 bool isInside(const Position);

/*!
 * \brief isBorder checks if the hexagon at that position has no neighbour
 *  in the passed direction.
 * \param direction the direction to check  a neighbour in.
 * \return true if there is a neighbour in that direction false otherwise.
 */
 bool isBorder(const Position,esi::Direction direction);//prive


 /**
 * @brief getHexagonAt gets a pointer to the hexagon located at position.
 * @param position the position of the Hexagon.
 * @return a pointer pointing to that Hexagon.
 */
Hexagon*  getHexagonAt(Position position);

/**
 * @brief backTo3Dcoordinates calculates the 3D cordinates from 2D coordinates.
 * @param square the 2D coordinates of an Hexagon.
 * @return the 3D coordinates represented by an instance of Position class.
 */
Position backTo3Dcoordinates(Square square);

/**
 * @brief translateInto2D calculates 2D coordinates from ABA-PRO system.
 * @param lettre the first coordinate in ABA-PRO.
 * @param val the second coordinate in ABA-PRO.
 * @return the 2D coordinates value representated by an instance of Square.
 */
Square translateInto2D(Alphabet lettre, int val);
/**
 * @brief hexagons , gets m_hexagons member.
 * @return a pointer to the vector of hexagons.
 */
inline std::shared_ptr<vector<Hexagon>*> hexagons()const;
};

inline std::shared_ptr<vector<Hexagon>*>  Board::hexagons() const {
    return m_hexagons;
}

#endif // BOARD_H
