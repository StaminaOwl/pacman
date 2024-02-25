#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
#include<limits>
#include "GameConfig.h"
#include <math.h>
#include "PacMan.h"
#include <random>
using std::cout;
using std::endl;
class ghost
{

private :
	sf::Texture look_down, look_up, look_left, look_right;
	bool energizer_taken;
	Clock horloge_frighten;
	Time energizer_duration;
	bool door_taken;
	std::vector<int> Frighten_mode_direction;
	enum Directionn {
		Left = 1,
		Right,
		Up,
		Down
	};

	
	sf::Texture ghost_texture;
	sf::Texture frighten_texture;
	sf::Texture eaten_texture;
	int speed;
	bool immunized;
	sf::Texture freeze;
	sf::Clock timer, timer_for_frighten_mode, speed_diminution;
	sf::Time eslapsed_time, frighten_mode_elapsed, elapsed_speed_diminution;

	bool way_available, frighten_mode, backward_movement, test;
	bool ghost_eaten, in_jail;
	int GHOST_ID;
	int limit;
	float distance_from_left, distance_from_right, distance_from_up, distance_from_down, speed_decrease;
	short py, px;
	bool start;
	std::string ghost_name;
	sf::Vector2f blinky_position, vector_to_target, extended_vector, pacman_position;
	sf::Vector2f target;
	sf::Vector2f scatter_mode_home;
	sf::Vector2f test_direction;
	sf::Vector2f home;
	int direction;
	int pacman_direction;
	int backward_direction;
	int scatter_duration = 20, chase_duration = 7;

public:
	void setEatenTexture(sf::Texture &eyes);
	int getDirection();
	bool chase_mode, scatter_mode;
	string get_name();
	void get_freeze_mode();
	ghost(std::string Ghost_name, sf::Texture &ghost_texture, sf::Texture &frighten_texture);
	void ghost_move(sf::Sprite &cible, sf::Sprite blinky, sf::Sprite& ghost, sf::CircleShape& pacman, int pacman_direction, std::vector <std::string> mapPC, PacMan& player);
	void getDirection(sf::Sprite& ghost, std::vector <std::string> mapPC);
	void getBackwardDirection();
	void fritghen_mode_behavior();
	bool collision(const std::vector<std::string> mapPC);
	int get_shortest_way();
	bool interesection();
	void normal_move(PacMan& player, CircleShape& pacman, std::vector <std::string> mapPC, sf::Sprite& ghost, sf::Sprite blinky);
	void frighten_move(std::vector <std::string> mapPC, sf::Sprite& ghost);
	int getRandomDirection(vector <int> &Frighten_mode_direction);
	void go_home();
	void update_target(PacMan& pacman, sf::Sprite &blinky, sf::Sprite& ghost);
	bool collisionWithPacman(sf::Sprite& ghost, CircleShape& pacman);
	bool got_home(sf::Sprite& ghost);
	bool getScatterMode();
	bool getGhostEaten();
};