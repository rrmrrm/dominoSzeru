#include "model.h"
#include <iostream>
#include <QTcpServer>
#include <string>
#include <QVector>
#include "common.h"

model::model()
{
}


void model::setPlayernum(int number)
{
    playernum=number;
}

void model::startGame()
{
    //delete  deck;
    firstTurn=true;
    deck= new Deck(playernum);
    currentnumber=0;
    players.clear();
    sorrend.resize(playernum);
    players.resize(playernum);
    for(int i = 0; i < playernum;i++)
    {
        emit updateActivePlayer(i);
        AddDominoConfirm(players[i].getFields());
        sorrend[i]=i;
    }
    for(int i = 0; i < 50; i++)
    {
        int a=rand()%playernum;
        int b=rand()%playernum;
        int temp;
        temp=sorrend[a];
        sorrend[a]=sorrend[b];
        sorrend [b]=temp;
    }
    //for(int i = 0; i < playernum; i++)
    //{
        currentplayer=&players[sorrend[0]];
        //AddDominoConfirm();
        emit updateActivePlayer(sorrend[0]);
        currentnumber=0;
    //}
    deck->draw();
    emit newDominos(deck->getNewOnes());
    emit updateDeckSize(max(0,deck->cardsLeftNum()));
    emit updateTurnsleft(1+deck->cardsLeftNum()/playernum);
}
bool lerakahto(Domino domi, DIR dominoDir, Player* player, int x, int y, Deck* deck)
{
        bool szabalyos;
        int x2=x;
        int y2=y;
        if(dominoDir==UP)
        {
            x2--;
        }
        if(dominoDir==DOWN)
        {
            x2++;
        }
        if(dominoDir==LEFT)
        {
            y2--;
        }
        if(dominoDir==RIGHT)
        {
            y2++;
        }

        if(x>=0 && x <=4 && y>=0 && y <=4 && x2>=0 && x2 <=4 && y2>=0 && y2 <=4)
        {
        bool bal=false;
        bool jobb=false;
        bool fent=false;
        bool lent=false;
        if(x==0)
        {
            fent=true;
        }
        if(x==4)
        {
            lent=true;
        }
        if(y==0)
        {
            bal=true;
        }
        if(y==4)
        {
            jobb=true;
        }
        if(!bal && (player->getFields()[x][y-1]==deck->getCurrent().at(player->getKingPlace()).GetColors().first || player->getFields()[x][y-1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!jobb && (player->getFields()[x][y+1]==deck->getCurrent().at(player->getKingPlace()).GetColors().first || player->getFields()[x][y+1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!fent && (player->getFields()[x-1][y]==deck->getCurrent().at(player->getKingPlace()).GetColors().first || player->getFields()[x-1][y]==CASTLE))
        {
            szabalyos=true;
        }
        if(!lent && (player->getFields()[x+1][y]==deck->getCurrent().at(player->getKingPlace()).GetColors().first || player->getFields()[x+1][y]==CASTLE))
        {
            szabalyos=true;
        }
        if(x2==0)
        {
            fent=true;
        }
        if(x2==4)
        {
            lent=true;
        }
        if(y2==0)
        {
            bal=true;
        }
        if(y2==4)
        {
            jobb=true;
        }
        if(!bal && (player->getFields()[x2][y2-1]==deck->getCurrent().at(player->getKingPlace()).GetColors().second || player->getFields()[x2][y2-1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!jobb && (player->getFields()[x2][y2+1]==deck->getCurrent().at(player->getKingPlace()).GetColors().second || player->getFields()[x2][y2+1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!fent && (player->getFields()[x2-1][y2]==deck->getCurrent().at(player->getKingPlace()).GetColors().second || player->getFields()[x2-1][y2]==CASTLE))
        {
            szabalyos=true;
        }
        if(!lent && (player->getFields()[x2+1][y2]==deck->getCurrent().at(player->getKingPlace()).GetColors().second || player->getFields()[x2+1][y2]==CASTLE))
        {
            szabalyos=true;
        }
        if(player->getFields()[x2][y2]!=EMPTY || player->getFields()[x2][y2]!=EMPTY)
        {
            szabalyos=false;
        }
}
return szabalyos;
}
void model::PutKingAttempt(bool firstDominoRow, int place)
{
    if(!(deck->taken[place]))
    {
        currentplayer->placeKing(place);
        deck->taken[place]=true;
        PutKingConfirm(firstDominoRow, place, sorrend[currentnumber]);
        if(currentnumber==(playernum-1))
        {
            if(firstTurn)
            {
                firstTurn=false;
                emit notTheFirstTurn();
            }
            deck->draw();
            emit newDominos(deck->getNewOnes());
            currentnumber=-1;
            for(int i = 0; i < playernum; i++)
            {
                for(int j = 0; j < playernum; j++)
                {
                    if(players[j].getKingPlace()==i)
                    {
                        sorrend[i]=j;
                    }
                }
            }
        }
        currentnumber++;

        if(!firstTurn){
                 bool lephet=false;
                 for(int i = 0; i < 5; i++)
                 {
                     for(int j = 0; j < 5; j++)
                     {
                         lephet=(lephet ||lerakahto(deck->getCurrent().at(sorrend[currentnumber]),UP, currentplayer, i, j, deck));
                         lephet=(lephet ||lerakahto(deck->getCurrent().at(sorrend[currentnumber]),DOWN, currentplayer, i, j, deck));
                         lephet=(lephet ||lerakahto(deck->getCurrent().at(sorrend[currentnumber]),LEFT, currentplayer, i, j, deck));
                         lephet=(lephet ||lerakahto(deck->getCurrent().at(sorrend[currentnumber]),RIGHT, currentplayer, i, j, deck));

                     }
                 }
                 if(!lephet)
                 {
                     AddDominoConfirm(currentplayer->getFields());
                     if(deck->cardsLeftNum()==0)
                     {
                         PutKingConfirm(true,-1, sorrend[currentnumber]);
                     }
                 }


             }

        currentplayer=&players[sorrend[currentnumber]];
        std::cout << "JELENLEGI JATEKOS: " << sorrend[currentnumber] << std::endl;
    }
    emit updateActivePlayer(sorrend[currentnumber]);
    emit updateDeckSize(max(0,deck->cardsLeftNum()));
    emit updateTurnsleft(1+deck->cardsLeftNum()/playernum);
    if(!firstTurn)
    emit showChosenDomino(deck->Current().at(currentplayer->getKingPlace()));
}



void model::AddDominoAttempt(int x, int y)
{
    bool szabalyos=false;
    DIR dominoDir = deck->getCurrent().at(currentplayer->getKingPlace()).GetDirection();
    int x2=x;
    int y2=y;
    if(dominoDir==UP)
    {
        x2--;
    }
    if(dominoDir==DOWN)
    {
        x2++;
    }
    if(dominoDir==LEFT)
    {
        y2--;
    }
    if(dominoDir==RIGHT)
    {
        y2++;
    }

    std::cout << x << " " << y << " " << x2 << " " << y2 << std::endl;
    if(x>=0 && x <=4 && y>=0 && y <=4 && x2>=0 && x2 <=4 && y2>=0 && y2 <=4)
    {

        bool bal=false;
        bool jobb=false;
        bool fent=false;
        bool lent=false;
        if(x==0)
        {
            fent=true;
        }
        if(x==4)
        {
            lent=true;
        }
        if(y==0)
        {
            bal=true;
        }
        if(y==4)
        {
            jobb=true;
        }
        if(!bal && (currentplayer->getFields()[x][y-1]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().first || currentplayer->getFields()[x][y-1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!jobb && (currentplayer->getFields()[x][y+1]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().first || currentplayer->getFields()[x][y+1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!fent && (currentplayer->getFields()[x-1][y]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().first || currentplayer->getFields()[x-1][y]==CASTLE))
        {
            szabalyos=true;
        }
        if(!lent && (currentplayer->getFields()[x+1][y]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().first || currentplayer->getFields()[x+1][y]==CASTLE))
        {
            szabalyos=true;
        }
        if(x2==0)
        {
            fent=true;
        }
        if(x2==4)
        {
            lent=true;
        }
        if(y2==0)
        {
            bal=true;
        }
        if(y2==4)
        {
            jobb=true;
        }
        if(!bal && (currentplayer->getFields()[x2][y2-1]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().second || currentplayer->getFields()[x2][y2-1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!jobb && (currentplayer->getFields()[x2][y2+1]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().second || currentplayer->getFields()[x2][y2+1]==CASTLE))
        {
            szabalyos=true;
        }
        if(!fent && (currentplayer->getFields()[x2-1][y2]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().second || currentplayer->getFields()[x2-1][y2]==CASTLE))
        {
            szabalyos=true;
        }
        if(!lent && (currentplayer->getFields()[x2+1][y2]==deck->getCurrent().at(currentplayer->getKingPlace()).GetColors().second || currentplayer->getFields()[x2+1][y2]==CASTLE))
        {
            szabalyos=true;
        }
        if(currentplayer->getFields()[x2][y2]!=EMPTY || currentplayer->getFields()[x2][y2]!=EMPTY)
        {
            szabalyos=false;
        }
    }

    if(szabalyos)
    {
        currentplayer->placeDomino(deck, x, y);
        AddDominoConfirm(currentplayer->getFields());
        if(deck->cardsLeftNum()==0)
        {
            PutKingConfirm(true,-1, sorrend[currentnumber]);
        }
    }



    if(deck->cardsLeftNum()==-1*playernum)
    {
        if(currentnumber==(playernum-1))
        {
            int maxpont=-1;
            vector<int> nyertesek;
            for(int i = 0; i < playernum; i++)
            {
                if(players[i].getPoint().first>maxpont)
                {
                    nyertesek.clear();
                    nyertesek.resize(1);
                    nyertesek.push_back(i);
                }
                if(players[i].getPoint().first==maxpont)
                {
                    nyertesek.push_back(i);
                }
            }
            emit gameOver(nyertesek);
            startGame();
        }
        else
        {

            emit
        updateActivePlayer(sorrend[++currentnumber]);
        }
    }
}

void model::rotateDominoAttempt(int player, DIR newDir){
    if( player == sorrend[currentnumber]){
        ///elforgatom a jatekos dominojat newDire fele
        deck->Current().at(currentplayer->getKingPlace()).Rotate(newDir);
        ///jelzem a nezetnek, hogy elforgattuk a dominot a modellben
        rotateDominoConfirm(player, newDir);
        showChosenDomino( deck->Current().at(currentplayer->getKingPlace()) );
    }
}

void model::playerNumChanged()
{
    if(playernum==3)
    {
        playernum=4;
    }
    else
        playernum=3;
    startGame();
    sendPlayerNum(playernum);
}


void model::startServer()
{
    isServer=true;
    server =  new QTcpServer(this);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any, 1234))
    {
        std::cout << "rossz" << std::endl;
    }
    else
    {
        std::cout << "jo" << std::endl;
    }
}

void model::connect()
{
    isClient=true;
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost", 1234);
    socket->write("helloServer");
    std::cout << "done" << endl;
}

void model::newConnnection()
{
    cout << "Van kapcsolat" << endl;
    QTcpSocket *socket =server->nextPendingConnection();
    sockets.push_back(socket);
    clientnum++;
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket));
    QObject::connect(this, SIGNAL(wantToSend(QString)), this, SLOT(wantToRead(QString)));
    socket->write("0\n");
    QString asd = "LOL";

    char buf[16]; // need a buffer for that
    int i = playernum;
    sprintf(buf,"%d",i);
    buf[1]='/';
    buf[2]='n';
    const char* p = buf;
    socket->write(p);
    for(int j = 0; j < playernum; j++)
    {
        int i = sorrend[i];
        sprintf(buf,"%d",i);
        buf[1]='/';
        buf[2]='n';
        const char* p = buf;
        socket->write(p);
    }
}

void model::readSocket()
{
    if(isClient)
    {
        while(socket->canReadLine())
        {
            QString line = QString::fromUtf8(socket->readLine());
            if(line=="0")
            {
                playernum=QString::fromUtf8(socket->readLine()).split(" ")[0].toInt();
                deck->dominoes.resize(12*playernum);
                for(int i = 0; i < playernum; i++)
                {
                    sorrend[i]=QString::fromUtf8(socket->readLine()).split(" ")[0].toInt();
                }
                for(int i = 0; i < 12* playernum; i++)
                {
                    deck->dominoes[i]=Domino( COLOR(QString::fromUtf8(socket->readLine()).split(" ")[0].toInt()), COLOR(QString::fromUtf8(socket->readLine()).split(" ")[0].toInt()), 0,0,RIGHT );
                }
            }
            if(line=="2")
            {
                PutKingConfirm(QString::fromUtf8(socket->readLine()).split(" ")[0].toInt(),QString::fromUtf8(socket->readLine()).split(" ")[0].toInt(),QString::fromUtf8(socket->readLine()).split(" ")[0].toInt());

            }
            if(line=="3")
            {
                QVector<QVector<COLOR>> szinek;
                szinek.resize(5);
                for(int i = 0; i < 5; i++)
                {
                    szinek[i].resize(5);
                    for(int j = 0; j < 5; j++)
                    {
                        szinek[i][j]=COLOR(QString::fromUtf8(socket->readLine()).split(" ")[0].toInt());
                    }
                }
                AddDominoConfirm(szinek);
            }
        }
        cout << "done reading " << endl;
    }
}

void model::wantToRead(QString arg)
{
    if(arg[0]=="0")
    {
        rotateDominoAttempt(sorrend[currentnumber], DIR(arg[1].digitValue()));
        AddDominoAttempt(arg[2].digitValue(),arg[3].digitValue());
    }
    if(arg[0]=="1")
    {
        PutKingConfirm(arg[1].digitValue(),arg[2].digitValue(),arg[3].digitValue());
    }
}

