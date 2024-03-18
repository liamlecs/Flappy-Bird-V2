#include "Game.h"
#include "Globals.h"
#include <sstream>

Game::Game(sf::RenderWindow& window) : win(window),  
is_enter_pressed(false), 
run_game(true), 
start_monitoring(false),
pipe_counter(71),
pipe_spawn_time(70),
score(0)
{ // Constructor

	win.setFramerateLimit(60); // Set the frame rate limit

	bg_texture.loadFromFile("assets/bg.png"); // Load the background texture
	bg_sprite.setTexture(bg_texture); // Set the background sprite to use the background texture
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the background sprite
	bg_sprite.setPosition(0.f, -100.f); // Set the position of the background sprite

	ground_texture.loadFromFile("assets/ground.png"); // Load the ground texture

	ground_sprite1.setTexture(ground_texture); // Set the ground sprite to use the ground texture
	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the ground sprite

	ground_sprite2.setTexture(ground_texture); // Set the ground sprite to use the ground texture
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR); // Scale the ground sprite

	ground_sprite1.setPosition(0, 578); // Set the position of the ground sprite
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578); // Set the position of the ground sprite

	title_texture.loadFromFile("assets/title.png"); // Load the title texture
	title_sprite.setTexture(title_texture); // Set the title sprite to use the title texture
	title_sprite.setScale(0.6, 0.6); // Scale the title sprite
	title_sprite.setPosition(108, 100); // Set the position of the title sprite

	play_button_texture.loadFromFile("assets/PlayButton.png"); // Load the play button texture
	play_button_sprite.setTexture(play_button_texture); // Set the play button sprite to use the play button texture
	play_button_sprite.setScale(0.8, 0.8); // Scale the play button sprite
	play_button_sprite.setPosition(183.5, 235); // Set the position of the play button sprite

	game_over_texture.loadFromFile("assets/gameover.png"); // Load the game over texture
	game_over_sprite.setTexture(game_over_texture); // Set the game over sprite to use the game over texture
	game_over_sprite.setScale(0.8, 0.8); // Scale the game over sprite
	// game_over_sprite.setPosition(160, 100);
	game_over_sprite.setPosition(-1000, -1000); // Set the position of the game over sprite intialy off the screen

	font.loadFromFile("assets/FlappyFont.ttf"); // Load the font
	restart_text.setFont(font); // Set the font of the restart text
	restart_text.setCharacterSize(48); // Set the character size of the restart text
	restart_text.setFillColor(sf::Color::White); // Set the fill color of the restart text
	restart_text.setPosition(127, 650); // Set the position of the restart text
	restart_text.setString("Restart Game!"); // Set the string of the restart text

	score_text.setFont(font); // Set the font of the restart text
	score_text.setCharacterSize(24); // Set the character size of the restart text
	score_text.setFillColor(sf::Color::White); // Set the fill color of the restart text
	score_text.setPosition(-1000, -1000); // Set the position of the restart text
	score_text.setString("Score: 0"); // Set the string of the restart text

	Pipe::loadTextures(); // Load the pipe textures

	dead_buffer.loadFromFile("assets/sfx/dead.wav"); // Load the dead sound buffer
	flap_buffer.loadFromFile("assets/sfx/flap.wav"); // Load the flap sound buffer
	score_buffer.loadFromFile("assets/sfx/score.wav"); // Load the score sound buffer

	dead_sound.setBuffer(dead_buffer); // Set the dead sound buffer
	flap_sound.setBuffer(flap_buffer); // Set the flap sound buffer
	score_sound.setBuffer(score_buffer); // Set the score sound buffer

}
void Game::doProcessing(sf::Time& dt) {
	if (is_enter_pressed){ // If the enter key is pressed
		moveGround(dt); // Move the ground
		if (pipe_counter>pipe_spawn_time) { // If the pipe counter is greater than the pipe spawn time
			pipes.push_back(Pipe(dist(rd))); // Add a new pipe to the vector
			pipe_counter = 0; // Reset the pipe counter
		}
		pipe_counter++; // Increment the pipe counter

		for (int i = 0; i < pipes.size(); ++i) { // For each pipe
			pipes[i].update(dt); // Update the pipe
			if (pipes[i].getRightBound() < 0) { // If the pipe is off the screen
				pipes.erase(pipes.begin() + i); // Erase the pipe
			}
		}
		checkCollisions(); // Check for collisions
		checkScore(); // Check the score
	}
	bird.update(dt); // Update the bird
}
void Game::StartGameLoop() {
	sf::Clock clock; // Create a clock to keep track of time
	while (win.isOpen()) { // While the window is open

		sf::Time dt= clock.restart(); // restart returns the time since the last restart
		sf::Event event; // Create an event object
		while (win.pollEvent(event)) { // While there are events to process
			if (event.type == sf::Event::Closed) { // If the event is a close event
				win.close(); // Close the window
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !is_enter_pressed) { // If the event is a mouse button pressed event
				if (play_button_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // If the play button is clicked
					is_enter_pressed = true; // Set the enter pressed variable to true
					bird.setShouldFly(true); // Set the bird to fly 
					play_button_sprite.setPosition(-1000, -1000); // Set the position of the play button sprite off the screen
					title_sprite.setPosition(-1000, -1000); // Set the position of the title sprite off the screen
					score_text.setPosition(15, 15); // Set the position of the score text
				}
			}
			if (event.type == sf::Event::KeyPressed && run_game) { // If the event is a key pressed event
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed) { // If the enter key is pressed and the enter key is not already pressed
					is_enter_pressed = true; // Set the enter pressed variable to true
					bird.setShouldFly(true); // Set the bird to fly
					play_button_sprite.setPosition(-1000, -1000); // Set the position of the play button sprite off the screen
					title_sprite.setPosition(-1000, -1000); // Set the position of the title sprite off the screen
					score_text.setPosition(15, 15); // Set the position of the score text
				}
				if (event.key.code == sf::Keyboard::Space && is_enter_pressed) { // If the space key is pressed and the enter key is pressed
					bird.flapBird(dt); // Flap the bird
					flap_sound.play(); // Play the flap sound
				}
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game) { // If the event is a mouse button pressed event and the game is not running
				if (restart_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) { // If the restart text is clicked
					title_sprite.setPosition(108, 100);	// Set the position of the title sprite
					play_button_sprite.setPosition(183.5, 235); // Set the position of the play button sprite
					score_text.setPosition(-1000, -1000); // Set the position of the score text off the screen
					restartGame(); // Restart the game
				}
			}
			else if (event.type == sf::Event::KeyPressed && !run_game) { // If the event is a key pressed event and the game is not running
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed) { // If the enter key is pressed and the enter key is not already pressed
					title_sprite.setPosition(108, 100); // Set the position of the title sprite
					play_button_sprite.setPosition(183.5, 235); // Set the position of the play button sprite
					score_text.setPosition(-1000, -1000); // Set the position of the score text off the screen
					restartGame(); // Restart the game
				}
			}
		}

		win.clear(); // Clear the window
		doProcessing(dt); // Process the game
		draw(); // Draw the game
		win.display(); // Display the window
	}
}
void Game::checkCollisions() { // Check for collisions
	if (pipes.size() > 0) { // If there are pipes
		if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) || // If the bird intersects with the pipes
			pipes[0].sprite_up.getGlobalBounds().intersects(bird.bird_sprite.getGlobalBounds()) || // If the bird intersects with the pipes
			bird.bird_sprite.getGlobalBounds().top >= 540) { // If the bird is below the ground
			is_enter_pressed = false; // Set the enter pressed variable to false
			run_game = false; // Set the run game variable to false
			dead_sound.play(); // Play the dead sound
			game_over_sprite.setPosition(115, 100); // Set the position of the game over sprite
		}
	}
}

