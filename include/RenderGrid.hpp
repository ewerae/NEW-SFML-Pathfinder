#pragma once
#include <cstdint>

#include "Global.hpp"

#include <SFML/Graphics.hpp>

class RenderGrid {

    public:
        RenderGrid();
        ~RenderGrid();

        void DrawGrid(sf::RenderWindow& window, sf::Sprite& gridSprite, const GLOBAL::Grid<>& grid, const uint16_t gridBeginX, const uint16_t gridBeginY, sf::Sprite& startSprite, const GLOBAL::Position<>& startPos, sf::Sprite& goalSprite, const GLOBAL::Position<>& goalPos, sf::Sprite& obstacleSprite, const GLOBAL::Grid<float>& distScore);
};