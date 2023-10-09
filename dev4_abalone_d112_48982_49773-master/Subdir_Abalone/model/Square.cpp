#include "square.h"

Square::Square(int x, int y) : m_x{x}, m_y {y}
{

}

std::ostream & operator<<(std::ostream & out, const Square& square)
{
    return out << "( " << square.getX() << " , " << square.getY() << " ) " << std::endl;
}

