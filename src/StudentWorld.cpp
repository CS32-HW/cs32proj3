#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath) : GameWorld(assetPath)
{
}

int StudentWorld::init()
{
	m_actors.push_back(new Avatar(this, 1, 1, 90));
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you type q
	setGameStatText("Game will end when you type q");

	list<Actor*>::iterator it = m_actors.begin();
	for (; it != m_actors.end(); it++)
		(**it).move();

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	list<Actor*>::iterator it = m_actors.begin();
	while (it != m_actors.end()) {
		delete *it;
		it = m_actors.erase(it);
	}
}
