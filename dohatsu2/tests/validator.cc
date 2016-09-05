#include "testlib.h"

using namespace std;

const int H_MIN =  1;
const int H_MAX = 16;
const int W_MIN =  1;
const int W_MAX = 16;

int H, W;
string F[H_MAX];

void input()
{
    H = inf.readInt(H_MIN, H_MAX, "H");
    inf.readSpace();
    W = inf.readInt(W_MIN, W_MAX, "W");
    inf.readEoln();
    for (int i = 0; i < H; i++) {
        F[i] = inf.readToken(format("[o.@]{%d, %d}", W_MIN, W_MAX), format("F[%d]", i+1)); 
        inf.readEoln();
    }
    inf.readEof();
}

void check()
{
    // Exist curling stone
    bool exist_curling_stone = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (F[i][j] == 'o') {
                exist_curling_stone = 1;
            }
        }
    }

    ensuref(exist_curling_stone, "Not exist curling stone.");
    
    
    // Exist goal (only one)
    int goal_cnt = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (F[i][j] == '@') {
                goal_cnt++;
            }
        }
    }

    ensuref(goal_cnt == 1, "Goal must be exist only one.");
}

int main()
{
    registerValidation();

    input();

    check();
    
    return 0;
}
