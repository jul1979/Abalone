#ifndef VIEW_H
#define VIEW_H
#include<vector>
#include<string>
#include"../model/observer/observer.h"
#include"../model/game.h"

class View:public nvs::Observer
{
Game * subject_;

public:


 /**
 * @brief View Default constructor.
 */
 View(Game* subject);

 /**
  * @brief displayBoard displays the board depicting the State
  * of the Game in the console.
  */
 void displayBoard(Game* subject_);
/*!
 * \brief addSpaces fills line with whitespace.
 * \param spaces the number of whiteSpaces to add.
 */

 /**
  * @brief readUserInput gets the data entered by a player.
  * @param input the data entered by the player.
  */
 void readUserInput(std::string& input);

 /**
  * @brief promptPlayer prompts the current player to enter his move.
  * @param current the player whose turn it is.
  */
 void promptPlayer(std::string current);
 /**
  * @brief displaError informs the current player that the input entered
  * is not valid by displaying a message in the console.
  */
 void displaError();
 /**
  * @brief displayWinner informs the competitors of the one
  *  who has won the game.
  */
 void displayWinner(std::string);



 /**
  * @brief update virtual method that every concrete observer must
   * implement: this is the method called by the subject observed during
   * a notification.
  * @param subject the subject of observation that notifies a change.
  */
 virtual void update( const nvs::Subject * subject) override;
 /**
  * @brief ~View Default virtual destructor.
  * Unsubscribes the observer.
  */
 virtual ~View() override;

private:

void addSpaces(int spaces);
/**
 * @brief addLetter appends a letter to a line.
 * @param number the row number to add the letter to.
 */
void addLetter(int number);
/**
 * @brief addBorderEast appends a final String to the boarder.
 * @param number the line number to add it to.
 */
void addBorderEast(int number);
/**
 * @brief addBorderWest appends a final String to the boarder.
 * @param number the line number to add it to.
 */
void addBorderWest(int number);

/**
 * @brief addTopBoarder appends a line separator
 * to distinguish each boarder display from the previous one.
 * @param number the number of times the character is appended to the line.
 */
void addTopBoarder(int number);
/**
 * @brief addBottomBoarder appends the final line to
 * the console representation of the board.
 */
void addBottomBoarder();

};

#endif // VIEW_H
