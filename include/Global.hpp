#pragma once
#include <cstdint>
#include <array>
#include <chrono>
#include <memory>

namespace GLOBAL{
    
    namespace GRID{
        constexpr uint8_t CELL_SIZE = 8;
        constexpr uint8_t ORIGIN_X = 8;
        constexpr uint8_t ORIGIN_Y = 8;

        constexpr uint16_t COLUMNS = 80;
		constexpr uint16_t ROWS = 80;


        enum class Cell{
            Empty,
            Path,
            Visited,
            Obstacle
        };


    }

    namespace SCREEN{
        constexpr uint8_t RESIZE = 1;

		constexpr uint16_t HEIGHT = 720;
		constexpr uint16_t WIDTH = 1280;

        // constexpr std::chrono::microseconds FRAME_DURATION(16667);
    }

    template<typename valType>
    char Sign(const valType val) {
		return (0 < val) - (0 > val);
	}

    template <typename valType = GRID::Cell>
	using Grid = std::array<std::array<valType, GRID::ROWS>, GRID::COLUMNS>;

	
	template <typename valType = uint8_t>
	using Position = std::pair<valType, valType>;

    namespace ASTAR {
        struct Node {
            Position<uint8_t> pos;
            float g, h, f;
            std::shared_ptr<Node> parent;

            Node(Position<uint8_t> pos) : pos(pos), g(0), h(0), f(0), parent(nullptr) {}
        };

        struct NodeComparator {
            bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) const {
                return a->f > b->f;
            }
        };
    }

    
}