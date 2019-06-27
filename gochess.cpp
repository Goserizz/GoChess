#include "gochess.h"
#include "mainwindow.h"
#include <QPainter>

GoChess::GoChess(){
    start = false;
    turn = true;
    shoushu = 1;
    baiTiZi = heiTiZi = 0;

    board = new char*[19];
    for(int i = 0; i < 19; i ++){
        board[i] = new char[19];
    }

    for(int i = 0; i < 19; i ++){
        for(int j = 0; j < 19; j ++){
            board[i][j] = -1;
        }
    }
}

GoChess::~GoChess(){
    for(int i = 0; i < 19; i ++){
        delete [] board[i];
    }
    delete [] board;
}

bool GoChess::getTurn(){
    return turn;
}

int GoChess::getShouShu(){
    return shoushu - 1;
}

bool GoChess::getStart(){
    return start;
}

int GoChess::getBaiTiZi(){
    return baiTiZi;
}

int GoChess::getHeiTiZi(){
    return heiTiZi;
}

void GoChess::LuoZi(int x, int y){
    bool **status;
    status = new bool*[19];
    for(int i = 0; i < 19; i ++){
        status[i] = new bool[19];
        for(int j = 0; j < 19; j ++){
            status[i][j] = false;
        }
    }

    if(board[x][y] != -1)
        return;
    board[x][y] = turn;
    if(!SuanQi(x, y, status) && !TiZi(x, y)){
        board[x][y] = -1;
        return;
    }
    else {
        TiZi(x, y);
    }

    tracker[shoushu].setX(x);
    tracker[shoushu].setY(y);
    shoushu ++;
    turn = !turn;

    for(int i = 0; i < 19; i ++){
        delete [] status[i];
    }
    delete [] status;
}

bool GoChess::TiZi(int x, int y){
    bool **status;
    bool beiti;
    bool ret = false;
    int tmpx, tmpy;

    if(board[x][y] == 1){
        beiti = 0;
    }
    else{
        beiti = 1;
    }

    status = new bool*[19];
    for(int i = 0; i < 19; i ++){
        status[i] = new bool[19];
    }

    QPoint points[4] ={QPoint(x + 1, y), QPoint(x - 1, y), QPoint(x, y + 1), QPoint(x, y -1)};

    for(int i = 0; i < 4; i ++){
        tmpx = points[i].x();
        tmpy = points[i].y();

        for(int j = 0; j < 19; j ++){
            for(int k = 0; k < 19; k ++){
                status[j][k] = false;
            }
        }

        if(tmpx < 19 && tmpx > -1 && tmpy < 19 && tmpy > -1 &&
            board[tmpx][tmpy] == beiti && !SuanQi(tmpx, tmpy, status)){
            for(int j = 0; j < 19; j ++){
                for(int k = 0; k < 19; k ++){
                    if(status[j][k]){
                        board[j][k] = -1;

                        tiziTracker[shoushu].push_back(QPoint(j, k));
                        beiti ? baiTiZi ++ : heiTiZi ++;
                    }
                }
            }
            ret = true;
        }
    }

    for(int i = 0; i < 19; i ++){
        delete [] status[i];
    }
    delete [] status;

    return ret;
}

bool GoChess::SuanQi(int x, int y, bool **status){
    if(status[x][y])
        return false;
    status[x][y] = true;

    int tmpx, tmpy;

    QPoint points[4] ={QPoint(x + 1, y), QPoint(x - 1, y), QPoint(x, y + 1), QPoint(x, y -1)};

    for(int i = 0; i < 4; i ++){
        tmpx = points[i].x();
        tmpy = points[i].y();

        if(tmpx < 19 && tmpx > -1 && tmpy < 19 && tmpy > -1 &&
            (board[tmpx][tmpy] == -1 ||
                (board[tmpx][tmpy] == board[x][y] &&SuanQi(tmpx, tmpy, status)))){
            return true;
        }
    }

    return false;
}

void GoChess::HuiQi(){
    if(shoushu == 1)
        return;

    shoushu --;

    board[tracker[shoushu].x()][tracker[shoushu].y()] == 1 ?
                heiTiZi -= tiziTracker[shoushu].size():
                baiTiZi -= tiziTracker[shoushu].size();

    board[tracker[shoushu].x()][tracker[shoushu].y()] = -1;

    for(int i = 0; i < tiziTracker[shoushu].size(); i ++){
        board[tiziTracker[shoushu][i].x()][tiziTracker[shoushu][i].y()] = turn;
    }

    tiziTracker[shoushu].clear();

    turn = !turn;
}

void GoChess::DuiYi(){
    for(int i = 0; i < 19; i ++){
        for(int j = 0; j < 19; j ++){
            board[i][j] = -1;
        }
    }
    for(int i = 1; i <= shoushu; i ++){
        tiziTracker[i].clear();
    }

    shoushu = 1;
    turn = true;
    start = true;
}

void GoChess::TouZi(){
    start = false;
}
