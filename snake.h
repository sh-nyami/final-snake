#pragma once
#include <ncurses.h>
#include <queue>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


using namespace std;
#ifndef SNAKE
#define SNAKE
class Snake
{
    int x, y;
    pair<int, int> pre;
    int dir = 1;
    int dir_pair[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
    int len;
    deque<pair<int, int> > body;


public:
    Snake()
    {
        x = 1;
        y = 1;
        len = 2;
        dir = 1;
    }
    void setDirection()
    {
        int key = getch();
        switch (key)
        {
        case KEY_UP:
            dir = 0;
            break;
        case KEY_DOWN:
            dir = 1;
            break;
        case KEY_LEFT:
            dir = 2;
            break;
        case KEY_RIGHT:
            dir = 3;
            break;
        }
    }
    void move()
    {
        pre = pair<int, int>(x, y);
        if (!body.empty() && body.size() >= len)
        {
            pre = pair<int, int>(*(body.end() - 1));
            body.pop_back();
        }
        if (body.size() < len)
            body.push_front(pair<int, int>(x, y));
        x += dir_pair[dir][0];
        y += dir_pair[dir][1];
    }
    int getDir() { return dir; }
    void gateTo(int gx, int gy, pair<int, int> d)
    {
        for (int i = 0; i < 4; i++) {
            if (dir_pair[i][0] == d.first && dir_pair[i][1] == d.second) {
                dir = i; break;
            }
        }
        pre = pair<int, int>(x, y);
        if (!body.empty() && body.size() >= len)
        {
            pre = pair<int, int>(*(body.end() - 1));
            body.pop_back();
        }
        if (body.size() < len)
            body.push_front(pair<int, int>(x, y));
        x = gx + dir_pair[dir][0];
        y = gy + dir_pair[dir][1];
    }
    void addLength(int add)
    {
        len += add;
        if (add > 0) {
            body.push_back(pre);
        }
        else {
            pre = pair<int, int>(*(body.end() - 1));
            body.pop_back();
        }
    }
    int getLength() { return len; }
    pair<int, int> getBody(int idx) { return *(body.begin() + idx); }
    int getX() { return x; }
    int getY() { return y; }
    pair<int, int> getLast() { return pre; }
};
#endif