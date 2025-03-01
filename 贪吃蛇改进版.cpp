#include <bits/stdc++.h>  // 包含几乎所有标准库头文件
#include <windows.h>      // 包含Windows特定函数库，用于清屏和延时
#include <conio.h>        // 包含控制台输入输出函数库，用于捕获键盘输入
#define H 22              // 定义棋盘的高度为22
#define W 22              // 定义棋盘的宽度为22
using namespace std;      // 使用标准命名空间

class chessboard       // 定义棋盘类
{
public:
    char qp[H][W];     // 定义棋盘的二维数组
    int i, j, x1, y1;  // 定义棋盘坐标和食物位置变量
    chessboard();      // 棋盘类的构造函数
    void food();       // 生成食物的函数
    void prt(int grade, int score, int gamespeed); // 打印棋盘的函数
};

chessboard::chessboard() // 构造函数的实现
{
    for (i = 1; i <= H - 2; i++) // 初始化棋盘内部为空格
        for (j = 1; j <= W - 2; j++)
            qp[i][j] = ' ';
    for (i = 0; i <= H - 1; i++) // 初始化棋盘的边界为'#'
        qp[0][i] = qp[H - 1][i] = '#';
    for (i = 1; i <= H - 2; i++)
        qp[i][0] = qp[i][W - 1] = '#';
    food(); // 生成一个初始食物
}

void chessboard::food() // 生成食物的函数实现
{
    srand(time(0)); // 使用当前时间作为随机数种子
    do
    {
        x1 = rand() % (W - 2) + 1; // 随机生成食物的x坐标
        y1 = rand() % (H - 2) + 1; // 随机生成食物的y坐标
    } while (qp[x1][y1] != ' '); // 确保食物不生成在非空格位置
    qp[x1][y1] = '$'; // 将食物位置标记为'$'
}

void chessboard::prt(int grade, int score, int gamespeed) // 打印棋盘的函数实现
{
    system("cls"); // 清屏
    cout << endl;
    for (i = 0; i < H; i++)
    {
        cout << "\t";
        for (j = 0; j < W; j++)
            cout << qp[i][j] << ' '; // 打印棋盘
        if (i == 0) cout << "\tGrade:" << grade; // 打印等级
        if (i == 2) cout << "\tScore:" << score; // 打印分数
        if (i == 4) cout << "\tAutomatic forward"; // 提示自动前进
        if (i == 5) cout << "\ttime interval:" << gamespeed << "ms"; // 打印时间间隔
        cout << endl;
    }
}

class snake : public chessboard // 定义蛇类，继承自棋盘类
{
public:
    int zb[2][100]; // 定义蛇的位置数组
    long start; // 定义开始时间
    int head, tail, grade, score, gamespeed, length, timeover, x, y; // 定义蛇的各种属性
    char direction; // 定义蛇的方向
    snake(); // 蛇类的构造函数
    void move(); // 蛇的移动函数
};

snake::snake() // 蛇类的构造函数实现
{
    cout << "\n\n\t\tThe game is about to begin!" << endl; // 提示游戏即将开始
    for (i = 3; i >= 0; i--)
    {
        start = clock(); // 获取当前时间
        while (clock() - start <= 1000); // 等待1秒
        system("cls"); // 清屏
        if (i > 0)
            cout << "\n\n\t\tCountdown:" << i << endl; // 打印倒计时
    }
    for (i = 1; i <= 3; i++)
        qp[1][i] = '*'; // 初始化蛇的身体
    qp[1][4] = '@'; // 初始化蛇的头部
    for (i = 0; i < 4; i++)
    {
        zb[0][i] = 1; // 初始化蛇的x坐标
        zb[1][i] = i + 1; // 初始化蛇的y坐标
    }
}

void snake::move() // 蛇的移动函数实现
{
    score = 0; // 初始化分数
    head = 3, tail = 0; // 初始化蛇头和蛇尾的位置
    grade = 1, length = 4; // 初始化等级和长度
    gamespeed = 500; // 初始化游戏速度
    direction = 77; // 初始化方向为右
    bool paused = false; // 初始化暂停状态
    while (1) // 无限循环，游戏主逻辑
    {
        timeover = 1; // 初始化时间标志
        start = clock(); // 获取当前时间
        while ((timeover = (clock() - start <= gamespeed)) && !kbhit()); // 等待游戏速度时间或有键盘输入
        if (timeover)
        {
            char ch = getch();
            if (ch == ' ') // 检测空格键
            {
                paused = !paused; // 切换暂停状态
                if (paused)
                {
                    cout << "\n\n\t\tPaused" << endl;
                    while (paused)
                    {
                        if (kbhit() && getch() == ' ')
                        {
                            paused = false; // 继续游戏
                            system("cls"); // 清屏
                        }
                    }
                }
            }
            else if (ch == 72 || ch == 80 || ch == 75 || ch == 77) // 检测方向键
            {
                direction = ch; // 获取方向键输入
            }
            else
            {
                continue; // 忽略其他按键
            }
        }
        switch (direction) // 根据方向更新蛇头的位置
        {
        case 72: x = zb[0][head] - 1; y = zb[1][head]; break; // 上
        case 80: x = zb[0][head] + 1; y = zb[1][head]; break; // 下
        case 75: x = zb[0][head]; y = zb[1][head] - 1; break; // 左
        case 77: x = zb[0][head]; y = zb[1][head] + 1; break; // 右
        }
        if (x == 0 || x == 21 || y == 0 || y == 21) // 撞墙检测
        {
            system("cls"); // 清屏
            cout << "\n\n\t\tGAME OVER" << endl; // 打印游戏结束
            cout << "\t\tScore: " << score << endl; // 打印分数
            Sleep(5000); // 等待5秒
            break; // 退出循环
        }
        if (qp[x][y] != ' ' && !(x == x1 && y == y1)) // 撞到自己检测
        {
            system("cls");
            cout << "\n\n\t\tGAME OVER" << endl;
            cout << "\t\tScore: " << score << endl;
            Sleep(5000);
            break;
        }
        if (x == x1 && y == y1) // 吃到食物
        {
            length++;
            score = score + 100;
            if (length >= 8)
            {
                length -= 8;
                grade++;
                if (gamespeed >= 200)
                    gamespeed = 550 - grade * 50;
            }
            qp[x][y] = '@';
            qp[zb[0][head]][zb[1][head]] = '*';
            head = (head + 1) % 100;
            zb[0][head] = x;
            zb[1][head] = y;
            food();
            prt(grade, score, gamespeed);
        }
        else
        {
            qp[zb[0][tail]][zb[1][tail]] = ' ';
            tail = (tail + 1) % 100;
            qp[zb[0][head]][zb[1][head]] = '*';
            head = (head + 1) % 100;
            zb[0][head] = x;
            zb[1][head] = y;
            qp[zb[0][head]][zb[1][head]] = '@';
            prt(grade, score, gamespeed);
        }
    }
}

int main() // 主函数
{
    chessboard cb; // 创建棋盘对象
    snake s; // 创建蛇对象
    s.move(); // 调用蛇的移动函数，开始游戏
}
