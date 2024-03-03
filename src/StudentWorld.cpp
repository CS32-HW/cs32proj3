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
	m_bonus = 0;
	m_level_complete = false;
}

int StudentWorld::init()
{
	int lvl = getLevel();
	if (lvl > 99)
		return GWSTATUS_PLAYER_WON;

	m_bonus = 1000; // each level starts off with bonus of 1000

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
				// player at front for easy access
				m_actors.push_front(new Avatar(this, x, y));
				break;
			case Level::wall:
				addActor(new Wall(this, x, y));
				break;
			case Level::marble:
				addActor(new Marble(this, x, y));
				break;
			case Level::pit:
				addActor(new Pit(this, x, y));
				break;
			case Level::crystal:
				addActor(new Crystal(this, x, y));
				break;
			case Level::exit:
				addActor(new Exit(this, x, y));
				break;
			case Level::extra_life:
				addActor(new ExtraLife(this, x, y));
				break;
			case Level::restore_health:
				addActor(new RestoreHealth(this, x, y));
				break;
			case Level::ammo:
				addActor(new Ammo(this, x, y));
				break;
			case Level::horiz_ragebot:
				addActor(new RageBot(this, x, y, right));
				break;
			case Level::vert_ragebot:
				addActor(new RageBot(this, x, y, down));
				break;
			case Level::thiefbot_factory:
				addActor(new ThiefBotFactory(this, x, y, 1));
				break;
			case Level::mean_thiefbot_factory:
				addActor(new ThiefBotFactory(this, x, y, 2));
				break;
			}
		}
	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	list<Actor*>::iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAlive())
			(**it).doSomething();
	}

	if (m_level_complete) {
		m_level_complete = false;
		increaseScore(m_bonus);
		return GWSTATUS_FINISHED_LEVEL;
	}

	// delete dead actors
	for (it = m_actors.begin(); it != m_actors.end(); ) {
		if (!(**it).isAlive()) {
			// if player died
			if (it == m_actors.begin()) {
				decLives();
				return GWSTATUS_PLAYER_DIED;
			}

			delete *it;
			it = m_actors.erase(it);
		} else {
			it++;
		}
	}

	// reduce bonus score by 1
	if (m_bonus > 0)
		m_bonus -= 1;

	char status[100];
	snprintf(status, 100, "Score: %07d  Level: %02d  Lives: %2d  Health: %3d%%  Ammo: %3d  Bonus: %4d",
			getScore(), getLevel(), getLives(), m_actors.front()->getHP()*5, m_actors.front()->getPeaCount(), m_bonus);
	setGameStatText((string)status);

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

bool StudentWorld::containsMovableActor(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y) && (**it).isMovable())
			return true;
	}

	return false;
}

bool StudentWorld::containsFillableActor(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y) && (**it).isFillable())
			return true;
	}

	return false;
}

bool StudentWorld::containsGoodie(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y) && (**it).isGoodie())
			return true;
	}

	return false;
}

bool StudentWorld::containsObstructiveActor(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y) && !(**it).canShareSpace())
			return true;
	}

	return false;
}

Actor* StudentWorld::getActor(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y))
			return *it;
	}

	return nullptr;
}

Actor* StudentWorld::getPlayer() const
{
	return m_actors.front();
}

Actor* StudentWorld::getGoodie(int x, int y) const
{
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y) && (**it).isGoodie())
			return *it;
	}

	return nullptr;
}

bool StudentWorld::playerIsInLineOfSight(int x, int y, int dir) const
{

	if (dir == left) {
		if (getPlayer()->getX() < x && getPlayer()->getY() == y)
			return !obstructionExists(getPlayer()->getX()+1, y, x-1, y);
	} else if (dir == right) {
		if (getPlayer()->getX() > x && getPlayer()->getY() == y)
			return !obstructionExists(x+1, y, getPlayer()->getX()-1, y);
	} else if (dir == up) {
		if (getPlayer()->getX() == x && getPlayer()->getY() > y)
			return !obstructionExists(x, y+1, x, getPlayer()->getY()-1);
	} else if (dir == down) {
		if (getPlayer()->getX() == x && getPlayer()->getY() < y)
			return !obstructionExists(x, getPlayer()->getY()+1, x, y-1);
	}

	return false;
}

bool StudentWorld::obstructionExists(int x1, int y1, int x2, int y2) const
{
	if (x1 > x2 || y1 > y2)
		return false;

	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		int x = (**it).getX();
		int y = (**it).getY();
		if (x1 <= x && x <= x2 && y1 <= y && y <= y2 && (**it).attack(0))
			return true;
	}

	return false;
}

int StudentWorld::getNumberOfCrystals() const
{
	int count = 0;
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAlive() && (**it).isCrystal())
			count++;
	}

	return count;
}

int StudentWorld::countThiefBots(int x1, int y1, int x2, int y2) const
{
	if (x1 > x2 || y1 > y2)
		return 0;

	int count = 0;
	list<Actor*>::const_iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		int x = (**it).getX();
		int y = (**it).getY();
		if ((**it).isAlive() && (**it).isThiefBot() &&
				x1 <= x && x <= x2 && y1 <= y && y <= y2)
			count++;
	}

	return count;
}

void StudentWorld::addActor(Actor* actor)
{
	m_actors.push_back(actor);
	return;
}

bool StudentWorld::attackActors(int x, int y, int damage)
{
	bool retval = false;

	list<Actor*>::iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y)) {
			if ((**it).attack(damage))
				retval = true;
		}
	}

	return retval;
}

bool StudentWorld::killActors(int x, int y)
{
	bool retval = false;

	list<Actor*>::iterator it;
	for (it = m_actors.begin(); it != m_actors.end(); it++) {
		if ((**it).isAt(x, y)) {
			(**it).setHP(0);
			retval = true;
		}
	}

	return retval;
}
