#ifndef WIDGET_H
#define WIDGET_H

#include "ghexacell.h"
#include <QGraphicsView>
#include <QWidget>
#include <game.h>
#include <observer/observer.h>

class QPushButton;
class QTextEdit ;
class widget : public QWidget,public nvs::Observer
{
    Q_OBJECT
public:
    explicit widget(Game * subject,QWidget *parent = nullptr);
    void displayBoard(Game* subject_);

private:
    Game * subject_;
    QTextEdit  * winner;
    void addHexaCellRow(char lettre,int number,int lower);
    void addHexaCellRow2(char lettre,int number,int lower);
    void makeSelectable(QColor color);

  private slots:
   void on_ghexacell_clicked(std::string value, QColor color);
    void on_play_Clicked();
    void on_change_player(Color);



   private:
    QPushButton * playButton;
    QGraphicsScene * scene;
    QGraphicsView * view;
    std::vector<GHexaCell *> _gHexaCells;
    std::vector<std::string>selectedCells;
    std::pair<double,double> current;
    std::pair<double,double> next;
    void populateScene();
protected:
signals:
void changePlayer(Color);


public:
    void update(const nvs::Subject *subject) override;
};

#endif // WIDGET_H
