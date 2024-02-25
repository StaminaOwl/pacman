#pragma once
#include"SFML/Graphics.hpp"

constexpr int cell_size = 32;
constexpr int cells_weight = 21;
constexpr int cells_height = 21;
constexpr int map_lenght = 21;
constexpr int map_width = 21;
constexpr int offsetY = 32;
constexpr int offsetX = 32;
constexpr int frighten_mode_duration = 9;


const sf::Vector2f home_inky = sf::Vector2f(cell_size * 10, cell_size * 9);
const sf::Vector2f home_blinky = sf::Vector2f(cell_size * 10, cell_size * 9);
const sf::Vector2f home_pinky = sf::Vector2f(cell_size *10, cell_size * 9);
const sf::Vector2f home_clyde = sf::Vector2f(cell_size * 10, cell_size * 9);



const sf::Vector2f prison = sf::Vector2f(cell_size * 10, cell_size * 9);

const sf::Vector2f door = sf::Vector2f(cell_size * 10, cell_size * 7);

const sf::Vector2f clyde_corner = sf::Vector2f(0, cell_size * 21);
const sf::Vector2f blinky_corner = sf::Vector2f(cell_size * 20, -cell_size);
const sf::Vector2f pinky_corner = sf::Vector2f(0, -cell_size);
const sf::Vector2f inky_corner = sf::Vector2f(cell_size * 20, cell_size * 21);
