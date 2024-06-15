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
        // ���� ������ ���� <time.h>�� �����Ѵ�
        srand(time(NULL));
        isActive = false;
        itemTime = 0;
        x = -1;
        y = -1;
    }

    // �������� �����ϰ�, ��� �ٸ� �����۰��� ��ħ�� ���ϱ� ���� ��ġ�� �����Ѵ�
    bool itemGenerate(Snake s, mapArr m, Item items[])
    {
        // ������ ���� ������ �����ϱ� ���� ���� �ð��� ����Ѵ�
        if (time(NULL) - itemTime > 4)
        {
            // �������� ���� �������� �����Ѵ�
            itemValue = rand() % 2 ? -1 : 1;
            while (true)
            {
                bool temp = false;
                int tx = rand() % 19 + 1;
                int ty = rand() % 19 + 1;

                // ���� ��ġ�� ������ ��ġ�� ���Ͽ� ��ġ���� Ȯ���Ѵ�
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
                if (temp) continue; // ��ġ�� ��� �ٸ� ��ġ�� �ٽ� �����Ѵ�

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