
#include "game.h"
#include<algorithm>


std::shared_ptr<Player> Game::current() const
{
    return m_current;
}


Square Game::changeInto2D(Alphabet lettre, int val)
{
    return m_board->translateInto2D(lettre,val);
}

Position Game::changeInto3D(Square square)
{
    return m_board->backTo3Dcoordinates(square);
}

Alphabet Game::enumValue(char charachter)
{
    int value= toupper(charachter);
    char letter=static_cast<char>(value);
    switch (letter) {
    case 'A':return Alphabet::A;
    case 'B':return Alphabet::B;
    case 'C':return Alphabet::C;
    case 'D':return Alphabet::D;
    case 'E':return Alphabet::E;
    case 'F':return Alphabet::F;
    case 'G':return Alphabet::G;
    case 'H':return Alphabet::H;
    case 'I':return Alphabet::I;

    }
}

char Game::getCharAt(Position position)
{
    if (m_board->getHexagonAt(position)->hasMarble()){
      if(m_board->getHexagonAt(position)->marble()->color()==Color::BLACK )
       return 'X';
      else if((m_board->getHexagonAt(position)->marble()->color()==Color::WHITE)){
        return 'O';
    }

    }return '.';
}

Position Game::fromAbaProToPosition(std::string coordinate)
{
    int a=static_cast<int>(coordinate.at(1));
    int abis=a%48;
    Square result=changeInto2D(enumValue(coordinate.at(0)),abis);
    return changeInto3D(result);
 }

bool Game::play(std::string input)
{
    bool executedInline=false;
    bool executedStepSide=false;
    if(clearConsoleData(input)){
        size_t length=input.length();
        switch (length) {
        case 4:{
        int a=static_cast<int>(input.at(1));
        int abis=a%48;
        int b=static_cast<int>(input.at(3));
        int bbis=b%48;
        Square origin=changeInto2D(enumValue(input.at(0)),abis);
        Square destination=changeInto2D(enumValue(input.at(2)),bbis);
        Position start=changeInto3D(origin);
        Position end=changeInto3D(destination);
        executedInline=playInline(start,end);
        break;}
        case 6:{
        int c=static_cast<int>(input.at(1));
        int cbis=c%48;
        int d=static_cast<int>(input.at(3));
        int dbis=d%48;
        int e=static_cast<int>(input.at(5));
        int ebis=e%48;


        Square originTop=changeInto2D(enumValue(input.at(0)),cbis);
        Square destinationQueue=changeInto2D(enumValue(input.at(2)),dbis);
        Square destinationTopEnd=changeInto2D(enumValue(input.at(4)),ebis);
        Position startTop=changeInto3D(originTop);
        Position endQueue=changeInto3D(destinationQueue);
        Position startTopEnd=changeInto3D(destinationTopEnd);
        executedStepSide=playSideWays(startTop,endQueue,startTopEnd);

        break;
        }
       }
       }
    if(executedStepSide||executedInline) {
     notifyObservers();
     if(!isOver()){
         swapPlayers();
     }
    }
    return executedInline||executedStepSide;

}

bool Game::isSumito(Position start, Position end)
{

    std::optional<Position>sumito=lastSumitoPosition(start,end);
    bool step1=  (sumito.has_value( ) && m_board->getHexagonAt(start)->marble()->color()!=
            m_board->getHexagonAt(sumito.value())->marble()->color());

    bool step2=  (sumito.has_value( ) && !hasMarbe(sumito.value()));

    return step1 || step2;
}









Game::Game():m_sameMarbleCount{0}
{
    m_board=make_shared<Board>();
    m_player1=make_shared<Player>(Color::BLACK);
    m_player2=make_shared<Player>(Color::WHITE);
    m_current=m_player1;
    m_directions.push_back( esi::Direction::EAST);
    m_directions.push_back( esi::Direction::WEST);
    m_directions.push_back( esi::Direction::NORTHEAST);
    m_directions.push_back( esi::Direction::NORTHWEST);
    m_directions.push_back( esi::Direction::SOUTHEAST);
    m_directions.push_back( esi::Direction::SOUTHWEST);
}





