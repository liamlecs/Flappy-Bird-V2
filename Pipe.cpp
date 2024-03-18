#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(int y_pos) { // Constructor
	sprite_down.setTexture(texture_down); // Set the down pipe sprite to use the down pipe texture
	sprite_up.setTexture(texture_up); // Set the up pipe sprite to use the up pipe texture

	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the down pipe sprite
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the up pipe sprite
	 
	sprite_up.setPosition(WIN_WIDTH, y_pos); // Set the position of the up pipe
	sprite_down.setPosition(WIN_WIDTH, y_pos - pipe_distance - sprite_down.getGlobalBounds().height); // Set the position of the down pipe
} 

void Pipe::update(sf::Time& dt) {

	sprite_up.move(-move_speed*dt.asSeconds(), 0); // Move the up pipe
	sprite_down.move(-move_speed*dt.asSeconds(), 0); // Move the down pipe

}

void Pipe::loadTextures() {
	texture_down.loadFromFile("assets/pipedown.png"); // Load the down pipe texture
	texture_up.loadFromFile("assets/pipe.png"); // Load the up pipe texture
}

float Pipe::getRightBound() {
	return sprite_down.getGlobalBounds().left+ sprite_down.getGlobalBounds().width; // Return the right bound of the down pipe
}

sf::Texture Pipe::texture_down, Pipe::texture_up; // The pipe textures
int Pipe::pipe_distance = 170; // The distance between the pipes
int Pipe::move_speed = 400;	// The speed at which the pipes move