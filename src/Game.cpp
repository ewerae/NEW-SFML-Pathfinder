#include "Game.hpp"


#include <iostream>


Game::Game() : isRunning(true) {
    //Initalise window size, title, style and camera 
	window.create(sf::VideoMode(GLOBAL::SCREEN::RESIZE * GLOBAL::SCREEN::WIDTH, GLOBAL::SCREEN::RESIZE * GLOBAL::SCREEN::HEIGHT), "Pathfinding", sf::Style::Close);
    window.setView(sf::View(sf::FloatRect(0, 0, GLOBAL::SCREEN::WIDTH, GLOBAL::SCREEN::HEIGHT)));

    
    // Intialise the font and grid sprites;
    fontTexture.loadFromFile("assets/fonts/font.png");
    gridTexture.loadFromFile("assets/sprites/grid.png");
    gridSprite.setTexture(gridTexture);

    startTexture.loadFromFile("assets/sprites/start.png");
    goalTexture.loadFromFile("assets/sprites/goal.png");
    obstacleTexture.loadFromFile("assets/sprites/obstacle.png");

    startSprite.setTexture(startTexture);
    goalSprite.setTexture(goalTexture);
    obstacleSprite.setTexture(obstacleTexture);

    font.loadFromFile("assets/fonts/playfair/PlayfairDisplay-VariableFont_wght.ttf");


    mousePress = false;
    isRun = false;

    // We will initially place start and end positions at the very start and at the very end, unless placed elsewhere
    startPos = GLOBAL::Position<uint8_t>(0, 0);
    goalPos = GLOBAL::Position<uint8_t>(GLOBAL::GRID::COLUMNS - 2, GLOBAL::GRID::ROWS - 1);


    
    // Grid specified in Global.hpp, creates a 2D array, and initialises it with Empty Cell members.
    for (std::array<GLOBAL::GRID::Cell, GLOBAL::GRID::ROWS>& column : grid) {
		column.fill(GLOBAL::GRID::Cell::Empty);
	}



    // Initialise all aStarScores as 0
    for (std::array<float, GLOBAL::GRID::ROWS>& column : aStarGScore) {
        for (float& gScore : column) {
            gScore = 0;
        }
    }

    

}

Game::~Game() {
    
}

GLOBAL::Position<uint8_t> Game::GetMouseCell(sf::RenderWindow& window){
    // Calculates current position of mouse relative to the grid's starting coordinates
    float currentMousePosX = sf::Mouse::getPosition(window).x - GLOBAL::GRID::ORIGIN_X;
    float currentMousePosY = sf::Mouse::getPosition(window).y - GLOBAL::GRID::ORIGIN_Y;

    // Returns a position with the grid coordinates, flooring the division by cell_size obtains the position.
    return GLOBAL::Position<uint8_t>(floor(currentMousePosX/GLOBAL::GRID::CELL_SIZE), floor(currentMousePosY/GLOBAL::GRID::CELL_SIZE));
}

void Game::Run() {
    

    while (isRunning) {
        
        
        ProcessEvents();
        Update();
        Render();
        
    }
}

void Game::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {

        switch (event.type){
            case sf::Event::Closed:{
                window.close();
                isRunning = false;
                break;
            }
            case sf::Event::KeyPressed:{
                switch(event.key.code){   
                    case sf::Keyboard::Space:{ // Reset
                        for (uint8_t i = 0; i < GLOBAL::GRID::COLUMNS; i++) {
                            for (uint8_t j = 0; j < GLOBAL::GRID::ROWS; j++) {
                                grid[i][j] = GLOBAL::GRID::Cell::Empty;
                            }
                        }
                        isRun = false;
                        aStar.Reset();
                        aStarPathVector.clear();
                        break;
                    }
                    case sf::Keyboard::Enter:{ // Runs
                        isRun = true;
                        break;
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            mousePress = true;
            mousePressedPos = GetMouseCell(window);
            
            
        } else{
            mousePress = false;
        }
        // If the mouse press is within the grid
        if(mousePress &&  mousePressedPos.first < GLOBAL::GRID::COLUMNS - 1 &&  mousePressedPos.second < GLOBAL::GRID::ROWS ){
            // Only execute if the mouse is not pressing on already stated cells like the start and goal positions
            if(static_cast<GLOBAL::Position<>>(mousePressedPos) != startPos && static_cast<GLOBAL::Position<>>(mousePressedPos) != goalPos){
                
                if (GLOBAL::GRID::Cell::Obstacle != grid[mousePressedPos.first][mousePressedPos.second]) {
                    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        grid[mousePressedPos.first][mousePressedPos.second] = GLOBAL::GRID::Cell::Empty;

                        startPos = mousePressedPos;
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                        grid[mousePressedPos.first][mousePressedPos.second] = GLOBAL::GRID::Cell::Empty;

                        goalPos = mousePressedPos;
                    } else{
                        grid[mousePressedPos.first][mousePressedPos.second] = GLOBAL::GRID::Cell::Obstacle;
                    }
                    
                    // if(mousePressedPos != lastMousePos){
                    //     int deltaX = mousePressedPos.first - lastMousePos.first;
                    //     int deltaY = mousePressedPos.second - lastMousePos.second;
                    //     int steps = std::max(std::abs(deltaX), std::abs(deltaY));
                        
                    //     for (int step = 1; step <= steps; ++step) {
                    //         int interpX = lastMousePos.first + deltaX * step / steps;
                    //         int interpY = lastMousePos.second + deltaY * step / steps;

                    //         if (interpX >= 0 && interpX < GLOBAL::GRID::COLUMNS - 1 && interpY >= 0 && interpY < GLOBAL::GRID::ROWS) {
                    //             grid[interpX][interpY] = GLOBAL::GRID::Cell::Obstacle;
                    //         }
                    //     }

                        
                    // }
                    // lastMousePos = mousePressedPos;
                    
                }
                
            }
        }       
        
    }
}

void Game::Update() {

    if(!aStar.Finish() && isRun){ // Executes if Enter is pressed and if a path has been found.
        aStar.AStarSearch(startPos, goalPos, grid, aStarPathVector, aStarGScore);
    }
        

}

void Game::Render() {
    window.clear(sf::Color::Black);

    renderGrid.DrawGrid(window, gridSprite, grid, 0,0, startSprite, startPos, goalSprite, goalPos, obstacleSprite, aStarGScore);
    //renderGrid.DrawGrid(window, gridSprite, grid, 500,0, startSprite, startPos,goalSprite, goalPos, obstacleSprite, aStarGScore);

    // test.setFont(font);
    // test.setCharacterSize(16);   
    // test.setFillColor(sf::Color::White);
    // test.setPosition(400.f, 10.0f);
    

    // std::string string;

    // for(int i = 0; i < visitVector.size(); i++){
        
    //     std::string temp = std::to_string(visitVector[i].first);
    //     std::string temp2 = std::to_string(visitVector[i].second);
    //     string = string + "(" + temp + "," + temp2 + ")" + " ";
    //     if(i % 12 == 0){
    //         string = string + "\n";

    //     }
        

    // }
    // test.setString(string);

    // window.draw(test);

    
    window.display();
}