void Game::swapPlayers()
{
   m_current->getColor()==Color::BLACK?m_current=m_player2:m_current=m_player1;

}

bool Game::isRightChar(char letter)
{
    char myLetter = letter;
    if(islower(letter)) {
        myLetter = static_cast<char>(toupper(letter));

    }
    return (myLetter >= 'A' && myLetter <= 'I');
}

bool Game::isRightDigit(char character){

    if(isdigit(character)) {
        int value = static_cast<int>(character);
        int newVal = value % 48;
        return newVal >= 1 && newVal <= 9;
    }
    return false;


}

bool Game::clearConsoleData(std::string input)
{
    if(validateUserEntry(input)){
        size_t length=input.length();
        switch (length) {
        case 4:return isRightCombinaison(input.at(0),input.at(1))&&isRightCombinaison(input.at(2),input.at(3));
        case 6:
        return isRightCombinaison(input.at(0),input.at(1))&&isRightCombinaison(input.at(2),input.at(3))&&
                                                                      isRightCombinaison(input.at(4),input.at(5));
        }
    }
    return false;
}
bool Game::isRightDigit(char character,int lowerbound,int upperbound)
{

    if(isdigit(character)) {
        int value = static_cast<int>(character);
        int newVal = value % 48;
        return newVal >= lowerbound && newVal <= upperbound;
    }
    return false;
}

bool Game::isRightCombinaison(char letter, char digit)
{
    if (islower(letter)) {
        letter=static_cast<char>((toupper(letter)));
    }

    switch (letter) {
    case 'A':
           return isRightDigit(digit,1,5);
    case 'B':
          return isRightDigit(digit,1,6);
    case 'C':
          return isRightDigit(digit,1,7);
    case 'D':
          return isRightDigit(digit,1,8);
    case 'E':
          return isRightDigit(digit,1,9);
    case 'F':
          return isRightDigit(digit,2,9);
    case 'G':
          return isRightDigit(digit,3,9);
    case 'H':
          return isRightDigit(digit,4,9);
    case 'I':
          return isRightDigit(digit,5,9);
    }

    return false;

}


bool Game::validateUserEntry(std::string input)
{
    size_t length = input.length();
    switch (length) {
    case 4:
        return (isRightChar(input.at(0))&&
                isRightDigit(input.at(1)) &&
                isRightChar(input.at(2)) &&
                isRightDigit(input.at(3)));


    case 6: return (isRightChar(input.at(0)) &&
                    isRightDigit(input.at(1)) &&
                    isRightChar(input.at(2)) &&
                    isRightDigit(input.at(3))&&
                    isRightChar(input.at(4)) &&
                    isRightDigit(input.at(5)));
    default:
        return false;
    }

}

bool Game::playSideWays(Position top, Position queue, Position topEnd)
{

    bool success=false;
    std::optional<esi::Direction>direction=directionFinder(top,queue);
    std::optional<esi::Direction>sideMoveDirection=directionFinder(top,topEnd);
    if(direction && sideMoveDirection){
        std::optional<esi::Direction>direction=std::optional<esi::Direction>(in_place,directionFinder(top,queue).value());
        std::optional<esi::Direction>sideMoveDirection=std::optional<esi::Direction>(in_place,directionFinder(top,topEnd).value());

        if(sameColorInRow(top,queue,direction.value())&& isValidForSideMove(sideMoveDirection.value())){

            bool neighbours=(topEnd==top.getPositionTo(sideMoveDirection.value()));

            if(neighbours&&emptySpotsAllTheWay(top,queue,sideMoveDirection.value(),direction.value())){

                success=true;

                for(auto m:sameRowMarblesPositions(top,queue,direction.value())){

                    playInline(m,m.getPositionTo(sideMoveDirection.value()));
                }
            }


        }

    }

    return  success;
}



