#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: m_level(assetPath), GameWorld(assetPath)
{
}

int StudentWorld::init()
{
	int lvl = getLevel();
	if (lvl > 99)
		return GWSTATUS_PLAYER_WON;

	char lvlStr[3];
	snprintf(lvlStr, 3, "%02d", lvl);
	string lvlFile = "level" + (string)lvlStr + ".txt";

	Level::LoadResult result = m_level.loadLevel(lvlFile);
	if (result == Level::load_fail_file_not_found) {
		cerr << "error: could not find " << lvlFile << endl;
		return GWSTATUS_LEVEL_ERROR;
	} else if (result == Level::load_fail_bad_format) {
		cerr << "error: " << lvlFile << " was improperly formatted" << endl;
		return GWSTATUS_LEVEL_ERROR;
	}

	for (int x = 0; x < VIEW_WIDTH; x++) {
		for (int y = 0; y < VIEW_HEIGHT; y++) {
			Level::MazeEntry obj = m_level.getContentsOf(x, y);
			switch (obj) {
			case Level::empty:
				break;
			case Level::player:
				m_actors.push_back(new Avatar(this, x, y));
				break;
			case Level::wall:
				m_actors.push_back(new Wall(this, x, y));
				break;
			}
		}
	}
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

bool StudentWorld::containsActor(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y))
			return true;
	}

	return false;
}
