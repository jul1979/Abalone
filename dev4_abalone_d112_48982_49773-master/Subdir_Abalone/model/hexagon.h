#ifndef HEXAGON_H
#define HEXAGON_H

#include"position.h"
#include<optional>
#include<iostream>
#include"marble.h"
#include <iostream>
#include<memory.h>

using namespace std;
/**
 * @brief The Hexagon class
 *  represents an Hexagon on the the Board.
 */
class Hexagon {

private:

    Position m_coordinates;
    std::optional<Marble> m_marble;
public:

  /**
 * @brief Hexagon Constructor.Creates an Hexagon of the Board.
 * @param coordinatesin the coordinates of the Hexagon.
 */

    Hexagon(Position coordinatesin, std::optional< Marble > marble =std::nullopt);




   /**
 * @brief gets the position coordinates.
 * @return the position coordinates of the hexagon.
 */
    inline Position coordinates()const;

    /*!
 * \brief hasMarble checks if a marble is present on the Hexagon.
 * \return true if the hexagon has a marble on it, false otherwise.
 */
    inline bool hasMarble() const;


    /**
 * @brief marble,gets the wrapping optional that may
 * or may not contain a marble.
 * @return the optional wrapper.
 */
  inline std::optional<Marble>& marble();
  /**
    * @brief operator = overloads  the assignement operator.
    * @return the hexagon after assignement.
    */

   Hexagon& operator=(const Hexagon &);

   /**
    * @brief operator ==overloads the equality operator.
    * @return true if both hexagons have the same position false otherwise.
    */
   friend bool operator==(const Hexagon &,const Hexagon &);

   /**
     * @brief operator   << this method overloads the insertion operator.
     * @param output, the output stream.
     * @param Hexagon, the Hexagon to insert.
     * @return a reference to the output stream.
     */
   friend std::ostream& operator<<(std::ostream& out, const Hexagon& h);


};


inline Position Hexagon::coordinates() const{
    return m_coordinates;
}

inline bool Hexagon::hasMarble() const {
    return m_marble.has_value();
}

inline std::optional<Marble> & Hexagon::marble(){
    return m_marble;
}



#endif // HEXAGON_H
