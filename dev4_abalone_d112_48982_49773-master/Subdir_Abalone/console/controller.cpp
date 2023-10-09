
#include "controller.h"
#include<iomanip>
#include<limits>

std::shared_ptr<Game> Controller::game() const
{
    return m_game;
}

std::shared_ptr<View> Controller::view() const
{
    return m_view;
}



Controller::Controller()
{
    m_game=make_shared<Game>();
    m_view=make_shared<View>(m_game.get());
}

void Controller::start()
{

    std::string input;

    while(!m_game->isOver()){
        m_view->promptPlayer(m_game->current()->to_string(m_game->current()->getColor()));
        m_view->readUserInput(input);
        while(!m_game->play(input)){
            m_view->displaError();
            m_view->promptPlayer(m_game->current()->to_string(m_game->current()->getColor()));
            m_view->readUserInput(input);
        }

    }
    m_view->displayWinner(m_game->winner()->get()->to_string(m_game->current()->getColor()));
}
