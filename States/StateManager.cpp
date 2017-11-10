#include "StateManager.h"

StateManager::StateManager():
	currentState(NULL)
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "TACD");
	//window.create(sf::VideoMode(240, 160), "PlasmaFlux");
	currentState = new GameState(&window);
	//renderer = new GameRenderer(w, currentState->getGame());
	running = true;
}

StateManager::~StateManager()
{
	delete currentState;
	delete oldState;
}

StateManager& StateManager::getInstance() {
	static StateManager instance;
	return instance;
}

void StateManager::switchToState(State* state) {
	oldState = state;
}

void StateManager::goBack() {

	currentState->goBack();
}

void StateManager::quit() {
	running = false;
}

void StateManager::run()
{
	int frame = 0, milisecond = 0, second = 0, minute = 0;
	double MS_PER_FRAME = (1000.0) / FPS;//1000 ms per seconds
										 //int MS_PER_FRAME = 16;//miliseconds per frame
										 //clock_t FPS = 60;
	sf::Clock currentTime;
	sf::Time elapsedTime = currentTime.restart();
	window.setFramerateLimit(FPS);//framerate
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
				system("cls");
			}

			if (second >= 60)
			{
				minute++;
				second = 0;
			}
		}
		/*~Manage Time Beta*/
		//current = clock();
		//elapsed = current - lastTime;
		currentTime.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		currentState->tick();
		elapsedTime = currentTime.getElapsedTime();
		{
			printf("%d:%d  Frame: %d\n", minute, second, frame);
			printf("NB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n",
				(float)elapsedTime.asMilliseconds() * 60, elapsedTime, (float)CLOCKS_PER_SEC);
			
			gotoxy(0, 0);
		}
	}
}
