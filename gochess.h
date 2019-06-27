#ifndef GOCHESS_H
#define GOCHESS_H

#include <QPainter>
#include <QPoint>
#include <QVector>

class GoChess{
public:
    explicit GoChess();

    ~GoChess();

    bool getTurn();

    int getShouShu();

    bool getStart();

    int getBaiTiZi();

    int getHeiTiZi();

    void LuoZi(int x, int y);

    void HuiQi();

    void DuiYi();

    void TouZi();

private:
    bool TiZi(int x, int y);

    bool SuanQi(int x, int y, bool **status);

public:
    char **board;  // black:1 white:0 blanck:-1

private:
    bool start;
    bool turn;  // black:1 white:0
    QPoint tracker[362];
    QVector<QPoint> tiziTracker[362];
    int shoushu;
    int baiTiZi, heiTiZi;
};

#endif // GOCHESS_H
