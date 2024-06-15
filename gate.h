#pragma once
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "snake.h"
using namespace std;
#ifndef GATE
#define GATE
typedef int(*Temp)[21];
class Gate
{
    pair<int, int> in, out;
    int outdir;
    int indir;
    int dir_pair[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
    int gateTime;
    bool isActive;

public:
    Gate()
    {
        gateTime = 0;
        isActive = false;
    }
    bool generateGate(Snake s, Temp m)
    {
        for (int i = 0; i < s.getLength(); i++)
        {
            int j;
            for (j = 0; j < 4; j++)
            {
                int first = s.getBody(i).first;
                int second = s.getBody(i).second;
                int dirY = dir_pair[j][1];
                int dirX = dir_pair[j][0];
                if ((second + dirY == in.second && first + dirX == in.first)
                    || (second + dirY == out.second && first + dirX == out.first))
                {
                    gateTime += 1;
                    break;
                }
            }
            if (j != 4) break;
        }
        if (time(NULL) - gateTime > 10)
        {
            vector<pair<int, int> > ValidSpot;
            for (int i = 0; i < 21; i++) {
                for (int j = 0; j < 21; j++) {
                    if (m[i][j] == 1) ValidSpot.push_back(pair<int, int>(j, i));
                }
            }

            while (true)
            {
                int inidx = rand() % ValidSpot.size();
                int outidx = rand() % ValidSpot.size();
                if (inidx == outidx) continue;
                in = ValidSpot[inidx];
                out = ValidSpot[outidx];

                if (ValidSpot[outidx].first == 0) { outdir = 3; }
                else if (ValidSpot[outidx].first == 20) { outdir = 1; }
                else if (ValidSpot[outidx].second == 0) { outdir = 2; }
                else if (ValidSpot[outidx].second == 20) { outdir = 0; }
                else { outdir = 4; }

                if (ValidSpot[inidx].first == 0) { indir = 3; }
                else if (ValidSpot[inidx].first == 20) { indir = 1; }
                else if (ValidSpot[inidx].second == 0) { indir = 2; }
                else if (ValidSpot[inidx].second == 20) { indir = 0; }
                else { indir = 4; }

                gateTime = time(NULL);
                isActive = true;
                return true;
            }
        }
        return false;
    }
    bool getActive() { return isActive; }
    pair<int, int> getIn() { return in; }
    pair<int, int> getOut() { return out; }
    pair<int, int> getOutDir(int d, Temp m)
    {
        switch (d)
        {
        case 1:
            d = 2;
            break;
        case 2:
            d = 3;
            break;
        case 3:
            d = 1;
            break;
        }
        if (outdir == 4)
        {
            int t = m[out.second + dir_pair[d][1]][out.first + dir_pair[d][0]];
            if (t == 1 || t == 2)
            {
                d = (d + 1) % 4;
                t = m[out.second + dir_pair[d][1]][out.first + dir_pair[d][0]];
                if (t == 1 || t == 2)
                {
                    d = (d + 3) % 4;
                    t = m[out.second + dir_pair[d][1]][out.first + dir_pair[d][0]];
                    if (t == 1 || t == 2)
                    {
                        d = (d + 2) % 4;
                        return pair<int, int>(dir_pair[d][0], dir_pair[d][1]);
                    }
                    else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
                }
                else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
            }
            else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
        }
        else { return pair<int, int>(dir_pair[outdir][0], dir_pair[outdir][1]); }
    }
    pair<int, int> getInDir(int d, Temp m)
    {
        switch (d)
        {
        case 1:
            d = 2;
            break;
        case 2:
            d = 3;
            break;
        case 3:
            d = 1;
            break;
        }
        if (indir == 4)
        {
            int t = m[in.second + dir_pair[d][1]][in.first + dir_pair[d][0]];
            if (t == 1 || t == 2)
            {
                d = (d + 1) % 4;
                t = m[in.second + dir_pair[d][1]][in.first + dir_pair[d][0]];
                if (t == 1 || t == 2)
                {
                    d = (d + 3) % 4;
                    t = m[in.second + dir_pair[d][1]][in.first + dir_pair[d][0]];
                    if (t == 1 || t == 2)
                    {
                        d = (d + 2) % 4;
                        return pair<int, int>(dir_pair[d][0], dir_pair[d][1]);
                    }
                    else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
                }
                else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
            }
            else { return pair<int, int>(dir_pair[d][0], dir_pair[d][1]); }
        }
        else { return pair<int, int>(dir_pair[indir][0], dir_pair[indir][1]); }
    }
};
#endif