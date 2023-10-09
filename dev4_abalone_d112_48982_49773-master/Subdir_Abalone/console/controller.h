#ifndef CONTROLLER_H
#define CONTROLLER_H
#include"game.h"
#include"view.h"
#include<memory.h>


class Controller{

private:
    std::shared_ptr<Game> m_game;
    std::shared_ptr<View>m_view;

public:
 /*!
 * \brief Default constructor.
 * creates an instance of Game and View classes.
 */
    Controller();
 /*!
 * \brief start,launches the application in the console.
 */
    void start();
    std::shared_ptr<Game> game() const;
    std::shared_ptr<View> view() const;
 /*!
 * \brief displayBoard  displays the board on the console.
 */
   // void displayBoard();

};

#endif // CONTROLLER_H
