#include "RenderGrid.hpp"

#include <iostream>
#include <cmath>

RenderGrid::RenderGrid() {

}

RenderGrid::~RenderGrid() {

}


void RenderGrid::DrawGrid(sf::RenderWindow& window, sf::Sprite& gridSprite, const GLOBAL::Grid<>& grid, const uint16_t gridBeginX, const uint16_t gridBeginY, sf::Sprite& startSprite, const GLOBAL::Position<>& startPos, sf::Sprite& goalSprite,const GLOBAL::Position<>& goalPos, sf::Sprite& obstacleSprite, const GLOBAL::Grid<float>& distScore){
    
	// Visited tiles are set a colour that eventually showcases a gradient from start to the goal. The max distance obtained from the gScores of the A* algorithm
	float maxDist = 0;
	for(const std::array<float, GLOBAL::GRID::ROWS>& column : distScore){
		for(const float distScore : column){
			maxDist = std::max(distScore, maxDist);
		}
	}
	
	for (uint8_t i = 0; i < GLOBAL::GRID::COLUMNS; i++) {
		for (uint8_t j = 0; j < GLOBAL::GRID::ROWS; j++) {
			gridSprite.setPosition(GLOBAL::GRID::ORIGIN_X + gridBeginX + i * GLOBAL::GRID::CELL_SIZE, GLOBAL::GRID::ORIGIN_Y + gridBeginY + j * GLOBAL::GRID::CELL_SIZE);
			
			if (i == startPos.first && j == startPos.second) {
				startSprite.setPosition(GLOBAL::GRID::ORIGIN_X + gridBeginX + startPos.first * GLOBAL::GRID::CELL_SIZE, GLOBAL::GRID::ORIGIN_Y + gridBeginY + startPos.second * GLOBAL::GRID::CELL_SIZE);
				window.draw(startSprite);
			} else if (i == goalPos.first && j == goalPos.second) {
				goalSprite.setPosition(GLOBAL::GRID::ORIGIN_X + gridBeginX + goalPos.first * GLOBAL::GRID::CELL_SIZE, GLOBAL::GRID::ORIGIN_Y + gridBeginY + goalPos.second * GLOBAL::GRID::CELL_SIZE);
				window.draw(goalSprite);
			} else if (grid[i][j] == GLOBAL::GRID::Cell::Obstacle) {
				obstacleSprite.setPosition(GLOBAL::GRID::ORIGIN_X + gridBeginX + i * GLOBAL::GRID::CELL_SIZE, GLOBAL::GRID::ORIGIN_Y + gridBeginY + j * GLOBAL::GRID::CELL_SIZE);
				window.draw(obstacleSprite);
			}
			else {
				GLOBAL::GRID::Cell cellType = grid[i][j];
				

 				switch (cellType) {
					case GLOBAL::GRID::Cell::Empty: {
						gridSprite.setColor(sf::Color(36, 36, 85));
						break;
					}
					case GLOBAL::GRID::Cell::Path: {
						gridSprite.setColor(sf::Color(255, 255, 255));
						break;
					}
					case GLOBAL::GRID::Cell::Visited: {
						uint8_t colVal = 255- round(255 * distScore[i][j] / maxDist);
						gridSprite.setColor(sf::Color(0, std::max(0, colVal - 170), std::min(255, 85 + colVal)));
					}
				}
				window.draw(gridSprite);
			}			
		}
	}
}



