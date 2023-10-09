#include "widget.h"
#include <cmath>
#include<QDebug>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>

widget::widget(Game *subject, QWidget *parent) : QWidget(parent),subject_{subject},
    _gHexaCells {},selectedCells{}
{
    subject->registerObserver(this);
    QHBoxLayout *layout=new QHBoxLayout(this);

    winner=new QTextEdit(this);
    winner->setHtml("<h1 style=color:SeaGreen;>WELCOME TO ABALONE.<br>PLAYER BLACK STARTS.<br>TO PLAY SELECT TWO CELLS FOR A LINE MOVE.<br>"
                    "OR SELECT THREE CELLS FOR A SIDESTEP MOVE.<br>AND HIT PLAY BUTTON.</h1>");
    winner->setReadOnly(true);
    winner->setAlignment(Qt::AlignCenter);
    playButton =new QPushButton("PLAY",this);
    populateScene();
    scene = new QGraphicsScene();

    std::for_each(begin(_gHexaCells), end(_gHexaCells),
                  [this](GHexaCell * e) {

        e->mapToScene(QPointF(x(),y()));
        scene->addItem(e);
        QObject::connect(e,
                         SIGNAL(sendValue(std::string,QColor)),
                         this,
                         SLOT(on_ghexacell_clicked(std::string,QColor)));
    });
    makeSelectable(Qt::cyan);
    makeSelectable(Qt::black);
    QObject::connect(playButton,SIGNAL(clicked()),this,
                     SLOT(on_play_Clicked()));
    QObject::connect(this,SIGNAL(changePlayer(Color)),this,SLOT(on_change_player(Color)));


    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::TextAntialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setDragMode(QGraphicsView::ScrollHandDrag);

    view->update();
    layout->addWidget(view);
    layout->addWidget(playButton);
    layout->addWidget(winner);
    resize(1000, 800);
    setLayout(layout);
}

void widget::displayBoard(Game *subject_)
{
    char current;
    for (QGraphicsItem * item :scene->items()){
        GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
        Position p3D= subject_->fromAbaProToPosition(cell->value());
        current= subject_->getCharAt(p3D);
        switch (current) {
        case '.':
            cell->setColor(Qt::cyan);
            break;
        case 'X':
            cell->setColor(Qt::black);
            break;
        case'O':
            cell->setColor(Qt::white);
            break;
        default:
            break;
        }
    }
}

void widget::addHexaCellRow(char letr, int number, int lower)
{
    int total=1;
    double rad = 25;
    double w = sqrt(3) / 2 * rad;
    QColor color=Qt::cyan;
    if (letr=='I'||letr=='H'){
        color=Qt::white;
    }

    if (letr=='E') {
        current=std::make_pair(-173.205,0);
    }else{
        current=std::make_pair(next.first,next.second);
    }
    while (total<=number) {
        if (total==2) {

            next=std::make_pair(current.first-w,current.second-((3./2)*rad));
        }

        std::string coord="";
        coord.push_back(letr);
        coord+=std::to_string(lower);
        lower++;
        if (coord=="G5"||coord=="G6"||coord=="G7"){
            color=Qt::white;
        }
        if (coord=="G8"||coord=="G9") {
            color=Qt::cyan;
        }
        _gHexaCells.push_back( new GHexaCell(rad,current.first,current.second,coord,false,color,nullptr));
        current.first+=2*w;
        total++;
    }
}

void widget::addHexaCellRow2(char letr, int number, int lower)
{
    int total=1;
    double rad = 25;
    double w = sqrt(3) / 2 * rad;
    QColor color=Qt::cyan;
    if (letr=='A'||letr=='B'){
        color=Qt::black;
    }

    if (letr!='D') {

        current=std::make_pair(next.first,next.second);
    }

    while (total<=number) {
        if (total==2) {
            next=std::make_pair(current.first-w,current.second+((3./2)*rad));
        }
        std::string coord="";
        coord.push_back(letr);
        coord+=std::to_string(lower);
        if (coord=="C3"||coord=="C4"||coord=="C5"){

            color=Qt::black;
        }
        if (coord=="C6"||coord=="C7") {

            color=Qt::cyan;
        }
        lower++;
        _gHexaCells.push_back (new GHexaCell(rad,current.first,current.second,coord,false,color,nullptr));
        current.first+=2*w;
        total++;
    }
}

