#pragma once


#include <array>
#include <chrono>
#include <queue>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "RenderGrid.hpp"
#include "AStar.hpp"




class Game {
    private:
        sf::RenderWindow window;
        bool isRunning;

        RenderGrid renderGrid;
        AStar aStar;

        GLOBAL::Position<uint8_t>  GetMouseCell(sf::RenderWindow& window);

        void ProcessEvents();
        void Update();
        void Render();
        

        sf::Sprite gridSprite;
        sf::Texture fontTexture;
        sf::Texture gridTexture;

        sf::Texture startTexture;
        sf::Texture goalTexture;
        sf::Texture obstacleTexture;

        sf::Sprite startSprite;
        sf::Sprite goalSprite;
        sf::Sprite obstacleSprite;

        GLOBAL::Grid<> grid;
        GLOBAL::Position<uint8_t> startPos;
        GLOBAL::Position<uint8_t> goalPos;

        GLOBAL::Grid<float> aStarGScore;
        std::vector<GLOBAL::Position<uint8_t>> aStarPathVector;
        

        GLOBAL::Position<uint8_t> mousePressedPos;
        GLOBAL::Position<uint8_t> lastMousePos;

        bool mousePress;
        bool isRun;

        sf::Text test;
        sf::Font font;


    public:
        Game();
        ~Game();

        void Run();

    
};