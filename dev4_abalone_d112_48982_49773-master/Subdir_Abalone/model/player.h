#ifndef PLAYER_H
#define PLAYER_H

#include"color.h"
#include<string>

class Player{

private:
    Color m_color;

public:

    /*!
     * \brief Player Constructor.Instantiates a player.
     * \param color the color of the player.
     */
    Player(Color color);
    /*!
     * \brief getColor gets the player color.
     * \return the player color.
     */
    inline Color getColor()const;

    /**
     * @brief operator << overloaded insertion operator.
     * @param out the output stream.
     * @param colorin the color to inject  in the output stream.
     * @return the output stream.
     */
    friend std::ostream & operator<<(std::ostream &out, const Color &colorin);

    /*!
     * \brief to_string creates a string representing the player.
     * \param color the Player color.
     * \return a string represenation of the player.
     */
    inline  std::string to_string(Color color);

};

inline Color Player::getColor() const {
    return m_color;
}

inline std::string Player::to_string(Color color) {
    if(color == Color::BLACK) {
        return "BLACK(X)";
    }
    return "WHITE(O)";
}


#endif // PLAYER_H
