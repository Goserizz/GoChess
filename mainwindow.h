#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gochess.h"

#define CORDX(i)        (aleft + i * a_side)
#define CORDY(i)        (atop + i * a_side)
#define CHSIZE          side * 9 / 360
#define CHPOINT(x, y)   QPointF(CORDX(x), CORDY(y))
#define PTSIZE          side / 120
#define FCPOINT(x, y)   QPointF(CORDX(x) + a_side / 6, CORDY(y) + a_side / 6)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void drawChess(QPainter *, int x, int y, bool turn, bool preview);
    void drawBoard(QPainter *);
    void setTexts();

private slots:
    void on_duiyiButton_clicked();

    void on_touziButton_clicked();

    void on_huiqiButton_clicked();

private:
    GoChess *goChess;
    Ui::MainWindow *ui;
    qreal side, a_side;
    qreal aleft, atop;
    int cursorx, cursory;
};

#endif // MAINWINDOW_H
