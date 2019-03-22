#include "gamemodel.h"

#include <cstring>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <utility>
//#include <QDebug>

using namespace Game;

GameModel::GameModel(Game_Mode mode, Game_Player player) : _mode(mode), _gamer(player)
{
    memset(board, EMPTY, sizeof(board));  //置0
    _player = _gamer;
    //初始化为ai所使用
    if(mode == PVE)
    {
        if(_gamer == WPlayer)
        {
            aiValue = BLACK;
            gamerValue = WRITE;
        }
        else
        {
            aiValue = WRITE;
            gamerValue = BLACK;
        }
    }
    //随机化种子
    srand((unsigned int)time(nullptr));
    _status = PLAYING;
}

GameModel::~GameModel()
{

}

void GameModel::gamerPlay(int x, int y)
{
    _updateMap(x, y);
    //检查输赢
    checkWin(x, y);
    if(_status == WIN)  return;
    //互换
    _player = (Game_Player)-_player;
}

void GameModel::checkWin(int x, int y)
{
    int i, j, k, dx, dy, count, flag;
    flag = board[y][x];  //获得方块属性

    for(k = 1; k <= 4; k++)
    {
        switch(k)
        {
        case 1: dx = 1;  dy = 0; break;//横向
        case 2: dx = 0;  dy = 1; break;//纵向
        case 3: dx = 1;  dy = 1; break;//右下斜
        case 4: dx = -1; dy = 1; break;//左下斜
        }
        count = 0;
        for(i = y - 4 * dy, j = x - 4 * dx;
            i <= y + 4 * dy && (dx == -1 ? j >= x - 4 : j <= x + 4 * dx);
            i += dy, j += dx)
        {
            if(i < 0 || i >= BOARD_LEN || j < 0 || j >= BOARD_LEN)
                continue;
            if(board[i][j] == flag)
            {
                count++;
                if(count == 5)
                {
                    _status = WIN;
                    goto End;
                }
            }
            else {
                count = 0;
            }
        }
    }
End:
    return;
}

void GameModel::AIPlay()  //AI下棋
{
    _calculateScore();
    //找出最大的分数
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints; //最大的分数创建数组

    for(int y = 0; y < BOARD_LEN; y++)
    {
        for(int x = 0; x < BOARD_LEN; x++)
        {
            if(_scoreAera[y][x] > maxScore)
            {
                maxPoints.clear();
                maxScore = _scoreAera[y][x];
                maxPoints.push_back(std::make_pair(x, y));
            }
            else if(_scoreAera[y][x] == maxScore)
            {
                maxPoints.push_back(std::make_pair(x, y));
            }
        }
    }
    //随机选择一个点下棋
    std::size_t idx = (size_t)rand() % maxPoints.size();
    std::pair<int, int> point = maxPoints.at(idx);
    int x = point.first;
    int y = point.second;
    //qDebug() << x << y << idx << maxScore << maxPoints.size();
    //下棋
    _updateMap(x, y);
    //检查输赢
    checkWin(x, y);
    if(_status == WIN)  return;
    //互换
    _player = (Game_Player)-_player;
}

void GameModel::_calculateScore()        //对局势进行评分
{
    int gamerNum; //玩家个数
    int aiNum;    //ai个数

    memset(_scoreAera, 1, sizeof(_scoreAera));  //清空评分数组

    //遍历map
    int i, j, k, dx, dy, x, y;
    for(y = 0; y < BOARD_LEN; y++)
    {
        for(x = 0; x < BOARD_LEN; x++)
        {
            if(board[y][x] != EMPTY) //如果不是空白棋子就跳过
            {
                _scoreAera[y][x] = -1;
                continue;
            }

            //遍历该子的各个方向
            for(k = 1; k <= 4; k++)
            {
                switch(k)
                {
                case 1: dx = 1;  dy = 0; break;//横向
                case 2: dx = 0;  dy = 1; break;//纵向
                case 3: dx = 1;  dy = 1; break;//右下斜
                case 4: dx = -1; dy = 1; break;//左下斜
                }
                //玩家棋子遍历
                for(int m = 0; m < 5; m++)
                {
                    //初始化
                    gamerNum = 0;
                    aiNum = 0;
                    for(i = y - (4 - m) * dy, j = x - (4 - m) * dx;
                        i <= y + m * dy && (dx == -1 ? j >= x - m : j <= x + m * dx);
                        i += dy, j += dx)
                    {
                        if(i < 0 || i >= BOARD_LEN || j < 0 || j >= BOARD_LEN)
                            continue;
                        //子统计
                        if(board[i][j] == gamerValue)  //玩家子
                        {
                            gamerNum++;
                        }
                        else if(board[i][j] == aiValue)  //ai子
                        {
                            aiNum++;
                        }
                    }
                    //评分
                    _scoreAera[y][x] += _assessScore(gamerNum, aiNum);
                }
            }
        }
    }
}

int GameModel::_assessScore(int gamerNum, int aiNum)
{
    if((gamerNum == 0 && aiNum == 0) || (gamerNum > 0 && aiNum > 0))
        return 0;
    int gamerScore[5] = {0, 50, 800, 2000, 11000};
    int AIScore[5] = {0, 100, 200, 1100, 10000};
    return gamerScore[gamerNum] + AIScore[aiNum];
}

void GameModel::_updateMap(int x, int y)
{
    //if(board[y][x] != EMPTY)  //判断占位
    //    return;
    if(_player == BPlayer)
        board[y][x] = BLACK;
    else
        board[y][x] = WRITE;
}
