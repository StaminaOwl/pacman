#include "map.h"


std::vector<std::string> gamemap::getmap() {
	return mapPC;
}
gamemap::gamemap() {
	
	
		if (!door_texture.loadFromFile("images/door.png")) {
			std::cout << "ERROR !! " << std::endl;
		}
		door.setTexture(door_texture);
}
std::vector<sf::Vector2f> gamemap::get_energizers_positions() {
	return energizers_positions;
}
void gamemap::draw_map(sf::RenderWindow& window) {
	energizers_positions.clear();
	dots_positions.clear();
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_lenght; y++) {
			
				if (start == true){
					if (mapPC[x][y] == '#') {
						sf::RectangleShape wall(sf::Vector2f(offsetX, offsetY));
						wall.setFillColor(sf::Color::Blue);
						wall.setPosition(sf::Vector2f(y * offsetY, x * offsetX));
						all_walls.push_back(wall);
					}
					
						
				}

				if (mapPC[x][y] == '.') {
					sf::CircleShape dot(2.5);
					sf::Vector2f dot_position = sf::Vector2f(y * offsetY + 14, x * offsetX + 14);
					dot.setFillColor(sf::Color::Yellow);
					dot.setPosition(sf::Vector2f(y * offsetY + 14, x * offsetX + 14));
					window.draw(dot);
					dots_positions.push_back(dot_position);
					
				}
				if (mapPC[x][y] == 'o') {
					sf::CircleShape energizer(7);
					sf::Vector2f energizer_position = sf::Vector2f(y * offsetY + 9, x * offsetX + 9);
					energizer.setFillColor(sf::Color::Yellow);
					energizer.setPosition(sf::Vector2f(y * offsetY + 9, x * offsetX + 9));
					window.draw(energizer);
					energizers_positions.push_back(energizer_position);

				}
				else if (mapPC[x][y] == 'D') {
					door.setPosition(sf::Vector2f(y * offsetY, x * offsetX));
					window.draw(door);
				}

		}
	}
	start = false;

}

void gamemap::display_blocks(sf::RenderWindow& window) {
	for (int i = 0; i < all_walls.size(); i++)
		window.draw(all_walls[i]);
}


std::vector<sf::Vector2f> gamemap::get_dots_positions() {
	return dots_positions;
}

void gamemap::update(sf::Vector2f dot_to_remove, sf::Vector2f energizer_to_remove) {
	for (int x = 0; x < map_width; x++) {
		for (int y = 0; y < map_lenght; y++) {
			sf::Vector2f dot = sf::Vector2f(y * offsetY + 14, x * offsetX + 14);
			if (dot == dot_to_remove)
				mapPC[x][y] = ' ';
			sf::Vector2f energizer = sf::Vector2f(y * offsetY + 9, x * offsetX + 9);
			if (energizer == energizer_to_remove)
				mapPC[x][y] = ' ';
		}
	}
}
