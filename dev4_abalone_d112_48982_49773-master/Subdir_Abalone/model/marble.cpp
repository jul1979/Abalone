#include "marble.h"

Marble::Marble(Color color) : m_color {color} {}

std::ostream & operator << (std::ostream & out, const Marble & marble) {
    return out << "Marble: " << marble.color();
}

Marble& Marble::operator=(const Marble &marblein) {
    m_color = marblein.color();
    return *this;
}