void widget::makeSelectable(QColor color)
{
    for(auto item: scene->items()){
        GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
        if(cell->color()==color){
            cell->setIsSelectable(true);
        }
    }
}

void widget::on_ghexacell_clicked(std::string value,QColor color)
{
    Color co;
    if (color==Qt::black) {
        co=Color::BLACK;
    }
    if(color==Qt::white){
        co=Color::WHITE;
    }
    if(std::count(selectedCells.begin(), selectedCells.end(), value)){
        auto it = std::find(std::begin(selectedCells), std::end(selectedCells), value);
        selectedCells.erase(it);
    }else{
        if ((subject_->current()->getColor()==Color::BLACK && color==Qt::black) ||(
                    subject_->current()->getColor()==Color::WHITE && color==Qt::white )||
                color==Qt::cyan)
        {
            selectedCells.push_back(value);
            qDebug()<<value.c_str()<<endl;
        }



    }
}

void widget::on_play_Clicked()
{
    if (subject_->current()->getColor()==Color::BLACK){
        for(auto item: scene->items()){
            GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
            if(cell->color()==Qt::black)
                cell->setIsSelectable(true);
            cell->setSelected(false);
        }
    }
    if (subject_->current()->getColor()==Color::WHITE){
        for(auto item: scene->items()){
            GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
            if(cell->color()==Qt::white)
                cell->setIsSelectable(true);
            cell->setSelected(false);
        }
    }



    QList<GHexaCell *>list;
    std::string argument;
    for (std::string abapro : selectedCells) {
        argument+=abapro;
    }
    for(auto item: scene->items()){
        GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);

        auto result = std::find(std::begin(selectedCells),std::end(selectedCells), cell->value());
        if(result!=selectedCells.end()){
            list.append(cell);
            cell->setSelected(false);
        }
    }
    if(selectedCells.size()==2||selectedCells.size()==3){
        bool changeOccured=subject_->play(argument);
        if(changeOccured){
          emit changePlayer(subject_->current()->getColor());
        }
    }

    else{

        foreach (GHexaCell * item , list) {
            item->setSelected(false);
        }
    }
    selectedCells.clear();
    list.clear();
}

void widget::on_change_player(Color name)
{

    if(name==Color::BLACK){

        for(auto item: scene->items()){
            GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
            if(cell->color()==Qt::black)
                cell->setIsSelectable(true);
            if(cell->color()==Qt::white)
               cell->setIsSelectable(false);
              winner->setHtml("<h1 style=color:Tomato;>CURRENT PLAYER:BLACK</h1>");
        }
    }
    if(name==Color::WHITE){
        for(auto item: scene->items()){
            GHexaCell * cell=qgraphicsitem_cast<GHexaCell *>(item);
            if(cell->color()==Qt::white)
                cell->setIsSelectable(true);
            if(cell->color()==Qt::black)
                cell->setIsSelectable(false);
           winner->setHtml("<h1 style=color:Tomato;>CURRENT PLAYER:WHITE</h1>");
        }
    }
}



void widget::populateScene()
{
    current=std::make_pair(-173.205,0);
    double rad = 25;
    double w = sqrt(3) / 2 * rad;

    addHexaCellRow('E',9,1);

    addHexaCellRow('F',8,2);

    addHexaCellRow('G',7,3);

    addHexaCellRow('H',6,4);

    addHexaCellRow('I',5,5);

    current=std::make_pair(-173.205+(2*w),0);
    current=std::make_pair (current.first-w,current.second+((3./2)*rad));

    next=std::make_pair(0,0);

    addHexaCellRow2('D',8,1);
    addHexaCellRow2('C',7,1);

    addHexaCellRow2('B',6,1);
    addHexaCellRow2('A',5,1);
}

void widget::update(const nvs::Subject *subject)
{
    if (subject != subject_) return;
    displayBoard(subject_);

    if (subject_->isOver()) {
      if (subject_->current()->getColor()==Color::BLACK) {
           winner->setHtml("<h1>The Winner is BLACK.Congratulations.<br></h1>");
        }else if(subject_->current()->getColor()==Color::WHITE){
           winner->setHtml("<h1>The Winner is WHITE.Congratulations.<br></h1>");
        }
        this->setDisabled(true);
    }
}

