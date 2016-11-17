#include "Game.h"
#include "GeneralEnum.h"
#include "Main.h"

Game::Game(){
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

Game::~Game(){
	window.close();
}

void Game::init()
{
	window.create(sf::VideoMode(800, 600), "Why doesnt the block draw");
}

int Game::test2() {

	std::string blockTexturePath = TACD_DIRECTORY;
	blockTexturePath += "IMG Files/blocks.png";

	//std::string boardOutlinePath = TACD_DIRECTORY;
	//boardOutlinePath += "1p.png";

	sf::Texture blockTexture;
	blockTexture.setRepeated(true);

	//sf::Texture boardOutlineTexture;
	//sf::Sprite boardOutline;
	//boardOutline.setTexture(boardOutlineTexture);

	sf::Sprite sprite_block1;
	sf::Sprite betaSprite;
	betaSprite.setTexture(blockTexture, true);

	if (!blockTexture.loadFromFile(blockTexturePath))
	{
		// error...
		printf("%s\n", "What have I done : Texture Failure");
		return -1;
	}
	else
	{
		printf("%s\n", "Evreything seems good : Texture Success2");
		sprite_block1.setTexture(blockTexture);
		//sprite_block1.setTextureRect(sf::IntRect(322+TILE_SIZE *2, 166, TILE_SIZE, TILE_SIZE));
		//sprite_block1.scale(sf::Vector2f(3.f, 3.f)); // factor relative to the current scale
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// inside the main loop, between window.clear() and window.display()
		//window.draw(sprite_block1);
		window.draw(sprite_block1);
		//sprite_block1.move(TILE_SIZE, 0);
		//window.draw(sprite_block1);


		//sprite_block1.scale(sf::Vector2f(1.5f, 3.f)); // factor relative to the current scale
		window.display();
	}

	return 0;
}

void Game::run() {

	//Board b1;
	//Board b2;

	//Board board;
	ControllerCommand input;
	int frame = 0;
	int second = 0;
	int minute = 0;
	int milisecond = 0;
	int MS_PER_FRAME = 16;//miliseconds per frame
						  //clock_t FPS = 60;
	clock_t lastTime = clock();
	clock_t current = clock();
	clock_t elapsed = current - lastTime;
	while (true)
	{
		/*Manage Time Beta*/
		if (frame == 32767) {
			frame = 0;
		}
		else {
			frame++;
			milisecond++;

			if (milisecond >= 60)
			{
				second++;
				milisecond = 0;
			}

			if (second >= 60)
			{
				minute++;
				second = 0;
			}
		}

		//processInput();

		//current = clock();
		//elapsed = current - lastTime;
		current = clock();
		input = ControllerCommand::noInput;
		if (_kbhit())
		{
			b1.handleInput(getInput());
		}

		printf("%d:%d  Frame: %d\n", minute, second, frame);
		printf("Average FPS: %3.2f        \nNB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n", CalcAverageTick((int)elapsed), (float)elapsed * 60, elapsed, (float)CLOCKS_PER_SEC);
		b1.run();
		b1.display();
		//lastTime = current;
		elapsed = clock() - current;

		if (MS_PER_FRAME - elapsed > 0)
		{
			fflush(stdout);
			Sleep(MS_PER_FRAME - elapsed);
		}

		//system("cmd /c cls");
		gotoxy(0, 0);
	}

}

void Game::draw()
{
}

void Game::display()
{
}
