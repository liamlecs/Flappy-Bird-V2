#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"

int main() {
	sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Flappy Bird"); // Create a window
	Game game(win); // Create a game object
	game.StartGameLoop(); // This is the main game loop
	return 0; // Return 0
}