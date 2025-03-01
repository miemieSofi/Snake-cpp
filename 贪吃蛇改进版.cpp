#include <bits/stdc++.h>  // �����������б�׼��ͷ�ļ�
#include <windows.h>      // ����Windows�ض������⣬������������ʱ
#include <conio.h>        // ��������̨������������⣬���ڲ����������
#define H 22              // �������̵ĸ߶�Ϊ22
#define W 22              // �������̵Ŀ��Ϊ22
using namespace std;      // ʹ�ñ�׼�����ռ�

class chessboard       // ����������
{
public:
    char qp[H][W];     // �������̵Ķ�ά����
    int i, j, x1, y1;  // �������������ʳ��λ�ñ���
    chessboard();      // ������Ĺ��캯��
    void food();       // ����ʳ��ĺ���
    void prt(int grade, int score, int gamespeed); // ��ӡ���̵ĺ���
};

chessboard::chessboard() // ���캯����ʵ��
{
    for (i = 1; i <= H - 2; i++) // ��ʼ�������ڲ�Ϊ�ո�
        for (j = 1; j <= W - 2; j++)
            qp[i][j] = ' ';
    for (i = 0; i <= H - 1; i++) // ��ʼ�����̵ı߽�Ϊ'#'
        qp[0][i] = qp[H - 1][i] = '#';
    for (i = 1; i <= H - 2; i++)
        qp[i][0] = qp[i][W - 1] = '#';
    food(); // ����һ����ʼʳ��
}

void chessboard::food() // ����ʳ��ĺ���ʵ��
{
    srand(time(0)); // ʹ�õ�ǰʱ����Ϊ���������
    do
    {
        x1 = rand() % (W - 2) + 1; // �������ʳ���x����
        y1 = rand() % (H - 2) + 1; // �������ʳ���y����
    } while (qp[x1][y1] != ' '); // ȷ��ʳ�ﲻ�����ڷǿո�λ��
    qp[x1][y1] = '$'; // ��ʳ��λ�ñ��Ϊ'$'
}

void chessboard::prt(int grade, int score, int gamespeed) // ��ӡ���̵ĺ���ʵ��
{
    system("cls"); // ����
    cout << endl;
    for (i = 0; i < H; i++)
    {
        cout << "\t";
        for (j = 0; j < W; j++)
            cout << qp[i][j] << ' '; // ��ӡ����
        if (i == 0) cout << "\tGrade:" << grade; // ��ӡ�ȼ�
        if (i == 2) cout << "\tScore:" << score; // ��ӡ����
        if (i == 4) cout << "\tAutomatic forward"; // ��ʾ�Զ�ǰ��
        if (i == 5) cout << "\ttime interval:" << gamespeed << "ms"; // ��ӡʱ����
        cout << endl;
    }
}

class snake : public chessboard // �������࣬�̳���������
{
public:
    int zb[2][100]; // �����ߵ�λ������
    long start; // ���忪ʼʱ��
    int head, tail, grade, score, gamespeed, length, timeover, x, y; // �����ߵĸ�������
    char direction; // �����ߵķ���
    snake(); // ����Ĺ��캯��
    void move(); // �ߵ��ƶ�����
};

snake::snake() // ����Ĺ��캯��ʵ��
{
    cout << "\n\n\t\tThe game is about to begin!" << endl; // ��ʾ��Ϸ������ʼ
    for (i = 3; i >= 0; i--)
    {
        start = clock(); // ��ȡ��ǰʱ��
        while (clock() - start <= 1000); // �ȴ�1��
        system("cls"); // ����
        if (i > 0)
            cout << "\n\n\t\tCountdown:" << i << endl; // ��ӡ����ʱ
    }
    for (i = 1; i <= 3; i++)
        qp[1][i] = '*'; // ��ʼ���ߵ�����
    qp[1][4] = '@'; // ��ʼ���ߵ�ͷ��
    for (i = 0; i < 4; i++)
    {
        zb[0][i] = 1; // ��ʼ���ߵ�x����
        zb[1][i] = i + 1; // ��ʼ���ߵ�y����
    }
}

void snake::move() // �ߵ��ƶ�����ʵ��
{
    score = 0; // ��ʼ������
    head = 3, tail = 0; // ��ʼ����ͷ����β��λ��
    grade = 1, length = 4; // ��ʼ���ȼ��ͳ���
    gamespeed = 500; // ��ʼ����Ϸ�ٶ�
    direction = 77; // ��ʼ������Ϊ��
    bool paused = false; // ��ʼ����ͣ״̬
    while (1) // ����ѭ������Ϸ���߼�
    {
        timeover = 1; // ��ʼ��ʱ���־
        start = clock(); // ��ȡ��ǰʱ��
        while ((timeover = (clock() - start <= gamespeed)) && !kbhit()); // �ȴ���Ϸ�ٶ�ʱ����м�������
        if (timeover)
        {
            char ch = getch();
            if (ch == ' ') // ���ո��
            {
                paused = !paused; // �л���ͣ״̬
                if (paused)
                {
                    cout << "\n\n\t\tPaused" << endl;
                    while (paused)
                    {
                        if (kbhit() && getch() == ' ')
                        {
                            paused = false; // ������Ϸ
                            system("cls"); // ����
                        }
                    }
                }
            }
            else if (ch == 72 || ch == 80 || ch == 75 || ch == 77) // ��ⷽ���
            {
                direction = ch; // ��ȡ���������
            }
            else
            {
                continue; // ������������
            }
        }
        switch (direction) // ���ݷ��������ͷ��λ��
        {
        case 72: x = zb[0][head] - 1; y = zb[1][head]; break; // ��
        case 80: x = zb[0][head] + 1; y = zb[1][head]; break; // ��
        case 75: x = zb[0][head]; y = zb[1][head] - 1; break; // ��
        case 77: x = zb[0][head]; y = zb[1][head] + 1; break; // ��
        }
        if (x == 0 || x == 21 || y == 0 || y == 21) // ײǽ���
        {
            system("cls"); // ����
            cout << "\n\n\t\tGAME OVER" << endl; // ��ӡ��Ϸ����
            cout << "\t\tScore: " << score << endl; // ��ӡ����
            Sleep(5000); // �ȴ�5��
            break; // �˳�ѭ��
        }
        if (qp[x][y] != ' ' && !(x == x1 && y == y1)) // ײ���Լ����
        {
            system("cls");
            cout << "\n\n\t\tGAME OVER" << endl;
            cout << "\t\tScore: " << score << endl;
            Sleep(5000);
            break;
        }
        if (x == x1 && y == y1) // �Ե�ʳ��
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

int main() // ������
{
    chessboard cb; // �������̶���
    snake s; // �����߶���
    s.move(); // �����ߵ��ƶ���������ʼ��Ϸ
}
