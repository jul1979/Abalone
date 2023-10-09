#ifndef COLOR_H
#define COLOR_H

#include<iostream>



/**
 * \brief The Color enum
 * This enumeration represents the colors of the Players
 *  and the colors of the marbles.
 */

enum Color
{
    WHITE,
    BLACK
};

/**
  * @brief operator << this method overloads the insertion operator.
  * @param output, the output stream.
  * @param color, the color to insert.
  * @return a reference to the output stream.
  */
 inline std::ostream &operator<<(std::ostream & output,const Color &color );

 /**
  * @brief to_string a string representation of  a color.
  * @param color, the color to provide a string for.
  * @return a string representation for that color.
  */
 inline std::string to_string(Color color);

 inline std::string to_string(Color color) {
     if(color == Color::BLACK) {
         return "BLACK";
     }
     return "WHITE";
 }

 inline std::ostream & operator << (std::ostream & out, const Color & color) {
     return out << to_string(color);
 }

#endif // COLOR_H
