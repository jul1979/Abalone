#ifndef MARBLE_H
#define MARBLE_H

#include"color.h"

 /**
 * @brief The Marble class
 * represents a marble on the board.
 */

class Marble{

private:

Color m_color;


public:
/**
 * @brief Marble,Constructor creates a marble
 * @param color the color of the marble.
 */
Marble(Color color);

/**
 * @brief color gets the marble color.
 * @return the color of the marble.
 */
inline Color color() const;

/*!
 * \brief operator = overloaded assignement operator.
 * \param marblein the marble being assigned.
 */
Marble& operator = (const Marble &marblein );
/**
 * @brief operator << overloaded insertion operator.
 * @param out the output stream.
 * @param marblein the marble to inject  in the output stream.
 * @return the output stream.
 */
friend std::ostream &operator<<(std::ostream & output,const Marble &marblein );

};

inline Color Marble::color() const {
    return m_color;
}

#endif // MARBLE_H

