#include "player.h"

Player::Player(Color color) : m_color {color} {}

std::ostream & operator << (std::ostream & out, const Player & player) {
    return out << player.getColor();
}
