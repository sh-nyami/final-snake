#include <ncurses.h>
#include <iostream>
#include "map.h"
#include "score.h"

Map m;

int game(int tick, int mission)
{
    Snake snake = Snake();
    Item item[3];
    Gate gate = Gate();
    Score score = Score();
    int check = 2;
    for (int i = 0; i < 3; i++)
    {
        item[i] = Item();
    }

    while (1) {
        m.getTick(tick);
        m.init();
        m.view(snake, item, gate, score);

        snake.setDirection();
        snake.move();
        gate.generateGate(snake, m.getMap());
        score.init(mission);

        for (int i = 0; i < 3; i++)
            item[i].itemGenerate(snake, m.getMap(), item);

        for (int i = 0; i < 3; i++)
        {
            if (item[i].getActive())
            {
                if (item[i].getX() == snake.getX() && item[i].getY() == snake.getY())
                {
                    if (item[i].getValue() > 0) { score.growthScore += 1; }
                    else { score.poisonScore += 1; }
                    snake.addLength(item[i].getValue());
                    item[i].setActive(false);
                }
            }
        }

        score.bodyScore = snake.getLength() + 1;
        if (score.maxbodyScore < score.bodyScore) { score.maxbodyScore = score.bodyScore; }

        if (gate.getActive())
        {
            if (snake.getX() == gate.getIn().first && snake.getY() == gate.getIn().second)
            {
                score.gateScore += 1;
                snake.gateTo(gate.getOut().first, gate.getOut().second, gate.getOutDir(snake.getDir(), m.getMap()));
            }
            else if (snake.getX() == gate.getOut().first && snake.getY() == gate.getOut().second)
            {
                score.gateScore += 1;
                snake.gateTo(gate.getIn().first, gate.getIn().second, gate.getInDir(snake.getDir(), m.getMap()));
            }
        }
        check = m.isGameOver(snake, score);
        if (check != 2) { break; }
    }
    return check;
}

int main()
{
    int tick = 500000;
    int res;
    for (int i = 0; i < 5; i++) {
        m = Map();
        res = game(tick - (i * 50000), i);
        if (res) break;
    }
    return 0;
}