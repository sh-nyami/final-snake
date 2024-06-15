#pragma once
#include <time.h>
#include "snake.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef int(*mapArr)[21];
#ifndef ITEM
#define ITEM
class Item
{
    int x, y;
    int itemValue;
    int itemTime;
    bool isActive;

public:
    Item()
    {
        // 난수 생성을 위해 <time.h>를 포함한다
        srand(time(NULL));
        isActive = false;
        itemTime = 0;
        x = -1;
        y = -1;
    }

    // 아이템을 생성하고, 뱀과 다른 아이템과의 겹침을 피하기 위해 위치를 조정한다
    bool itemGenerate(Snake s, mapArr m, Item items[])
    {
        // 아이템 생성 간격을 조절하기 위해 현재 시간을 사용한다
        if (time(NULL) - itemTime > 4)
        {
            // 아이템의 값은 랜덤으로 설정한다
            itemValue = rand() % 2 ? -1 : 1;
            while (true)
            {
                bool temp = false;
                int tx = rand() % 19 + 1;
                int ty = rand() % 19 + 1;

                // 뱀의 위치와 아이템 위치를 비교하여 겹치는지 확인한다
                for (int i = 0; i < s.getLength(); i++)
                {
                    if (s.getBody(i).second == ty && s.getBody(i).first == tx)
                        temp = true;
                }
                if (s.getY() == ty && s.getX() == tx) continue;

                if (m[ty][tx] != 0) continue;

                for (int i = 0; i < 3; i++) {
                    if (items[i].getActive() && items[i].getX() == tx && items[i].getY() == ty) {
                        temp = true;
                        break;
                    }
                }
                if (temp) continue; // 겹치는 경우 다른 위치를 다시 선택한다

                itemTime = time(NULL);
                x = tx;
                y = ty;
                isActive = true;
                return true;
            }
        }
        return false;
    }
    bool getActive() { return isActive; }
    void setActive(bool a)
    {
        isActive = a;
        itemTime = time(NULL);

    }
    int getX() { return x; }
    int getY() { return y; }
    int getValue() { return itemValue; }
};
#endif