void Game::checkScore() { // Check the score
	if (pipes.size() > 0) { // If there are pipes
		if (!start_monitoring) { // If the game has not started monitoring the score
			if (bird.bird_sprite.getGlobalBounds().left > pipes[0].sprite_down.getGlobalBounds().left && bird.getRightBound() < pipes[0].getRightBound()) { 
				// If the bird is between the pipes
				start_monitoring = true; // Set the start monitoring variable to true
			}
		}
		else {
			if (bird.bird_sprite.getGlobalBounds().left >= pipes[0].getRightBound()) { // If the bird has passed the pipes
				score++; // Increment the score
				score_text.setString("Score: " + toString(score)); // Set the score text
				start_monitoring = false; // Set the start monitoring variable to false
				score_sound.play(); // Play the score sound
			}
		}
	}
}
void Game::draw() { // Draw the game

	win.draw(bg_sprite); // Draw the background
	win.draw(title_sprite); // Draw the title
	win.draw(play_button_sprite); // Draw the play button
	for (Pipe& pipe : pipes) {
		win.draw(pipe.sprite_down); // Draw the pipe
		win.draw(pipe.sprite_up); // Draw the pipe
	}
	win.draw(ground_sprite1); // Draw the ground
	win.draw(ground_sprite2); // Draw the ground
	win.draw(bird.bird_sprite); // Draw the bird
	win.draw(score_text); // Draw the score
	win.draw(game_over_sprite); // Draw the game over

	if (!run_game) { // If the game is not running
		win.draw(restart_text); // Draw the restart text
	}
}

void Game::moveGround(sf::Time& dt) { // Move the ground
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f); // Move the ground
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f); // Move the ground

	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0) { // If the ground is off the screen
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left+ ground_sprite2.getGlobalBounds().width, 578); 
		// Move the ground to the right of the other ground
	} 
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0) { // If the ground is off the screen
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 578);
		// Move the ground to the right of the other ground
	}
}

void Game::restartGame() {	// Restart the game
	bird.resetBirdPosition(); // Reset the bird position
	bird.setShouldFly(false); // Set the bird to not fly
	run_game = true; // Set the run game variable to true
	is_enter_pressed = false; // Set the enter pressed variable to false
	pipe_counter = 71; // Reset the pipe counter
	pipes.clear(); // Clear the pipes
	score = 0; // Reset the score
	score_text.setString("Score: 0"); // Set the score text
	game_over_sprite.setPosition(-1000, -1000); // Set the position of the game over sprite off the screen
}

std::string Game::toString(int num) { // Convert an integer to a string
	std::stringstream ss; // Create a stringstream
	ss << num; // Add the integer to the stream
	return ss.str(); // Return the string
}

// Game.cpp Documentation
/* The constructor initializes the game's properties such as the background, ground, title, play button, game over, bird, pipes, 
and the font and sound buffers and sounds.
The doProcessing method processes the game by moving the ground, adding new pipes, updating the pipes, checking for collisions, and checking the score.
The StartGameLoop method is the main game loop that processes the game and draws the game.
The checkCollisions method checks for collisions between the bird and the pipes and the ground.
The checkScore method checks the score by monitoring the bird's position and the pipes.
The draw method draws the game by drawing the background, title, play button, pipes, ground, bird, score, and game over.
The moveGround method moves the ground to the left at a constant speed.
The restartGame method restarts the game by resetting the bird's position, clearing the pipes, and resetting the score.
The toString method converts an integer to a string.
*/