#include <iostream>
#include"SFML/Graphics.hpp"
#include <vector>
#include "map.h"
#include "Pacman.h"
#include "ghost.h"
#include "GhostManagement.h"

using namespace std;
int main() {
	GhostManagement ghostManager;
	sf::Texture pinky_texture, Inky_texture, Clyde_texture, inky_cible_texture, blinky_cible_texture, pinky_cible_texture, clyde_cible_texture, frighten_texture;
	if (!frighten_texture.loadFromFile("images/frighten_ghost.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	sf::Sprite inky, blinky, pinky, clyde, inky_cible, blinky_cible, pinky_cible, clyde_cible;
	std::vector<sf::Sprite> ghosts;
	if (!clyde_cible_texture.loadFromFile("images/clyde_target.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	if (!inky_cible_texture.loadFromFile("images/inky_target.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	if (!blinky_cible_texture.loadFromFile("images/blinky_target.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	if (!pinky_cible_texture.loadFromFile("images/pinky_target.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	
	if (!	Clyde_texture.loadFromFile("images/clyde.png")) {
		std::cout << "ERROR !! " << std::endl;
	}


	if (!pinky_texture.loadFromFile("images/pinky.png")) {
		std::cout << "ERROR !! " << std::endl;
	}

	if (!Inky_texture.loadFromFile("images/inky.png")) {
		std::cout << "ERROR !! " << std::endl;
	}
	inky_cible.setTexture(inky_cible_texture);
	pinky_cible.setTexture(pinky_cible_texture);
	blinky_cible.setTexture(blinky_cible_texture);
	clyde_cible.setTexture(clyde_cible_texture);
	sf::Sprite target;
	sf::Texture target_texture;
	if (!target_texture.loadFromFile("images/target.png")) {
		std::cout << "prout" << std::endl;
	}
	target.setTexture(target_texture);

	sf::Sprite target2;
	sf::Texture target2_texture;
	if (!target2_texture.loadFromFile("images/target2.png")) {
		std::cout << "prout" << std::endl;
	}
	target2.setTexture(target2_texture);

	clyde.setTexture(Clyde_texture);
	inky.setTexture(Inky_texture);

	pinky.setTexture(pinky_texture);
	
	sf::Texture blinky_texture;
	if (!blinky_texture.loadFromFile("images/blinky.png"))
		std::cout << "ERROR !! " << std::endl;
	blinky.setTexture(blinky_texture);
		
	PacMan pacman_player;
	ghost Blinky("blinky", blinky_texture, frighten_texture);
	ghost Pinky("pinky", pinky_texture, frighten_texture);
	ghost Inky("inky", Inky_texture, frighten_texture);
	ghost Clyde("clyde", Clyde_texture, frighten_texture);
	vector <ghost> ghosts_ID;

	sf::RenderWindow window(sf::VideoMode(cells_weight * cell_size, cells_height * cell_size), "pacman");
	window.setFramerateLimit(170);
	sf::CircleShape pacman(16);
	pacman.setFillColor(sf::Color::Yellow);
	gamemap MAP;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ghosts_ID.clear();
		ghosts.clear();
		window.clear();
		MAP.draw_map(window);
		ghosts_ID.push_back(Blinky);
		ghosts_ID.push_back(Pinky);
		ghosts_ID.push_back(Inky);
		ghosts_ID.push_back(Clyde);

		pacman_player.pacman_move(pacman, MAP.getmap());
		pacman_player.dots_eaten(pacman, MAP.get_dots_positions());
		pacman_player.energizers_eaten(pacman, MAP.get_energizers_positions());
		MAP.update(pacman_player.get_dot_eaten(), pacman_player.get_energizer_eaten());
		Inky.ghost_move(inky_cible, blinky, inky, pacman, pacman_player.getDirection(), MAP.getmap(), pacman_player);
		Clyde.ghost_move(clyde_cible, blinky, clyde, pacman, pacman_player.getDirection(), MAP.getmap(), pacman_player);
		Blinky.ghost_move(blinky_cible, blinky, blinky, pacman, pacman_player.getDirection(), MAP.getmap(), pacman_player);
		Pinky.ghost_move(pinky_cible, blinky, pinky, pacman, pacman_player.getDirection(), MAP.getmap(), pacman_player);
		ghostManager.main(ghosts_ID);
		window.draw(pacman);

		window.draw(blinky);
		window.draw(pinky);
		window.draw(inky);
		window.draw(clyde);

		window.draw(inky_cible);
		window.draw(clyde_cible);
		window.draw(blinky_cible);
		window.draw(pinky_cible);


		MAP.display_blocks(window);
		window.display();

	}





	return 0;
}

