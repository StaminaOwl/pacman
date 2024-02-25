#pragma once
#include"SFML/Graphics.hpp"
#include "ghost.h"
class GhostManagement
{
private:
	sf::Texture look_down, look_up, look_left, look_right;
	sf::Clock timer, timer_for_frighten_mode, speed_diminution;
	sf::Time eslapsed_time, frighten_mode_elapsed, elapsed_speed_diminution;
public:
	void main(std::vector<ghost> & ghostVector);
};

