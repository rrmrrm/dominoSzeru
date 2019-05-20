#ifndef WIDGET_H
#define WIDGET_H

#ifdef TEST
    class Tester;
#endif

#include <vector>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QVector>
#include <QMessageBox>

#include "color.h"
#include "tablewidget.h"
#include "playerwidget.h"

#include "model.h"
#include "dominobutton.h"
namespace Ui {
class Widget;
}

using namespace std;
class Widget : public QWidget, ColorConverter{
    Q_OBJECT

    friend class Tester;

    Ui::Widget *ui;
    model* m;
    vector<DominoButton*> dominoRow1;
    vector<DominoButton*> dominoRow2;
    bool isFirstTurn;
    int dominoSideSize;
    QMessageBox qmb;

    void addSecondDominoRow();
    void removeSecondDominoRow();
public:
    void clear();
    int playerNum ;
    int activePlayer;
    vector<PlayerWidget*> players;

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void initialize(int playerNum);
    void notTheFirstTurn();

    void dominoRow1Clicked();
    void dominoRow2Clicked();
    void activePlayerUpdated(int);
    void showNewDominos(vector<Domino> v);
    void putKingConfirmed(bool firstDominoRow,int pos, int player);
    void rotateDominoConfirmed(int player, DIR newDir);

    ///show domino placed,and
    ///show next player's domino over his/her table's center
    void addDominoConfirmed(QVector< QVector<COLOR> > newDominos);


    ///winners contains the winners' indexes in the players array
    void show_winner( vector<int> winners);

    void playerDominoClicked();

    //kirajzolja az aktiv jatekos forgathato/lehelyezhető dominóját
    void showChosenDomino(Domino d);

    void ConnectButtonClicked();
    void startServerButtonClicked();
    void setPlayerNumButtonClicked();

    void ConnectConfirmed();
    void startServerConfirmed();
    void setPlayerNumChangeConfirmed();
    void updatePlayerNum(int);

    void muteOthers(int unMuted);
    void muteAllPlayers();

    ///a megadott jatekosWidgetet kiszinezi, hogy a jatekos tudja, hogy melyik az o tablaja
    void indicatePlayer(int player);
    void yourTurn();
    //---------------------------------------------------------
signals:
    void PutKingAttempt();

    void AddDominoAttempt();



};

#endif // WIDGET_H
