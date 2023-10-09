#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include "alphabet.h"


class Square {

private:
    int m_x;
    int m_y;

public:

    /**
     * @brief Square Default Constructor.
     */
    Square(int,int);

    /**
     * @brief gets the x coordinate.
     * @return  the x coordinate value.
     */
    int getX() const;

    /**
     * @brief gets the y coordinate.
     * @return  the y coordinate value.
     */
    int getY() const;

    /**
     * @brief operator << this method overloads the insertion operator.
     * @param out the output stream.
     * @return a reference to the output stream.
     */
    friend std::ostream & operator<<(std::ostream & out, const Square&);

};

inline int Square::getX() const
{
    return m_x;
}

inline int Square::getY() const
{
    return m_y;
}
#endif //SQUARE_H
