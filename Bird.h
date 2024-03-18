#pragma once 
#include <SFML/Graphics.hpp>  
class Bird
{
private:
	sf::Texture textures[2];
	const int gravity = 10; // The gravity
	const int flap_speed; // The flap speed
	float velocity_y = 0; // The y velocity
	int anim_counter; // The animation counter
	int texture_switch; // The texture switch
	bool should_fly; // Whether the bird should fly
public:
	sf::Sprite bird_sprite; // The bird sprite
	Bird(); // Constructor
	void setShouldFly(bool fly); // Set whether the bird should fly
	void flapBird(sf::Time&dt); // Flap the bird
	void resetBirdPosition(); // Reset the bird position
	void update(sf::Time& dt); // Update the bird
	float getRightBound(); // Get the right bound of the bird

};