std::optional<esi::Direction> Game::directionFinder(Position start,Position end)
{
    bool found=false;
    Position current=start;
    std::optional<esi::Direction> sideStepDirection=std::nullopt;
    for(auto dir:m_directions){
        while( m_board->isInside(current)&& !found){
            found=current==end;
            current=current.getPositionTo(dir);
        }
        if(found){
            sideStepDirection=std::optional<esi::Direction>(in_place,dir);
            break;
        }
        current=start;
    }
    return sideStepDirection;

}

bool Game::sameColorInRow(Position start, Position end, esi::Direction direction)
{
    unsigned count=0;
    Position current=start;
    while (current!=end) {
        count++;
        current=current.getPositionTo(direction);
    }
    if(current==end)count++;
    return (count==2|| count ==3||count==1);
}

bool Game::isValidForSideMove(esi::Direction direction)
{
    std::vector<esi::Direction>directions;
    directions.push_back( esi::Direction::NORTHEAST);
    directions.push_back( esi::Direction::NORTHWEST);
    directions.push_back( esi::Direction::SOUTHEAST);
    directions.push_back( esi::Direction::SOUTHWEST);
    auto iter= std::find(directions.begin(),directions.end(),direction);
    return iter!=directions.end();
}

bool Game::emptySpotsAllTheWay(Position start, Position end, esi::Direction sideStep, esi::Direction direction)
{
    int empty=0;
    Position current=start;
    while (current!=end) {
        if (hasMarbe(current.getPositionTo(sideStep))) {
            empty++;
        }
        current=current.getPositionTo(direction);
    }
    if(hasMarbe(end.getPositionTo(sideStep))) {
        empty++;
    }
    return  empty==0;
}

std::vector<Position> Game::sameRowMarblesPositions(Position start,Position end,esi::Direction direction)
{
    std::vector<Position>positions;

    for (Position current=start ;current!=end ;current=current.getPositionTo(direction)){
        if(m_board->isInside(current))
            positions.push_back(current);
    }
    positions.push_back(end);
    return positions;
}

bool Game::isOver()
{
   // return isOver();
    return ((m_board->countMarblesLeft(Color::BLACK)==8)|| (m_board->countMarblesLeft(Color::WHITE)==8));
}

//std::shared_ptr<Player> Game::winner()
std::optional<std::shared_ptr<Player>>Game::winner()
{
    std::optional<std::shared_ptr<Player>>temp;
    if(isOver()){
        return  m_current;
     }else return temp ;
}




std::optional<Position> Game::lastSumitoPosition(Position start, Position end)
{

    std::optional<esi::Direction> checkInput=checkConsoleInput(start,end);
    bool inputOk=checkInput.has_value();
    bool colorChanged=false;
    bool step2=false;
    std::optional<Position>row2=std::nullopt;
    std::optional<Position>result;

    if (inputOk) {
        std::optional<Position>nextStart=freeSpotInLine(start,checkInput.value());

        if(this->hasMarbe(nextStart.value())){
            colorChanged=(m_board->getHexagonAt(nextStart.value())->marble()->color()
                          !=m_board->getHexagonAt(start)->marble()->color());
        }
        bool step1=((this->sameMarbleCount()==3||this->sameMarbleCount()==2)&& colorChanged);

        if(step1 ){
            row2=freeSpotInLine(nextStart.value(),checkInput.value());
            step2=this->sameMarbleCount()==2||this->sameMarbleCount()==1;
        }
        if( (step1&& step2) && this->hasMarbe(row2.value()) && (m_board->getHexagonAt(row2.value())->marble()->color()==

                                                                m_board->getHexagonAt(start)->marble()->color() ) )

        {
            result= std::nullopt;


        }else if((step1&& step2) && this->hasMarbe(row2.value()) &&
                 ( (m_board->getHexagonAt(row2.value())->marble()->color()!=m_board->getHexagonAt(start)->marble()->color())) )


        {
            result= std::optional<Position>(in_place,row2.value().x(),row2.value().y(),row2.value().z());

        }else if( (step1&& step2) && !hasMarbe(row2.value())){


            result= std::optional<Position>(in_place,row2.value().x(),row2.value().y(),row2.value().z());
        }

    }
    return  result;


}

