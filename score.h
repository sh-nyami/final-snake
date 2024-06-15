#pragma once
#ifndef SCORE
#define SCORE
class Score {
public:
    int bodyScore;
    int growthScore;
    int poisonScore;
    int gateScore;
    int maxbodyScore;
    int bodyScore_mission;
    int growthScore_mission;
    int poisonScore_mission;
    int gateScore_mission;
    Score() {
        bodyScore = 0;
        growthScore = 0;
        poisonScore = 0;
        gateScore = 0;
        maxbodyScore = 0;
        bodyScore_mission = 4;
        growthScore_mission = 1;
        poisonScore_mission = 0;
        gateScore_mission = 0;
    }
    void init(int n) {

        bodyScore_mission = 4 + n;
        growthScore_mission = 1 + n;
        poisonScore_mission = 0 + n;
        gateScore_mission = 0 + n;

    }

};
#endif