#include "SFML.h"

int SFML_Window()
{
    sf::Window window(sf::VideoMode(800, 600), "TACD");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}


int SFML_TestWindow()
{


	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");

	std::string blockTexturePath = TACD_DIRECTORY;
	blockTexturePath += "TetrisAttackBeta.png";

	std::string boardOutlinePath = TACD_DIRECTORY;
	boardOutlinePath += "1p.png";

	sf::Texture blockTexture;
	blockTexture.setRepeated(true);

	sf::Texture boardOutlineTexture;
	sf::Sprite boardOutline;
	boardOutline.setTexture(boardOutlineTexture);

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
		printf("%s\n", "Evreything seems good : Texture Success");
		sprite_block1.setTexture(blockTexture);
		//sprite_block1.
		sprite_block1.setTextureRect(sf::IntRect(322+TILE_SIZE *2, 166, TILE_SIZE, TILE_SIZE));
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

int SFML_DrawWindow()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		// window.draw(...);



		// end the current frame
		window.display();
	}

	return 0;
}

int SpriteTest() {
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Sprite Test");

	sf::Event event;

	sf::Texture texture;
	texture.loadFromFile("Y:/TACD C++/TetrisAttackBeta.png");

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}
	return 0;
}


/*
SFML_DYNAMiC is used now due to not having the dlls installed

*/


//string TACD_DIRECTORY = "Y:\TACD C++";

sf::Sprite SFML_Texture() {
	
	std::string blockTexturePath = TACD_DIRECTORY;
		blockTexturePath+= "TetrisAttackBeta.png";
	sf::Texture blockTexture;

	if (!blockTexture.loadFromFile(blockTexturePath))
	{
		// error...
		printf("%s\n", "What have I done : Texture");
	}
	else
	{
		printf("%s\n", "Evreything seems good : Texture");
	}

	blockTexture.setRepeated(true);


	sf::Sprite sprite_block1;
	sf::Sprite sprite_block2;
	sf::Sprite sprite_block3;
	sf::Sprite sprite_block4;
	sf::Sprite sprite_block5;


	sprite_block1.setTextureRect(sf::IntRect(166, 322, TILE_SIZE, TILE_SIZE));
	return sprite_block1;

	/*
	// create an empty 200x200 texture
	if (!texture.create(200, 200))
	{
		// error...
	}
	*/

}