Game::~Game()
{
}

bool Game::playInline(Position start, Position end)
{

    std::optional<esi::Direction> checkInput=checkConsoleInput(start,end);
    bool success=false;
    if(!this->hasMarbe(start)&&!this->hasMarbe(end))return success;
    if(m_board->getHexagonAt(start)->marble()->color()!=m_current->getColor()) return success;
    if (checkInput.has_value()) {
        std::optional<Position>queue =freeSpotInLine(start,checkInput.value());
        if (( m_sameMarbleCount>=1 && m_sameMarbleCount<=3)&& (queue.has_value() && !this->hasMarbe(queue.value()))) {
            swapBackwards(queue.value(),start,checkInput.value());
            success=true;
           // notifyObservers();
        }
        else if(isSumito(start,end)) {
            std::optional<Position>last=lastSumitoPosition(start,end).value();
            if (hasMarbe(last.value())) {
              m_board->getHexagonAt(last.value())->marble().reset();
            }
            swapBackwards(last.value(),start,checkInput.value());
            success=true;
           // notifyObservers();
          }
     }

    return success;

}

bool Game::hasMarbe(Position position)
{
    return m_board->getHexagonAt(position)->hasMarble();
}

std::optional<Position> Game::freeSpotInLine(Position current, esi::Direction direction)
{

    std::optional<Position> sentinel;

    std::optional<Position> result;

    if (m_board->getHexagonAt(current)->hasMarble()) {
        m_sameMarbleCount=0;
        m_sameMarbleCount++;
    }

    Position nextPosition=current.getPositionTo(direction);

    while(m_board->isInside(nextPosition) && (*(m_board->getHexagonAt(nextPosition))).hasMarble()){

        if((*m_board->getHexagonAt(nextPosition)).marble()->color()== ((*m_board->getHexagonAt(current)).marble()->color())){
            m_sameMarbleCount++;
            current=nextPosition;
            nextPosition=current.getPositionTo(direction);
        }else{

            break;
        }

    }
    sentinel= std::optional<Position>(in_place,current.x(),current.y(),current.z());

    result= std::optional<Position>(in_place,nextPosition.x(),nextPosition.y(),nextPosition.z());

    if (m_board->isInside(nextPosition)) {

        return result;
    } else {

        return sentinel;
    }

}


void Game::swapBackwards(Position queue, Position head,esi::Direction direction)
{
    if(m_board->isBorder(queue,direction)){
        m_board->getHexagonAt(queue)->marble().reset();
    }
    esi::Direction backwards=oppositeDirection(direction);
    while( m_board->isInside(queue) && queue!=head){
        (m_board->getHexagonAt(queue))->marble().
                swap(m_board->getHexagonAt(queue.getPositionTo(backwards))->marble());
        queue=queue.getPositionTo(backwards);
    }
}

std::optional<esi::Direction> Game::checkConsoleInput(Position start, Position end)
{

    if(m_board->isInside(start)&&m_board->isInside(end)){

        for(auto m: m_directions) {

            if (m_board->neighbour(*m_board->getHexagonAt(start),m)) {

                if( m_board->neighbour(*m_board->getHexagonAt(start),m).value()==* m_board->getHexagonAt(end)){
                    return std::optional<esi::Direction>(m);
                }
            }

        }

    }

    return std::nullopt;
}

esi::Direction Game::oppositeDirection(esi::Direction direction)
{
    esi::Direction result;

    switch (direction) {

    case esi::Direction::EAST:
        result =esi::Direction::WEST;
        break;
    case esi::Direction::WEST:
        result = esi::Direction::EAST;
        break;
    case esi::Direction::NORTHEAST:
        result =esi::Direction::SOUTHWEST;
        break;
    case esi::Direction::NORTHWEST:
        result =esi::Direction::SOUTHEAST;
        break;
    case esi::Direction::SOUTHEAST:
        result =esi::Direction::NORTHWEST  ;
        break;
    case esi::Direction::SOUTHWEST:
        result = esi::Direction::NORTHEAST;
        break;
    }
    return result;
}




