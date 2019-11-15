//   Copyright © 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com | GPL v3.0   //


#include <QtGui>
#include <QWidget>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int N = 20, M = 20;
int apple[2];
int snake[300][3] = { 0 };
int snake_len;
bool pause = false;
bool ended = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fon = new QWidget(this);
    fon->setGeometry(0,0,600,600);
    fon->setStyleSheet("background-image: url("Figures/bg.png);");

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
          elem[i][j] = new QWidget(this);
          elem[i][j]->setGeometry(j*30,i*30,30,30);
          elem[i][j]->setStyleSheet("background-color:lightgray;");
        }
    }

    tmr = new QTimer;
    connect(tmr, SIGNAL(timeout()), this, SLOT(Step()));
    tmr->start();

    MainWindow::End();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_8 || event->key() == Qt::Key_W) {MainWindow::Up();}
    else if(event->key() == Qt::Key_2 || event->key() == Qt::Key_S) {MainWindow::Down();}
    else if(event->key() == Qt::Key_6 || event->key() == Qt::Key_D) {MainWindow::Right();}
    else if(event->key() == Qt::Key_4 || event->key() == Qt::Key_A) {MainWindow::Left();}
    else if(event->key() == Qt::Key_P) {MainWindow::Pause();}
    QMainWindow::keyPressEvent(event);
}

void MainWindow::Step() {
    if(!pause) {
        if(snake[0][0] == apple[0] && snake[0][1] == apple[1]) { MainWindow::Plus(); }

        for(int i = snake_len-1; i > 0; i--) {
            snake[i][0] = snake[i-1][0];
            snake[i][1] = snake[i-1][1];
            snake[i][2] = snake[i-1][2];
        }

        if(snake[0][2] == 0) {
            if(snake[0][0] + 1 >= N) snake[0][0] = 0;
            else snake[0][0] += 1;
        }
        else if(snake[0][2] == 1) {
            if(snake[0][1] - 1 < 0) snake[0][1] = M - 1;
            else snake[0][1] -= 1;
        }
        else if(snake[0][2] == 2) {
            if(snake[0][0] - 1 < 0) snake[0][0] = N - 1;
            else snake[0][0] -= 1;
        }
        else if(snake[0][2] == 3) {

            if(snake[0][1] + 1 >= M) snake[0][1] = 0;
            else snake[0][1] += 1;
        }

        for (int j = 1; j < snake_len; j++)
            if (snake[0][0] == snake[j][0] && snake[0][1] == snake[j][1]) {
                MainWindow::End();
                break;
            }
        MainWindow::Update();
    }
}

void MainWindow::Update() {
    if(ended) {
        ended = false;
        tmr->setInterval(250);
        fon->setStyleSheet("background-image: url("Figures/go.png);");
    }
    else {
        fon->setStyleSheet("background-image: url("Figures/bg1.png);");
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
              elem[i][j]->setStyleSheet("background-color:#00000000;");
            }
        }
        elem[apple[0]][apple[1]]->setStyleSheet("background-image: url(Figures/apple.png);");
        for(int i = 0; i < snake_len; i++) {
            if (i == 0) {
                if (!(snake[0][0] == apple[0] && snake[0][1] == apple[1])) {
                    if (snake[0][2] == 0) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/00.png);");
                    else if (snake[0][2] == 1) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/01.png);");
                    else if (snake[0][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/02.png);");
                    else if (snake[0][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/03.png);");
               }
                else {
                    if (snake[0][2] == 0) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/u0.png);");
                    else if (snake[0][2] == 1) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/u1.png);");
                    else if (snake[0][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/u2.png);");
                    else if (snake[0][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/u3.png);");
                }

            }
            else if(i+1 <= snake_len-1) {

                if (snake[i][2] == snake[i+1][2]) {
                    if (snake[i][2] == 0 || snake[i][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/20.png);");
                    else if (snake[i][2] == 1 || snake[i][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/13.png);");
                }
                else if (snake[i][2] != snake[i+1][2]) {
                    if (snake[i][2] == 0 && snake[i+1][2] == 1) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/1--0.png);");
                    else if (snake[i][2] == 0 && snake[i+1][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/3--0.png);");
                    else if (snake[i][2] == 1 && snake[i+1][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/2--1.png);");
                    else if (snake[i][2] == 1 && snake[i+1][2] == 0) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/0--1.png);");
                    else if (snake[i][2] == 2 && snake[i+1][2] == 1) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/1--2.png);");
                    else if (snake[i][2] == 2 && snake[i+1][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/3--2.png);");
                    else if (snake[i][2] == 3 && snake[i+1][2] == 0) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/0--3.png);");
                    else if (snake[i][2] == 3 && snake[i+1][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/2--3.png);");
                }
            }
             if(i == snake_len-1) {
                if (snake[i][2] == 0) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/p0.png);");
                else if (snake[i][2] == 1) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/p1.png);");
                else if (snake[i][2] == 2) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/p2.png);");
                else if (snake[i][2] == 3) elem[snake[i][0]][snake[i][1]]->setStyleSheet("background-image: url(Figures/p3.png);");
            }
        }
    }
}

void MainWindow::CreateApple() {
    while(true) {
        apple[0] = rand()%N;
        apple[1] = rand()%M;
        bool flag = true;
        for(int i = 0; i < snake_len; i++)
            if(snake[i][0] == apple[0] && snake[i][1] == apple[1]) flag = false;
        if(flag) break;
    }
}

void MainWindow::Pause() {
    pause = !pause;
}

void MainWindow::Plus() {
    MainWindow::CreateApple();
    snake_len++;
    if (snake_len >= 5 && snake_len < 10) tmr->setInterval(250);
    else if (snake_len >= 10 && snake_len < 15) tmr->setInterval(200);
    else if (snake_len >= 15 && snake_len < 20) tmr->setInterval(150);
    else if (snake_len >= 20 && snake_len < 25) tmr->setInterval(100);
    else if (snake_len >= 25) tmr->setInterval(75);
}

void MainWindow::End() {
    ended = true;
    tmr->setInterval(750);
    snake_len = 3;
    snake[0][2] = 0;
    snake[0][0] = 5;
    snake[0][1] = 7;
    MainWindow::CreateApple();
}

void MainWindow::Up() {
    if(snake[0][2] != 0) snake[0][2] = 2;
    if(pause) pause = !pause;
}

void MainWindow::Down() {
    if(snake[0][2] != 2) snake[0][2] = 0;
    if(pause) pause = !pause;
}

void MainWindow::Left() {
    if(snake[0][2] != 3) snake[0][2] = 1;
    if(pause) pause = !pause;
}

void MainWindow::Right() {
    if(snake[0][2] != 1) snake[0][2] = 3;
    if(pause) pause = !pause;
}
