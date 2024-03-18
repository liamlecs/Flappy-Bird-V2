#pragma once
#include <SFML/Graphics.hpp>
class Pipe
{
private:
	static sf::Texture texture_down, texture_up; // The pipe textures
	static int pipe_distance, move_speed; // The distance between the pipes and the speed at which the pipes move

public:
	Pipe(int y_pos); // Constructor
	sf::Sprite sprite_up, sprite_down; // The pipe sprites
	static void loadTextures(); // Load the textures
	void update(sf::Time& dt); // Update the pipes
	float getRightBound(); // Get the right bound of the pipes
};

