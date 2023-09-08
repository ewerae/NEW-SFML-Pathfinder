#include "AStar.hpp"
#include <iostream>

AStar::AStar() {
    isFinished = false;
    
}

AStar::~AStar() {

}

void AStar::Reset() {
    while (!openSet.empty()) {
        openSet.pop();
    }
    openSetVector.clear();
    isFinished = false;
    
}

// Calculate the H score, heuristic approach, commented lines are other approaches.
float AStar::CalculateH(const GLOBAL::Position<>& pos1, const GLOBAL::Position<>& pos2) {
    float distX = std::abs(pos2.first - pos1.first);
    float distY = std::abs(pos2.second - pos1.second);

    //return distX + distY + (std::sqrt(2)  - 2) * std::min(distX, distY);
    //return std::max(distX, distY) + (std::sqrt(2) - 1) * std::min(distX, distY); 
    return std::sqrt(std::pow(distX,2) + std::pow(distY,2));
}

// Have to check if a node is already present in the openSet priority queue, however, finding if a node is already in there is quite troublesome, hence another vector filled with nodes is used to check.
bool AStar::IsInOpenSet(int x, int y) {
    for (const auto& node : openSetVector) {
        if (node->pos.first == x && node->pos.second == y) {
            return true;
        }
    }
    return false;
}


void AStar::AStarSearch(const GLOBAL::Position<>& startPos, const GLOBAL::Position<>& goalPos, GLOBAL::Grid<>& grid, std::vector<GLOBAL::Position<uint8_t>>& aStarPathVector, GLOBAL::Grid<float>& aStarGScore){
    
    if(openSet.empty()){
        openSet.push(std::make_shared<GLOBAL::ASTAR::Node>(startPos)); // This initially sets the start node as the first node in the priority queue.
        return;
    }
    std::shared_ptr<GLOBAL::ASTAR::Node> current = openSet.top();
    openSet.pop();
    
    if (isFinished)
        return;

    // First checks if goal is reached and if so finds the optimal pathing by obtaining the parent member of each node.
    if (grid[current->pos.first][current->pos.second]!= GLOBAL::GRID::Cell::Visited) {
        if(current->pos.first == goalPos.first && current->pos.second == goalPos.second){
            while(current){
                aStarPathVector.push_back(current->pos); 
                if (current->pos != startPos && current->pos != goalPos ){
                    grid[current->pos.first][current->pos.second] = GLOBAL::GRID::Cell::Path;     
                }     
                if (current->parent) {
                    current = current->parent;
                } else {
                    break; 
                }
            }
            
            isFinished = true;
        }

        grid[current->pos.first][current->pos.second] = GLOBAL::GRID::Cell::Visited;
        aStarGScore[current->pos.first][current->pos.second] = current->g;

        // Computes the score of diagonal and adjacent tiles.
        for (const auto& neighbour : neighbours) {
            int nx = current->pos.first + neighbour[0]; 
            int ny = current->pos.second + neighbour[1];
            
            if((grid[current->pos.first + 1][current->pos.second] == GLOBAL::GRID::Cell::Obstacle && grid[current->pos.first][current->pos.second + 1] == GLOBAL::GRID::Cell::Obstacle) ||
                (grid[current->pos.first - 1][current->pos.second] == GLOBAL::GRID::Cell::Obstacle && grid[current->pos.first][current->pos.second + 1] == GLOBAL::GRID::Cell::Obstacle) || 
                (grid[current->pos.first + 1][current->pos.second] == GLOBAL::GRID::Cell::Obstacle && grid[current->pos.first][current->pos.second - 1] == GLOBAL::GRID::Cell::Obstacle) ||
                (grid[current->pos.first - 1][current->pos.second] == GLOBAL::GRID::Cell::Obstacle && grid[current->pos.first][current->pos.second - 1] == GLOBAL::GRID::Cell::Obstacle)){
                break;
            } // Checks if two diagonal obstacles are placed, and if so does not allow a path to form.


            if (nx >= 0 && nx < GLOBAL::GRID::COLUMNS && ny >= 0 && ny < GLOBAL::GRID::ROWS && grid[nx][ny] != GLOBAL::GRID::Cell::Obstacle && grid[nx][ny] != GLOBAL::GRID::Cell::Visited) { 
                if (!IsInOpenSet(nx,ny)){
                    auto neighbourNode = std::make_shared<GLOBAL::ASTAR::Node>(GLOBAL::Position<uint8_t>(nx, ny)); // Creates a new node shared pointer if a node for a particular tile has not been yet made.

                    if(std::abs(neighbour[0]) == std::abs(neighbour[1])){ // Computes G score, adjacent tiles are only  + 1, diagonals are +  sqrt(2)
                        neighbourNode->g = current->g + std::sqrt(2);
                    } else{
                        neighbourNode->g = current->g + 1;
                    }
                    
                    neighbourNode->h = CalculateH(neighbourNode->pos, goalPos); 
                    neighbourNode->f = neighbourNode->g + neighbourNode->h;
                    neighbourNode->parent = current;

                    openSetVector.push_back(neighbourNode);
                    openSet.push(neighbourNode);
                    
                }
                
            }
        }
    }
}