#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
#include"direction.h"


class Position {

private:
      int m_x;
      int m_y;
      int m_z;
public:

 /**
 * @brief Position Constructor.Creates a 3D coordinates.It checks if xin,yin,zin are valid.
 * @param xin the x axis coordinates.
 * @param yin the y axis coordinates.
 * @param zin the z axis coordinates.
 */
Position(int xin,int yin,int zin);

/**
 * @brief Position a copy constructor to replace the default.
 * @param otherPosition the position to copy.
 */
Position(const Position& other);

/*!
 * \brief operator << overloaded insertion operator.
 * \param out the output stream.
 * \param positionin the position to inject in the stream.
 * \return the output stream.
 */
friend std::ostream& operator<< (std::ostream& out,const Position& positionin);

Position& operator=(const Position& right_handside);


/*!
* \brief axialCoordinates transforms position coordinates into axial coordinates.
* \param coordinates the position coordinates to transform.
* \return the pair of coordinates.
*/
std::pair<int,int> axialCoordinates();

Position getPositionTo(esi::Direction direction);

/*!
 * \brief gets the x axis of the position.
 * \return the x axis of the position.
 */
inline int x() const;
/*!
 * \brief y gets the y axis of the position.
 * \return the y axis of the position.
 */
inline int y() const;
/*!
 * \brief z gets the z axis of the position.
 * \return the z axis of the position.
 */
inline int z() const;


friend bool operator!= (const Position &c1, const Position &c2);
friend bool operator==(const Position & position,const Position & position2);
};
inline int Position::x() const {
    return m_x;
}

inline int Position::y() const {
    return m_y;
}

inline int Position::z() const {
    return m_z;
}


#endif // POSITION_H
