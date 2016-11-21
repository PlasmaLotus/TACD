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
	window.create(sf::VideoMode(800, 600), "TACD");


	std::string blockTexturePath = TACD_DIRECTORY;
	blockTexturePath += "IMG Files/blocksUpdated.png";
	std::string boardFramePath = TACD_DIRECTORY;
	boardFramePath += "1p.png";
	std::string cursorPath = TACD_DIRECTORY;
	cursorPath += "IMG Files/cursor.png";

	blockTexture.setRepeated(true);

	if (!blockTexture.loadFromFile(blockTexturePath))
	{
		// error...
		printf("%s\n", "What have I done : Block Texture Failure");
		//return -1;
	}
	else if (!boardFrameTexture.loadFromFile(boardFramePath))
	{
		// error...
		printf("%s\n", "What Happened : BoardTexture fail , TestDisplay");
		//return -1;
	}
	else if (!cursorTexture.loadFromFile(cursorPath))
	{
		printf("%s\n", "What Happened : Cursor Texture fail");
	}
	else
	{
		printf("All Texture Loaded\n");
		boardFrameSprite.setTexture(boardFrameTexture);
		//blockSprite1.setTextureRect();
		
		for (int i = 0; i < NB_BLOCKS_SPRITES; i++)
		{
			blockSprites[i].setTexture(blockTexture);
			blockSprites[i].setTextureRect(sf::IntRect(i*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
			//blockSprites[i].setTextureRect()
		}

		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				boardSprites[i][j].setTexture(blockTexture);
			}
		}
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			bufferRowSprites[j].setTexture(blockTexture);
		}

	}
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
	/*
	clock_t lastTime = clock();
	clock_t current = clock();
	clock_t elapsed = current - lastTime;
	*/
	sf::Clock current;
	sf::Time elapsed = current.restart();
	while (window.isOpen())
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
		/*~Manage Time Beta*/

		//processInput();

		//current = clock();
		//elapsed = current - lastTime;
		current.restart();
		input = ControllerCommand::noInput;
		///get input here
		/*
		if (_kbhit())
		{
			b1.handleInput(getInput());
		}
		*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				//exit(EXIT_SUCCESS);
			}
		}

		//blockSprites[1].setColor(sf::Color::Red);

		window.clear();

		//window.draw(boardFrameSprite);
		//window.draw(blockSprites[1]);

		printf("%d:%d  Frame: %d\n", minute, second, frame);
		printf("Average FPS: %3.2f        \nNB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n", CalcAverageTick((int)elapsed.asMilliseconds()), (float)elapsed.asMilliseconds() * 60, elapsed, (float)CLOCKS_PER_SEC);
		b1.run();
		//testDisplay(b1);
		draw();
		b1.display();
		display();
		//lastTime = current;
		elapsed = current.getElapsedTime();

		if (MS_PER_FRAME - elapsed.asMilliseconds() > 0)
		{
			fflush(stdout);
			Sleep(MS_PER_FRAME - elapsed.asMilliseconds());
		}

		//system("cmd /c cls");
		gotoxy(0, 0);
	}

}

sf::Sprite Game::spriteColor(BlockColor color) {
	switch (color) 
	{
	case BlockColor::blue: return blockSprites[3]; break;
	case BlockColor::none :
	default:
		return blockSprites[7]; break;
	}
}

int Game::spriteColorInt(BlockColor color) {
	switch (color)
	{
	case red: return 0;
	case green: return 1;
	case yellow: return 2;
	case blue: return 3;
	case purple: return 4;
	case pink: return 5;
	//case exclam: return 6;
	case none: return 7;
	default:
		return 7;
	}
}


void Game::setBoardTextures(Board board) {
	/*Set the texture of the blocks in the stack */

	int textureIndexX;
	int textureIndexY;

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			textureIndexX = 7*TILE_SIZE;
			textureIndexY = 0;

			textureIndexX = spriteColorInt(board.tiles[i][j].block.color)*TILE_SIZE;
			textureIndexY = 0;

			if (board.tiles[i][j].block.matching)// || board.tiles[i][j].block.clearing)
			{
				textureIndexY += TILE_SIZE;
			}
			if (board.tiles[i][j].isBlock())
			{
				//if (i == board.TOP_ROW)//smaller rectangle for the tip
					//boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY + board.bufferRowOffset *2, TILE_SIZE, TILE_SIZE - board.bufferRowOffset*2));
				//else
					boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				//boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
			}
			else if (board.tiles[i][j].isAir())
			{
				boardSprites[i][j].setTextureRect(sf::IntRect(0,0,0,0));
			}
			else if (board.tiles[i][j].isGarbage()) 
			{
				//TODO: code garbage blocks
			}
			//window.draw(spriteColor(b1.tiles[i][j].block.color));
		}
	}
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		/*Creates a block with a height of the bufferRowOffset*/
		bufferRowSprites[j].setTextureRect(sf::IntRect(
			spriteColorInt(board.bufferRow[j].block.color)*TILE_SIZE, 0, TILE_SIZE, board.bufferRowOffset*2));//16 same as tileSize
		//window.draw(spriteColor(b1.tiles[i][j].block.color));
		bufferRowSprites[j].setColor(sf::Color(255,255,255,64));
	}

	cursorSprite.setTexture(cursorTexture);
}
void Game::setCursorPosition(Board board) {
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;
	int spriteDisplaySize = 32;

	cursorTime++;
	//int size = cursorTexture.ge
	cursorSprite.setPosition(sf::Vector2f(displayX + board.cursor.column * spriteDisplaySize - 6, displayY- board.bufferRowOffset*(2) - board.cursor.row * spriteDisplaySize - 6));
	if (cursorTime % 60 == 0)
	{
		cursorTime = 0;
		cursorSprite.setTextureRect(sf::IntRect(0,0,75,44));
	}
	else if (cursorTime % 30 == 0) 
	{
		cursorSprite.setTextureRect(sf::IntRect(0,45, 75, 44));
	}
	
}
void Game::setBlockPositions(Board board) {
	/*Sets the position of all blocks sprites on the board;*/

	
	int bufferRowOffset = board.bufferRowOffset * (2);//spriteScale;

	int spriteDisplaySize = 32;
	int displayYTop = 43;
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;

	int vectorX;
	int vectorY;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			vectorX = displayX + spriteDisplaySize*j;
			vectorY = displayY - bufferRowOffset - spriteDisplaySize*i;
			/*
			if (i == board.TOP_ROW)
			{
				//Only display part of the top row blocks
				vectorY += board.bufferRowOffset * 2;
			}
			*/
			if (board.tiles[i][j].block.state == BlockState::swapping)
			{
				switch (board.tiles[i][j].block.stateExtra)
				{
				case swappingLeft:
				{
					vectorX -= board.tiles[i][j].swappingCounter;
					break;
				}
				case swappingRight:
				{
					vectorX += board.tiles[i][j].swappingCounter;
					break;
				}
				default: break;
				}
			}
			
			boardSprites[i][j].setPosition(sf::Vector2f(vectorX, vectorY));
			/*TODO: set position when blocks are swapping*/
		}
	}
	/*BufferRow*/
	vectorX = displayX + spriteDisplaySize*BOARD_HEIGHT;
	vectorY = displayY + spriteDisplaySize - board.bufferRowOffset * 2;
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		vectorX = displayX + spriteDisplaySize*j;
		//vectorX = displayX + spriteDisplaySize*j;
		//vectorY = bufferRowOffset + displayY + BOARD_HEIGHT*spriteDisplaySize;

		bufferRowSprites[j].setPosition(sf::Vector2f(vectorX, vectorY));

	}


}
void Game::drawBoard1(int row, int column) {

	for (int i = 0; i < b1.boardHeight; i++)
	{
		for (int j = 0; j < b1.boardSize; j++)
		{
			window.draw(spriteColor(b1.tiles[i][j].block.color));
		}
	}

}

