#include "ghost.h"

ghost::ghost(std::string Ghost_name, sf::Texture &ghost_texture, sf::Texture &frighten_texture)
: ghost_texture(ghost_texture), frighten_texture(frighten_texture){
	door_taken = false;
	this->ghost_texture = ghost_texture;
	frighten_mode = false;
	speed = 1;
	ghost_eaten = false;
	start = true;

	
	limit = std::numeric_limits<int>::max();
	distance_from_left = distance_from_right = distance_from_up = distance_from_down = limit;
	ghost_name = Ghost_name;
	direction = limit;
	if (ghost_name == "blinky")
		GHOST_ID = 1;
	if (ghost_name == "pinky")
		GHOST_ID = 2;
	if (ghost_name == "inky")
		GHOST_ID = 3;
	if (ghost_name == "clyde")
		GHOST_ID = 4;
	energizer_taken = immunized = false;

	switch (GHOST_ID) {
	case 1:
		px = door.x, py = door.y;
		door_taken = true;
		break;
	case 2:
		px = home_pinky.x, py = home_pinky.y;
		break;
	case 3:
		px = home_inky.x, py = home_inky.y;
		break;
	case 4:
		px = home_clyde.x, py = home_clyde.y;
		break;

	}
	backward_movement = false;
	scatter_mode = true;
	
}
bool ghost::getScatterMode() {
	return scatter_mode;
}
void ghost::fritghen_mode_behavior() {

	direction = backward_direction;

}
bool ghost::collision(const std::vector<std::string> mapPC) {

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
bool ghost::getGhostEaten() {
	return ghost_eaten;
}
bool ghost::interesection() {
	return(px % cell_size == 0 && py % cell_size == 0);
}
int ghost::get_shortest_way() { // check the tile where the ghost will be closer to its target
	if (distance_from_left != limit) {
		if (distance_from_left <= distance_from_right && distance_from_left <= distance_from_up && distance_from_left <= distance_from_down)
			return Left;
	}
	if (distance_from_right != limit) {
		if (distance_from_right <= distance_from_left && distance_from_right <= distance_from_up && distance_from_right <= distance_from_down)
			return Right;
	}
	if (distance_from_up != limit) {
		if (distance_from_up <= distance_from_left && distance_from_up <= distance_from_right && distance_from_up <= distance_from_down)
			return Up;
	}
	if (distance_from_down != limit) {
		if (distance_from_down <= distance_from_left && distance_from_down <= distance_from_up && distance_from_down <= distance_from_right)
			return Down;
	}
}
int ghost::getDirection() {
	return direction;
}
void ghost::setEatenTexture(sf::Texture &eyes) {
	eaten_texture = eyes;
}

void ghost::ghost_move(sf::Sprite& cible, sf::Sprite blinky, sf::Sprite &ghost, sf::CircleShape &pacman, int pacman_direction, std::vector <std::string> mapPC, PacMan& player) {

	energizer_taken = player.get_energizer_taken(); // 7
	if (energizer_taken) {
		if (door_taken)
			immunized = false;
		frighten_mode = true;
		horloge_frighten.restart();
	}
		

	if (frighten_mode) {
		energizer_duration = horloge_frighten.getElapsedTime();
		if (energizer_duration.asSeconds() >= frighten_mode_duration)
			frighten_mode = false;
	}

	if (!frighten_mode)
		immunized = false;

	if ((door_taken == false || ghost_eaten == true) || (frighten_mode && immunized == true))
		frighten_mode = false;

	
	


		if (got_home(ghost)) {
			door_taken = false;
			ghost_eaten = false;
			frighten_mode = false;
			backward_direction = 0;
			speed = 1;
		}

	



	if (!door_taken) {
		if (ghost.getPosition().x == door.x && ghost.getPosition().y == door.y) {
			door_taken = true;
			in_jail = false;
			
		}
		else {
			immunized = true;
			in_jail = true;
		}
			
		
	}

	

		if (frighten_mode && ghost_eaten != true) {
			ghost.setTexture(frighten_texture);
			frighten_move(mapPC, ghost);

		}

		else {
				ghost.setTexture(ghost_texture);
				backward_movement = false;
				normal_move(player, pacman, mapPC, ghost, blinky);

			
		}

		if (collisionWithPacman(ghost, pacman)) {
			if (frighten_mode) {
				ghost_eaten = true;

			}

		}

	

	distance_from_left = distance_from_right = distance_from_up = distance_from_down = limit;
	


	cible.setPosition(target);

}
bool ghost::got_home(sf::Sprite& ghost) {
	if (door_taken == false)
		return false;

	switch (GHOST_ID)
	{
	case 1:
		if (ghost.getPosition() == home_blinky)
			return true;
		break;
	case 2:
		if (ghost.getPosition() == home_pinky)
			return true;
		break;
	case 3:
		if (ghost.getPosition() == home_inky)
			return true;
		break;
	case 4:
		if (ghost.getPosition() == home_clyde)
			return true;
		break;

	}
	return false;
}
void ghost::getDirection(sf::Sprite& ghost, std::vector <std::string> mapPC) {
	// 1 = left, 2 = right, 3 = up, 4 = down
	sf::Vector2f original_position = sf::Vector2f(px, py);

	if (backward_direction != Left){
		px -= cell_size;

		ghost.setPosition(px, py);
		way_available = collision(mapPC);
		if (way_available) {

			if (frighten_mode && backward_direction != Left)
				Frighten_mode_direction.push_back(Left);

			else {
				test_direction = ghost.getPosition();
				distance_from_left = sqrt((target.x - test_direction.x) * (target.x - test_direction.x) + (target.y - test_direction.y) * (target.y - test_direction.y));
			}
			
		}
		px = original_position.x;

		ghost.setPosition(original_position);
	}


	if (backward_direction != Right){
		px += cell_size;
		ghost.setPosition(px, py);
		way_available = collision(mapPC);
		if (way_available) {
			if (frighten_mode && backward_direction != Right)
				Frighten_mode_direction.push_back(Right);

			else {
				test_direction = ghost.getPosition();
				distance_from_right = sqrt((target.x - test_direction.x) * (target.x - test_direction.x) + (target.y - test_direction.y) * (target.y - test_direction.y));
			}
		}
		px = original_position.x;
		ghost.setPosition(original_position);
	}


	if (backward_direction != Up){
		py -= cell_size;
		ghost.setPosition(px, py);
		way_available = collision(mapPC);
		if (way_available) {

			if (frighten_mode && backward_direction!=Up)
				Frighten_mode_direction.push_back(Up);
			else {
				test_direction = ghost.getPosition();
				distance_from_up = sqrt((target.x - test_direction.x) * (target.x - test_direction.x) + (target.y - test_direction.y) * (target.y - test_direction.y));
			}
		}
		py = original_position.y;
		ghost.setPosition(original_position);
	}
	if (backward_direction != Down){
		py += cell_size;
		ghost.setPosition(px, py);
		way_available = collision(mapPC);
		if (way_available) {

			if (frighten_mode && backward_direction != Down)
				Frighten_mode_direction.push_back(Down);

			else {
				test_direction = ghost.getPosition();
				distance_from_down = sqrt((target.x - test_direction.x) * (target.x - test_direction.x) + (target.y - test_direction.y) * (target.y - test_direction.y));
			}
		}
		py = original_position.y;
		ghost.setPosition(original_position);
	}

}

void ghost::getBackwardDirection() {
	if (direction == Left)
		backward_direction = Right;
	else if (direction == Right)
		backward_direction = Left;
	else if (direction == Up)
		backward_direction = Down;
	else if (direction == Down)
		backward_direction = Up;
}

void ghost::get_freeze_mode() {
	cout << ghost_name <<  frighten_mode << endl;
}
string ghost::get_name() {
	return ghost_name;
}
void ghost::normal_move(PacMan &player, CircleShape &pacman, std::vector <std::string> mapPC, sf::Sprite& ghost, sf::Sprite blinky) {
	

	if (scatter_mode)
		cout << "je suis en mode scatter en bien gui" << endl;
	else
		cout << "je suis en mode attaque hihi :)" << endl;

	update_target(player, blinky, ghost); // target of each ghost is updated here
	if (interesection()) { // the ghost is on an new intersection ? yes ? if so just make a new FREAKING DECISION !!!!!!
		getDirection(ghost, mapPC);
		direction = get_shortest_way();
	}
	getBackwardDirection(); // just a function to return the backward direction of the ghost so it doesn't choose that way as an option check up the getDirection function to understand :)

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

	ghost.setPosition(sf::Vector2f(px, py));
	if (px <= -cell_size + 1)
		px = cell_size * map_width - 1;
	else if (px >= cell_size * map_width - 1)
		px = -cell_size + 1;
	

}

void ghost::frighten_move(std::vector <std::string> mapPC, sf::Sprite& ghost) {

		frighten_mode_elapsed = timer_for_frighten_mode.getElapsedTime();
		// std::cout << "traceur numéro 1 " << std::endl;
		elapsed_speed_diminution = speed_diminution.getElapsedTime();
		//std::cout << "traceur numéro 2 " << std::endl;
		speed_decrease = 0.02;
		

		if (elapsed_speed_diminution.asSeconds() >= speed_decrease) {
			if (frighten_mode && elapsed_speed_diminution.asSeconds() >= speed_decrease)
				speed_diminution.restart();

			if (!backward_movement) {
				direction = backward_direction;
				backward_movement = true;
			}
			else if (interesection()) {
				getDirection(ghost, mapPC);
			
				direction = getRandomDirection(Frighten_mode_direction);
				Frighten_mode_direction.clear();
			}

			getBackwardDirection();
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

			ghost.setPosition(sf::Vector2f(px, py));
			// this little code's block just below handles the tunnel. 
			if (px <= -cell_size)
				px = cell_size * map_width;
			else if (px >= cell_size * map_width)
				px = -cell_size;


		}
}


void ghost::update_target(PacMan &pacman, sf::Sprite &blinky, sf::Sprite& ghost) {
	
	if (in_jail) {
		target = door;
	}
	else if (ghost_eaten) {
		if (px % 2 == 0 && py % 2 == 0)
			speed = 2;
		switch (GHOST_ID) {
		case 1:
			target = home_blinky;
			break;
		case 2:
			target = home_pinky;
			break;
		case 3:
			target = home_inky;
			break;
		case 4:
			target = home_clyde;
			break;
		}
	}
	else if (scatter_mode) {
		switch (GHOST_ID)
		{
		case 1:
			target = blinky_corner;
			break;
		case 2:
			target = pinky_corner;
			break;
		case 3:
			target = inky_corner;
			break;
		case 4:
			target = clyde_corner;
			break;

		}
	}
	else if (chase_mode) {
		switch (GHOST_ID)
		{
		case 1:
			target = pacman.get_position();
			break;
		case 2:
			pacman_direction = pacman.getDirection();
			switch (pacman_direction) {

			case Left:
				target = pacman.get_position() + sf::Vector2f(-3 * cell_size, 0);
				break;

			case Right:
				target = pacman.get_position() + sf::Vector2f(3 * cell_size, 0);
				break;

			case Up:
				target = pacman.get_position() + sf::Vector2f(0, -3 * cell_size) + sf::Vector2f(-3 * cell_size, 0);

				break;

			case Down:
				target = pacman.get_position() + sf::Vector2f(0, 3 * cell_size);
				break;
			}
			break;
		case 3:
			pacman_position = pacman.get_position();
			pacman_direction = pacman.getDirection();
			switch (pacman_direction) {

			case Left:
				pacman_position.x -= cell_size * 2;
				break;

			case Right:
				pacman_position.x += cell_size * 2;
				break;

			case Up:
				pacman_position.y -= cell_size * 2;
				break;

			case Down:
				pacman_position.y += cell_size * 2;
				break;
			}
			blinky_position = blinky.getPosition();
			vector_to_target = pacman_position - blinky_position;

			// Double the lenght of the vector
			extended_vector = 2.0f * vector_to_target;
			// the target position is the tile on which end the extended vector
			target = blinky_position + extended_vector;
		
			break;
		case 4:
			pacman_position = pacman.get_position();
			int distance_limit = 185;
			sf::Vector2f ghost_position = ghost.getPosition();
			float distance = sqrt((pacman_position.x - ghost_position.x) * (pacman_position.x - ghost_position.x) + (pacman_position.y - ghost_position.y) * (pacman_position.y - ghost_position.y));
			if (distance > distance_limit)
				target = pacman_position;
			else
				target = scatter_mode_home;
			break;
		}
	}
}
int ghost::getRandomDirection(vector<int> &Frighten_mode_direction) {
	if (Frighten_mode_direction.size() == 1)
		return Frighten_mode_direction.at(0);

	std::random_device rd;
	std::mt19937 gen(rd());
	// Generate a random index within the range of the vector
	std::uniform_int_distribution<> distribution(1, Frighten_mode_direction.size() - 1);
	int randomIndex = distribution(gen);

	// Access the randomly chosen element
	int randomElement = Frighten_mode_direction[randomIndex];
	return randomElement;
}

bool ghost::collisionWithPacman(sf::Sprite& ghost, CircleShape& pacman) {
	sf::Vector2f ghost_position = ghost.getPosition();
	float distance = sqrt((pacman.getPosition().x - ghost_position.x) * (pacman.getPosition().x - ghost_position.x) + (pacman.getPosition().y - ghost_position.y) * (pacman.getPosition().y - ghost_position.y));
	if (distance < 5)
		return true;
	return false;
}