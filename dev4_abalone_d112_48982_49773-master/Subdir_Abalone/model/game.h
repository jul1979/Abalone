#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "movetype.h"
#include"direction.h"
#include <string.h>
#include <memory>
#include"observer/subject.h"

class Game: public nvs::Subject{


private:

std::shared_ptr<Board> m_board;
std::shared_ptr<Player> m_player1 ;
std::shared_ptr<Player> m_player2 ;
std::shared_ptr<Player> m_current ;
std::vector<esi::Direction>m_directions;
int m_sameMarbleCount;






public:

/**
 * @brief play executes a round of play.
 * @return true if the move was successful false otherwise.
 */
bool play(std::string);

/**
 * @brief Game the default constuctor.
 */
Game();

/**
 * @brief getCharAt gets the character representing
 * the state of an hexagon on the board.
 * @return the character representing the state at that position.
 */
char getCharAt(Position);


/*!
 * \brief fromAbaProToPosition changes a coordinate from abaPro system to 3D system.
 * \param coordinate an ABAPRO value
 * \return a 3D position coordinate
 */
Position fromAbaProToPosition(std::string coordinate);


 /*!
   * \brief isOver checks if the game is finished by evaluating the marbles count of each player.
   * \return true the play has ended, false otherwise.
   */

  bool isOver();

  /**
   * @brief winner gets the player who won.
   * @return a pointer to the winning player.
   */
  std::optional<std::shared_ptr<Player>> winner();


  /*!
  * \brief the Destructor.
  */
  ~ Game();
  /**
   * @brief sameMarbleCount gets the same marble count.
   * @return the attribute value.
   */

  inline int sameMarbleCount() const;


  /**
   * @brief current gets the current Player.
   * @return the current player.
   */

  std::shared_ptr<Player> current() const;

private:

  /*!
  * \brief swapPlayers changes the current player to opponent and vice versa.
  */
  void swapPlayers();


/**
 * @brief changeInto2D calculates 2D coordinates from ABA-PRO system.
 * @param lettre the first coordinate in ABA-PRO.
 * @param val the second coordinate in ABA-PRO.
 * @return the 2D coordinates value representated by an instance of Square.
 */
Square changeInto2D(Alphabet lettre, int val);

/**
 * @brief changeInto3D calculates the 3D cordinates from 2D coordinates.
 * @param square the 2D coordinates of an Hexagon.
 * @return the 3D coordinates represented by an instance of Position class.
 */
Position changeInto3D(Square square);

/**
 * @brief enumValue gets the enum corresponding to character.
 * @param charachter the character to get the enum for.
 * @return the Alphabet enum value for that character.
 */
Alphabet enumValue(char charachter);




/**
 * @brief isSumito checks wether a player's column faces a
 * lesser number of marbles than the opponent.
 * @param start the player first marble position in the column.
 * @param end the player last marble position in the column.
 * @return true if the player has an advantage false otherwise.
 */
bool isSumito(Position start,Position end);

/**
 * @brief isRightChar checks wether the character is an acceptable first character as by ABA-PRO system.
 * @param letter the character to check.
 * @return true if is amongst the acceptable characters false otherwise.
 */
bool isRightChar(char letter);
/**
 * @brief isRightDigit checks wether the character is an acceptable second character as by ABA-PRO system.
 * @param letter the character to check.
 * @return true if is amongst the acceptable characters false otherwise.
 */
bool isRightDigit(char character);//p

/**
 * @brief isRightDigit checks wether the character is an acceptable second character as by ABA-PRO system.
 * @overload
 */
bool isRightDigit(char character,int lowerbound,int upperbound);

/**
 * @brief isRightCombinaison checks wether the combination is an acceptable combination as by ABA-PRO system.
 * @param letter the first character in the ABA-PRO system.
 * @param digit the second character in the ABA-PRO system.
 * @return true if the combination of the two is a valid ABA-PRO value.
 */
bool isRightCombinaison(char letter, char digit);

/**
 * @brief clearConsoleData checks if the data entered matches the expected formats in the ABA-PRO system.
 * @param input the data read from the input stream.
 * @return true if the input is valid ABA-PRO value.
 */
bool clearConsoleData(std::string input);





 /**
  * @brief validateUserEntry checks if the every character in the string supplied
  * matches characters expected and the length expected.
  * @param input the string to evaluate.
  * @return true it does false otherwise.
  */
 bool validateUserEntry(std::string input);