void Game::draw()
{

	int bufferRowOffset = b1.bufferRowOffset;
	int spriteDisplaySize = 32;
	int displayRow = 427;
	int displayCol = 58;

	
	window.draw(boardFrameSprite);
	//boardFrameSprite.setColor(sf::Color(255, 255, 255, 128));
	setBoardTextures(b1);
	setBlockPositions(b1);
	setCursorPosition(b1);

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			//boardSprites[i][j].setScale(sf::Vector2f(2.f, 2.f));
			window.draw(boardSprites[i][j]);
		}
	}

	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		//bufferRowSprites[j].setScale(sf::Vector2f(2.f, 2.f));
		window.draw(bufferRowSprites[j]);
	}
	/*calls the .draw() function on all sprites*/
	/*
	for (int i = 0; i < NB_BLOCKS_SPRITES; i++)
	{
		blockSprites[i].setScale(sf::Vector2f(2.f, 2.f));
	}
	*/
	//drawBoard1(427, 58);
	
	
	window.draw(cursorSprite);
}

void Game::display()
{
	window.display();
}


void Game::_testDisplay(Board &board) {


}

void Game::testDisplay(Board &board) {
	/*
	std::string boardFramePath = TACD_DIRECTORY;
	boardFramePath+= "1p.png";
	//sf::Vector2f(1.f, 2.f);
	sf::Texture boardFrameTexture;
	sf::Sprite boardFrameSprite;
	if (!boardFrameTexture.loadFromFile(boardFramePath))
	{
		// error...
		printf("%s\n", "What Happened : BoardTexture fail , TestDisplay");
		//return -1;
	}
	else 
	{
		printf("ok\n");
	}
	
	boardFrameSprite.setTexture(boardFrameTexture);
	boardFrameSprite.setPosition(10, 20);
	*/

	//while (window.isOpen())
	//{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				//exit(EXIT_SUCCESS);
			}
		}

		//blockSprites[1].setColor(sf::Color::Red);

		window.clear();

		window.draw(boardFrameSprite);
		window.draw(blockSprites[1]);

		//window.display();
	//}
}