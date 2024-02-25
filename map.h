#pragma once
#include <vector>
#include <string>
#include"SFML/Graphics.hpp"
#include <array>
#include "GameConfig.h"
#include <iostream>
using std::string;
using std::vector;
class gamemap {
private :
	bool start = true;
	sf::Sprite door;
	sf::Texture door_texture;
	std::vector<sf::RectangleShape> all_walls;
	std::vector<sf::CircleShape> all_dots;
	std::vector<sf::Vector2f> dots_positions;
	std::vector<sf::Vector2f> energizers_positions;

	vector <string > mapPC = {
{" ################### "},
{" #........#........# "},
{" #o##.###.#.###.##o# "},
{" #.................# "},
{" #.##.#.#####.#.##.# "},
{" #....#...#...#....# "},
{" ####.###.#.###.#### "},
{"    #.#.......#.#    "},
{"#####.#.##D##.#.#####"},
{"........#123#........"},
{"#####.#.#####.#.#####"},
{"    #.#.......#.#    "},
{" ####.#.#####.#.#### "},
{" #........#........# "},
{" #.##.###.#.###.##.# "},
{" #o.#...........#.o# "},
{" ##.#.#.#####.#.#.## "},
{" #....#...#...#....# "},
{" #.######.#.######.# "},
{" #.................# "},
{" ################### "}

	};


	// dededededede
public :
	gamemap();
	std::vector<std::string> getmap();
	void display_blocks(sf::RenderWindow& window);
	void draw_map(sf::RenderWindow& window);
	void update(sf::Vector2f dot_to_remove, sf::Vector2f energizer_to_remove);
	std::vector<sf::Vector2f> get_dots_positions();
	std::vector<sf::Vector2f> get_energizers_positions();

};

