#include "PlayState.h"
#include "Application.h"

int main()
{
	Application app;
	app.addGameState(new PlayState());
	app.runMainLoop();

    return 0;
}

