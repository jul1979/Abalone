#include "hexagon.h"


  Hexagon::Hexagon(Position coordinatesin, std::optional< Marble > marble) : m_coordinates{coordinatesin},
      m_marble{marble}
    {}

Hexagon &Hexagon::operator=(const Hexagon & hex)
{
    if(hex.hasMarble()){
    marble()=hex.m_marble;
    }
    return *this;
}

ostream & operator<<(ostream &out, const Hexagon &h)
{
    std::string noColor="no color";
    if (h.hasMarble()) {
        if (h.m_marble.value().color()==Color::BLACK) {
            out<<" " <<'X'<<" ";
        } else if(h.m_marble.value().color()==Color::WHITE) {
            out<<" " <<'O'<<" ";
        }
    } else {
        out<<" " <<'.'<<" ";
    }
return out;
}

bool operator==(const Hexagon  & h1, const Hexagon & h2)
{
        return ((h2.coordinates().x()==h1.coordinates().x())
                   &&
                (h2.coordinates().y()==h1.coordinates().y())
                   &&
                (h2.coordinates().z()==h1.coordinates().z())

               );


}





