#include "PacMan.h"


PacMan::PacMan() {
	lock = false;
	start = true;
	py = 96;
	px = 64;
	speed = 1;
	Direction = 10;
	otherDirectionDesired = false;
	chemin = sf::Vector2f(px, py);
	energizer_taken = false;
}

int PacMan::getDirection() {
	return Direction_pacman;
}
void PacMan::pacman_move(sf::CircleShape &Pacman, std::vector<std::string> mapPC) {
 	
	if (!lock)
		last_Direction = Direction; 
	previous.x = px;
	previous.y = py;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		Direction = Left;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		Direction = Right;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		Direction = Up;
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		Direction = Down;

	if (Direction != 0 && Direction == last_Direction)
		Direction_pacman = Direction;
	else
		Direction_pacman = last_Direction;

	if (last_Direction != Direction) {
		otherDirectionDesired = true;
		movement(Direction);
		if (isDirectionAvailable(mapPC)) {
			otherDirectionDesired = false;
			lock = false;
		}
		else {
			lock = true;
			px = previous.x;
			py = previous.y;
			movement(last_Direction);
			if (!isDirectionAvailable(mapPC)) {
				px = previous.x;
				py = previous.y;
				Direction = 0;
			}
		}
	}

	else {
		movement(Direction);
		DirectionAllowed = isDirectionAvailable(mapPC);

		if (!DirectionAllowed) {
			px = previous.x;
			py = previous.y;
			Direction = 0;
		}
	}

	chemin = sf::Vector2f(px, py);
	Pacman.setPosition(chemin);
	start = false;
	pacman_position = Pacman.getPosition();

	if (px <= -cell_size+1)
		px = cell_size * map_width - 1;
	else if (px >= cell_size * map_width -1)
		px = -cell_size+1;
}
sf::Vector2f PacMan::get_position() {
	return pacman_position;
}
bool PacMan::isDirectionAvailable(const std::vector<std::string> mapPC) {
	
	for (int y = 0; y < map_lenght; y++) {
		for (int x = 0; x < map_width; x++) {

			int top = y * offsetY;
			int bottom = y * offsetY + offsetY;
			int left = x * offsetX;
			int right = x * offsetX + offsetX;

			if (mapPC[y][x] == '#' && px + offsetX > left && px < right && py + offsetY > top && py < bottom) {
				return false;
			}
			

		}
	}
	return true;



}
void PacMan::movement(int direction) {

	switch (direction) {

	case Left:
		px -= speed;
		break;

	case Right:
		px += speed;
		break;

	case Up:
		py -= speed;
		break;

	case Down:
		py += speed;
		break;
	}
}


void PacMan::dots_eaten(sf::CircleShape& Pacman, std::vector<sf::Vector2f> dots_positions) {
	dot_eaten = sf::Vector2f(0, 0);
	sf::FloatRect pacman_box = Pacman.getGlobalBounds();
	for (sf::Vector2f dot : dots_positions) {
	
		if (pacman_box.contains(dot))
			dot_eaten = dot;
		
		
	}

}
void PacMan::energizers_eaten(sf::CircleShape& Pacman, std::vector<sf::Vector2f> energizers_positions) {
	energizer_eaten = sf::Vector2f(0, 0);
	energizer_taken = false;
	sf::FloatRect pacman_box2 = Pacman.getGlobalBounds();
	for (sf::Vector2f energizer : energizers_positions) {
		if (pacman_box2.contains(energizer)) {
			energizer_eaten = energizer;
			energizer_taken = true;
		}
		
	}
	
}
sf::Vector2f PacMan::get_dot_eaten() {
	return dot_eaten;
}
sf::Vector2f PacMan::get_energizer_eaten() {
	return energizer_eaten;
}
bool PacMan::get_energizer_taken() {
	return energizer_taken;
}
