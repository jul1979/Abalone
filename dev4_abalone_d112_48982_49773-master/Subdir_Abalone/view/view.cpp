#include "view.h"
#include<iostream>
#include<cmath>
#include<iomanip>
#include<limits>
#include<ios>

View::View(Game *subject):subject_{subject}
{
    subject_->registerObserver(this);
    update(subject);
}

void View::displayBoard(Game* subject_)
{
    int stopz=0;
    int stopy=4;
    int stopx=-4;
    int x,y,z;
    std::pair<int,int>result;
    std::cout<<setfill('-')<<setw(11)<<" "<<"\n";
    std::cout<<setfill('\000');
    for(;(stopx<=0 && stopy>=-4 );stopz++,stopy--){

        if(stopz>=4){stopz=4;}
        if(stopy==-1||stopy==-2||stopy==-3||stopy==-4){++stopx;}

        addSpaces(stopy);
        addBorderWest(stopy);

        for( x=stopx,z=stopz,y=stopy; x<=stopz; x++,z--){

            Position p(x,y,z);
            result=p.axialCoordinates();
            std::cout<<std::setw(2)<<
            subject_->getCharAt(p);
        }
        addBorderEast(stopy);
        addSpaces(stopy);
        std::cout<<"\n";
    }
    addBottomBoarder();
    std::cout<<"\n \n";
}



void View::addSpaces(int number)
{
   int spaces=abs(number);
    if (spaces>0) {
      for(int i=1;i<=spaces;i++){
          std::cout <<'\000';
        }
    }
}

void View::addLetter(int lineNo)
{
    switch (lineNo) {
    case -4: std::cout<<"A--";
          break;
    case -3: std::cout<<"B--";
          break;
    case -2: std::cout<<"C--";
           break;
    case -1: std::cout<<"D--";
           break;
    case 0: std::cout<<"E--";
           break;
    case 1:std::cout<<"F--";
           break;
    case 2:std::cout<<"G--";
           break;
    case 3:std::cout<<"H--";
            break;
    case 4:std::cout<<"I--";
            break;
    }
}

void View::addBorderEast(int number)
{
    if (number>0) {
        std::cout<<'\\';
        } else if(number<0){
        std::cout<<"/\\";
        switch (number) {
        case -2:
            std::cout<<" 9";
            break;
        case -3:
            std::cout<<" 8";
            break;
        case -4:
            std::cout<<" 7";
            break;
        }
        }else{
        std::cout<<')';
    }
}

void View::addBorderWest(int number)
{
    addLetter(number);
    if (number>0) {
    std::cout<<'/';
    } else if(number<0) {
    std::cout<<'\\';
    }else{
     std::cout<<'(';
    }
}

void View::promptPlayer(std::string current)
{
  std::cout<<" PLAYER:"<< current<<",Enter your MOVE: "<<std::endl ;
}

void View::displaError()
{
    std::cout<<"You entered an invalid MOVE/INPUT!"<<std::endl;
    std::cout<<"TRY AGAIN !"<<std::endl;
}

void View::displayWinner(std::string color)
{
    std::cout<<"CONGRATULATIONS PLAYER: "<<color<<"!"<<"YOU WON!"<<std::endl;
}

void View::addTopBoarder(int number)
{
    addSpaces(number);
    for(int i=1;i<=5;i++){
    std::cout<<std::setw(2)<<'-';
    }
   addSpaces(number);
    std::cout<<"\n";
}

void View::addBottomBoarder()
{
    addSpaces(9);
    for(int i=1;i<=5;i++){
    std::cout<<std::setw(2)<<'\\';
    }
     std::cout<<std::setw(2)<<'6';
    addSpaces(8);
    std::cout<<"\n";
    addSpaces(10);
    for(int i=1;i<=5;i++){
    std::cout<<std::setw(2)<<i;
    }
}

void View::readUserInput(std::string & input)
{
    std::cin>>input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

void View::update(const nvs::Subject *subject)
{
   if (subject != subject_) return;
    displayBoard(subject_);
}

View::~View()
{
   subject_->unregisterObserver(this);
}