 /**
  * @brief playSideWays executes a sideStep move.
  * @param top the first marble position of the column.
  * @param queue the last marble position of the column.
  * @param topEnd the destination position of the first marble.
  * @return true if it succeded as per game rules false otherwise.
  */
bool playSideWays(Position top,Position queue,Position topEnd);

/**
 * @brief playInline executes an inline move.
 * @param start the marble origin position.
 * @param end the marble destination position.
 * @return true if it succeded as per game rules false otherwise.
 */
bool playInline(Position start,Position end);

/**
 * @brief directionFinder finds the direction of sidestep move play.
 * @param start the first marble position.
 * @param end the first marble position destination.
 * @return an optional containing the direction or an empty optional if no valid path.
 */
std::optional<esi::Direction> directionFinder(Position start,Position end);

/**
 * @brief sameColorInRow checks if marbles in column are of same color.
 * @param start the first marble position in the column.
 * @param end the second marble position in the column.
 * @param direction the orientation to from start to end.
 * @return  true if all are of same colors false otherwise.
 */
bool sameColorInRow(Position start ,Position end,esi::Direction direction);

/**
 * @brief isValidForSideMove checks if a direction is valid for sideMoves.
 * @param direction the direction to check.
 * @return true if it is false otherwise.
 */
bool isValidForSideMove(esi::Direction direction);

/**
 * @brief emptySpotsAllTheWay checks if sidestep move can take place.
 * @param start the position of the first marble in the column.
 * @param end the position of the last marble in the column.
 * @param sideStep the direction of the sidestep move.
 * @param direction the direction to go from start to end position.
 * @return true if sideStep possible false otherwise.
 */
bool emptySpotsAllTheWay(Position start,Position end,esi::Direction sideStep,esi::Direction direction);

/**
 * @brief sameRowMarblesPositions gets a vector of positions of neighbour marbles sharing the same colors.
 * @param start the starting position.
 * @param end the final position.
 * @return the vector of positions where marbles are same color.
 */
std::vector<Position>sameRowMarblesPositions(Position start,Position end,esi::Direction);
 /*!
 * \brief play performs a player action on the board by moving his marbles on the Board.
 * \param num the number of Hexagon he wants to  displace.
 * \param current the player whose turn is is.
 * \param movetype the nature of the movement wanted either inline or sidestep.
 */





/**
 * @brief lastSumitoPosition in case of sumito returns an optional with last position of the column
 * if inside the board or an empty optional if outside the board.
 * @param start the starting position.
 * @param end the last position in the column.
 * @return an optinal containing that last position or an empty one.
 */
std::optional<Position> lastSumitoPosition(Position start,Position end);



/*!
 * \brief hasMarbe checks if a marble is present at some postion.
 * \param position the postion to check for a marble.
 * \return true if there is a marble at that position false otherwise.
 */
bool hasMarbe(Position position);

/*!
 * \brief freeSpotInLine counts the number of marbles of the same color as the one at the passed position  going
 * in the direction passed up until it either encounters an hexagon with a marble of a different color,
 * an empty hexagon or gets out of bounds.
 * \param start the position of the first marble.
 * \return the optional that may or may not contain a value if position out of bounds.
 */

 std::optional<Position> freeSpotInLine(Position start,esi::Direction);

/**
 * @brief checkConsoleInput validates that both positions coordinates are inside the board
 * and that they are direct neighbours.It sets the value of the direction from start to end
 *  if previous two conditions are met.
 * @param start the first position.
 * @param end the second position.
 * @return true if they are adjacent,false otherwise.
 */
std::optional<esi::Direction> checkConsoleInput(Position start,Position end);
/*!
 * \brief oppositeDirection gets the opposite direction based of another direction.
 * \param direction the direction supplied.
 * \return the opposite direction.
 */
esi::Direction oppositeDirection(esi::Direction direction);

/*!
 * \brief swapBackwards swaps neighbouring elements marbles recursively.
 * \param queue the position the swapping starts at.
 * \param head the position  the swapping ends.
 * \param direction the orientation the swapping takes place.
 */
void swapBackwards(Position queue,Position head,esi::Direction direction);
};

inline int Game::sameMarbleCount() const
{
 return m_sameMarbleCount;
}







#endif // GAME_H
