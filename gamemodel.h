#ifndef GAMEMODEL_H
#define GAMEMODEL_H

namespace  Game{

enum Game_Mode{
    PVE,
    PVP
};

enum Game_Status {
    PLAYING,       //正在游玩
    WIN,           //获胜
    DEAD           //输
};

enum Game_Player {
    BPlayer = -1,       //黑棋手
    WPlayer = 1         //白棋手
};

enum Role{
    EMPTY,  //空白
    BLACK,  //黑色
    WRITE   //白色
};

const int BOARD_LEN = 15;

class GameModel
{
public:
    GameModel(Game_Mode mode = PVP, Game_Player player = BPlayer);
    ~GameModel();
    void gamerPlay(int x, int y);   //玩家下棋
    void AIPlay();  //AI下棋
    void checkWin(int x, int y);       //检查是否胜利
    //
    Game_Player player() const {return _player;}
    Game_Player gamer() const {return _gamer;}
    Game_Status status() const {return _status;}
    Game_Mode   mode()   const {return _mode;}
    int getRole(int x, int y) const {return board[y][x];}  //获得map的key

private:
    char board[BOARD_LEN][BOARD_LEN];  //界面
    int _scoreAera[BOARD_LEN][BOARD_LEN]; //评分数组
    Game_Mode _mode;                      //模式4
    Game_Player _player, _gamer;          //正在下棋的一方 以及 玩家的颜色
    Game_Status _status;                  //游戏状态
    //PVE PVP不需要
    Role aiValue;                    //ai 的颜色
    Role gamerValue;                 //玩家颜色

    void _calculateScore();                //对局势进行评分
    int _assessScore(int gamerNum, int aiNum); //得分
    void _updateMap(int x, int y);          //更新界面
};

} //namespace

#endif // GAMEMODEL_H
