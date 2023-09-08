#pragma once

#include "Global.hpp"

#include <cmath>
#include <queue>
#include <unordered_set>

class AStar {

    private:
        std::priority_queue<std::shared_ptr<GLOBAL::ASTAR::Node>, std::vector<std::shared_ptr<GLOBAL::ASTAR::Node>>,GLOBAL::ASTAR::NodeComparator> openSet;
        std::vector<std::shared_ptr<GLOBAL::ASTAR::Node>> openSetVector;
        bool isFinished;

        float CalculateH(const GLOBAL::Position<>& pos1, const GLOBAL::Position<>& pos2);
        

        int neighbours[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
        
    public:
        AStar();
        ~AStar();
        void AStarSearch(const GLOBAL::Position<uint8_t>& startPos, const GLOBAL::Position<uint8_t>& goalPos, GLOBAL::Grid<>& grid, std::vector<GLOBAL::Position<uint8_t>>& aStarPathVector, GLOBAL::Grid<float>& aStarGScore);
        bool IsInOpenSet(int x, int y); 
        void Reset();
        bool Finish(){ return isFinished;}
        
};