#include "GhostManagement.h"

void GhostManagement::main(std::vector<ghost> &ghostVector) {
	eslapsed_time = timer.getElapsedTime();
	for (ghost& Ghost : ghostVector) {
		eslapsed_time = timer.getElapsedTime();
		if (Ghost.getScatterMode()) {
			if (eslapsed_time.asSeconds() >= 20) {
				Ghost.scatter_mode = false;

				timer.restart();
				Ghost.chase_mode = true;
			}

		}
		else {
			if (eslapsed_time.asSeconds() >= 7) {
				Ghost.chase_mode = false;

				timer.restart();
				Ghost.scatter_mode = true;
			}
			else
				Ghost.chase_mode = true;
		}


	}










	
	
}