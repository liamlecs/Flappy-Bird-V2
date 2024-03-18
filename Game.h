#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bird.h"
#include <vector>
#include "Pipe.h"
#include <random>

class Game {
private:
	sf::Texture bg_texture; // The background texture
	sf::Texture ground_texture; // The ground texture
	sf::Sprite bg_sprite, ground_sprite1, ground_sprite2; // The background and ground sprites
	sf::Texture title_texture; // The title texture
	sf::Texture play_button_texture; // The title and play button textures
	sf::Sprite title_sprite; // The title sprite
	sf::Sprite play_button_sprite; // The title and play button sprites
	sf::Texture game_over_texture; // The game over texture
	sf::Sprite game_over_sprite; // The game over sprite
	Bird bird; // The bird object
	bool is_enter_pressed, run_game, start_monitoring; 
	// Whether the enter key is pressed, whether the game is running and whether the game has started monitoring the score
	const int move_speed = 270; // The speed at which the ground moves
	void draw(); // Draw the game
	void moveGround(sf::Time& dt); // Move the ground
	void doProcessing(sf::Time& dt); // Process the game
	void checkCollisions(); // Check for collisions
	void restartGame(); // Restart the game
	void checkScore(); // Check the score
	std::string toString(int num); // Convert an integer to a string
	int pipe_counter, pipe_spawn_time, score; // The pipe counter, pipe spawn time and the score
	std::vector<Pipe> pipes; // The vector of pipes
	std::random_device rd; // Random device
	std::uniform_int_distribution<int> dist{ 250,550 }; // Uniform distribution
	sf::Font font; // The font
	sf::Text restart_text; // The restart text
	sf::Text score_text; // The score text
	sf::SoundBuffer dead_buffer; // The dead sound buffer
	sf::SoundBuffer flap_buffer; // The flap sound buffer
	sf::SoundBuffer score_buffer; // The score sound buffer
	sf::Sound dead_sound; // The dead sound
	sf::Sound flap_sound; // The flap sound
	sf::Sound score_sound; // The score sound
public:
	Game(sf::RenderWindow& window); // Constructor
	sf::RenderWindow& win; // Reference to the window
	void StartGameLoop(); // The main game loop
};