#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent=nullptr);

    private slots:

        // This function gets called when a user clicks on the
        // loginButton on the front page.
        void on_loginButton_clicked();

        // This gets called when you click the sayButton on
        // the chat page.
        void on_sayButton_clicked();

        // This is a function we'll connect to a socket's readyRead()
        // signal, which tells us there's text to be read from the chat server.
        void readyRead();

        // This function gets called when the socket tells us it's connected.
        void connected();

    private:

        // This is the socket that will let us communitate with the server.
        QTcpSocket *socket;
};

#endif // MAINWINDOW_H
