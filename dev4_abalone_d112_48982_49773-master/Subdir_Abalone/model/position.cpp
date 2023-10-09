#include "position.h"


Position::Position(int x, int y, int z) : m_x{x}, m_y{y}, m_z{z} {}


Position::Position(const Position & other)
{
    m_x = other.x();
    m_y = other.y();
    m_z = other.z();
}

Position& Position::operator=(const Position &right_handside)
{
    m_x=right_handside.x();
    m_y=right_handside.y();
    m_z=right_handside.z();
    return *this;
}

std::pair<int, int> Position::axialCoordinates()
{
    std::pair<int,int>result;
    result=std::make_pair(m_x,m_y);
    return result;
}

Position Position::getPositionTo(esi::Direction direction)
{

    int valX ;
    int valY ;
    int valZ ;

    switch (direction) {
    case esi::Direction::EAST:

        valX = m_x + 1;
        valY = m_y;
        valZ = m_z - 1;

        break;
    case esi::Direction::WEST:

        valX = m_x - 1;
        valY = m_y;
        valZ = m_z + 1;



        break;
    case esi::Direction::NORTHEAST:
        valX = m_x ;
        valY = m_y+1;
        valZ = m_z - 1;


        break;
    case esi::Direction::NORTHWEST:
        valX = m_x - 1;
        valY = m_y+1;
        valZ = m_z ;


        break;
    case esi::Direction::SOUTHEAST:
        valX = m_x + 1;
        valY = m_y -1;
        valZ = m_z ;



        break;
    case esi::Direction::SOUTHWEST:
        valX = m_x;
        valY = m_y -1;
        valZ = m_z + 1;


        break;
    }
    return Position(valX,valY,valZ);

}

bool operator!=(const Position &c1, const Position &c2)
{

    return !(c1 == c2);
}

bool operator==(const Position &position, const Position &position2)
{
    return (( position.x() == position2.x()) &&
            ( position.y() == position.y()) &&
            ( position.z() == position2.z()));
}




std::ostream & operator << (std::ostream & out, const Position & positionin) {
    out << "position: " << positionin.x() << " " << positionin.y() <<
           " " << positionin.z();
    return out;
}

