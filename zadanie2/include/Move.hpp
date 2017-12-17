#pragma once


struct Move
{
    int cost;
    int cityFrom;
    int cityTo;
};

struct TabuMove
{
    std::pair<int, int> move;
    int tenure;
};