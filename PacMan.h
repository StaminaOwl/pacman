#pragma once
#include"SFML/Graphics.hpp"
#include"GameConfig.h"
#include"map.h"
#include<iostream>
using namespace sf;
class PacMan
{

private:
	enum directionn {
		Left = 1,
		Right,
		Up,
		Down
	};
	sf::Vector2f dot_eaten;
	sf::Vector2f energizer_eaten;
	int a = 1;

	int last_Direction;
	bool lock;
	bool collision;
	bool otherDirectionDesired;
	sf::Vector2f chemin;
	int Direction_pacman;
	int py, px;
	bool DirectionAllowed;
	sf::Vector2f DirectionDesired;
	sf::Vector2f previous;
	sf::Vector2f pacman_position;
	int speed;
	bool start;
	int Direction; // 0 = left, 1 = right, 2 = up, 3 = down
	sf::Vector2f previous_Direction;
public:
	PacMan();
	bool energizer_taken;

	sf::Vector2f get_position();
	sf::Vector2f get_dot_eaten();
	sf::Vector2f get_energizer_eaten();
	void dots_eaten(sf::CircleShape& Pacman, std::vector<sf::Vector2f> dots_positions);
	void energizers_eaten(sf::CircleShape& Pacman, std::vector<sf::Vector2f> energizers_positions);
	void pacman_move(sf::CircleShape& Pacman, std::vector<std::string> mapPC);
	bool isDirectionAvailable(const std::vector<std::string> mapPC) ;
	void movement(int direction);
	int getDirection();
	bool get_energizer_taken();
};

