#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gochess.h"
#include <math.h>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    goChess = new GoChess();
    setMouseTracking(true);
    ui->setupUi(this);
    ui->touziButton->setDisabled(true);
    cursorx = -1;
    cursory = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter *painter = new QPainter(this);
    QWidget *board = ui->board_widget;

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(board->width() < board->height()){
        aleft = board->x();
        atop = board->y() + (board->height() - board->width()) / 2;
        side = board->width();
    }
    else{
        aleft = board->x() + (board->width() - board->height()) / 2;
        atop = board->y();
        side = board->height();
    }
    a_side = side / 18;

    painter->setPen(QColor(0, 0, 0));

    for(int i = 0; i < 19; i ++){
        painter->drawLine(CHPOINT(0, i), CHPOINT(18, i));
        painter->drawLine(CHPOINT(i, 0), CHPOINT(i, 18));
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(0, 0, 0));
    painter->drawEllipse(CHPOINT(3, 3), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(3, 9), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(3, 15), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(9, 3), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(9, 9), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(9, 15), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(15, 3), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(15, 9), PTSIZE, PTSIZE);
    painter->drawEllipse(CHPOINT(15, 15), PTSIZE, PTSIZE);

    drawBoard(painter);

    if(cursorx < 19 && cursorx > -1 && cursory < 19 && cursory > -1){
        drawChess(painter, cursorx, cursory, goChess->getTurn(), true);
    }

    delete painter;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    cursorx = static_cast<int>(floor((event->x() - aleft + a_side / 2) / a_side));
    cursory = static_cast<int>(floor((event->y() - atop + a_side / 2) / a_side));
    repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(!goChess->getStart()){
        return;
    }

    int x = static_cast<int>(floor((event->x() - aleft + a_side / 2) / a_side));
    int y = static_cast<int>(floor((event->y() - atop + a_side / 2) / a_side));
    goChess->LuoZi(x, y);

    setTexts();
    repaint();
}

void MainWindow::drawChess(QPainter* painter, int x, int y, bool turn, bool preview){
    QRadialGradient radialGradient(CHPOINT(x, y), CHSIZE * 2.5, FCPOINT(x, y));

    if(preview){
        QPen *preview_pen = new QPen();
        preview_pen->setColor(turn ? Qt::black : Qt::white);
        preview_pen->setStyle(Qt::DashLine);
        painter->setPen(*preview_pen);
        painter->setBrush(Qt::NoBrush);
    }
    else{
        painter->setPen(Qt::NoPen);
        if(turn){
            radialGradient.setColorAt(0.4, Qt::black);
            radialGradient.setColorAt(0.3, QColor(20, 20, 20));
            radialGradient.setColorAt(0.2, QColor(40, 40, 40));
            radialGradient.setColorAt(0.1, QColor(60, 60, 60));
            radialGradient.setColorAt(0, QColor(80, 80, 80));
            painter->setBrush(radialGradient);
        }
        else{
            radialGradient.setColorAt(0, Qt::white);
            radialGradient.setColorAt(0.2, QColor(235, 235, 235));
            radialGradient.setColorAt(0.4, QColor(215, 215, 215));
            radialGradient.setColorAt(0.6, QColor(195, 195, 195));
            radialGradient.setColorAt(0.8, QColor(175, 175, 175));
            painter->setBrush(radialGradient);
        }
    }

    painter->drawEllipse(CHPOINT(x, y), CHSIZE, CHSIZE);
}

void MainWindow::drawBoard(QPainter *painter){
    char **board = goChess->board;

    for(int i = 0; i < 19; i ++){
        for(int j = 0; j < 19; j ++){
            if(board[i][j] == -1){
                continue;
            }

            drawChess(painter, i, j, board[i][j], false);
        }
    }
}

void MainWindow::setTexts(){
    ui->shoushuEdit->setText(QString::number(goChess->getShouShu()));
    ui->baiTiZiEdit->setText(QString::number(goChess->getBaiTiZi()));
    ui->heiTiZiEdit->setText(QString::number(goChess->getHeiTiZi()));
}

void MainWindow::on_duiyiButton_clicked()
{
    goChess->DuiYi();
    ui->duiyiButton->setDisabled(true);
    ui->touziButton->setDisabled(false);
    ui->huiqiButton->setDisabled(false);

    setTexts();
    repaint();
}

void MainWindow::on_touziButton_clicked()
{
    goChess->TouZi();
    ui->duiyiButton->setDisabled(false);
    ui->touziButton->setDisabled(true);
    ui->huiqiButton->setDisabled(true);
}

void MainWindow::on_huiqiButton_clicked()
{
    goChess->HuiQi();
    setTexts();
    repaint();
}
