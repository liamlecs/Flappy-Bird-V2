#include "Bird.h"
#include "Globals.h"

Bird::Bird():
	gravity(15), // The gravity
	flap_speed(300), // The flap speed
	velocity_y(0), // The y velocity
	anim_counter(0), // The animation counter
	texture_switch(1), // The texture switch
	should_fly(false) // Whether the bird should fly

{
	textures[0].loadFromFile("assets/birddown.png"); // Load the bird down texture
	textures[1].loadFromFile("assets/birdup.png"); // Load the bird up texture

	bird_sprite.setTexture(textures[0]); // Set the bird sprite to use the bird down texture
	bird_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the bird sprite
	
	resetBirdPosition(); // Reset the bird position
}
void Bird::update(sf::Time& dt) { // Update the bird
	if (bird_sprite.getGlobalBounds().top < 548 && should_fly) { // If the bird is above the ground and should fly
		if (anim_counter == 5) { // If the animation counter is 5
			bird_sprite.setTexture(textures[texture_switch]); // Set the bird sprite to use the bird texture
			if (texture_switch) { // If the texture switch is true
				texture_switch = 0; // Set the texture switch to false
			}
			else { // If the texture switch is false
				texture_switch = 1; // Set the texture switch to true
			}
			anim_counter = 0; // Reset the animation counter
		}
		anim_counter++; // Increment the animation counter
		velocity_y += gravity*dt.asSeconds(); // Add the gravity to the y velocity
		bird_sprite.move(0, velocity_y); // Move the bird
	}

	if (bird_sprite.getGlobalBounds().top < 0) { // If the bird is above the top of the window
		bird_sprite.setPosition(100,0); // Set the position of the bird
	}
}

void Bird::flapBird(sf::Time& dt) { // Flap the bird
	velocity_y = -flap_speed*dt.asSeconds(); // Set the y velocity to the flap speed

}

float Bird::getRightBound() { // Get the right bound of the bird
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width; // Return the right bound of the bird
}

void Bird::resetBirdPosition() { // Reset the bird position
	bird_sprite.setPosition(100, 50); // Set the position of the bird
	velocity_y = 0; // Reset the y velocity
}

void Bird::setShouldFly(bool should_fly) { // Set whether the bird should fly

	this->should_fly = should_fly; // Set the should fly variable
}
