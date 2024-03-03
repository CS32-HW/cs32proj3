#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>

class Actor;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	virtual ~StudentWorld() { cleanUp(); }
	virtual int init();
	virtual int move();
	virtual void cleanUp();

	bool containsActor(int x, int y) const;
	Actor* getActor(int x, int y) const;
	Actor* getPlayer() const;
	Actor* getGoodie(int x, int y) const;
	bool playerIsInLineOfSight(int x, int y, int dir) const;
	// checks for actors that can be attacked by peas
	// bounds are inclusive
	// returns false if x1 > x2 || y1 > y2
	bool obstructionExists(int x1, int y1, int x2, int y2) const;
	int getNumberOfCrystals() const;
	bool containsMovableActor(int x, int y) const;
	bool containsFillableActor(int x, int y) const;
	bool containsGoodie(int x, int y) const;
	void addActor(Actor* actor);
	bool attackActors(int x, int y, int damage);
	bool killActors(int x, int y);
	void levelComplete() { m_level_complete = true; }

	// can't use the constants defined in GraphObject
	static const int none = -1;
	static const int right = 0;
	static const int left = 180;
	static const int up = 90;
	static const int down = 270;

private:
	std::list<Actor*> m_actors;
	Level m_level;
	int m_bonus;
	bool m_level_complete;
};

#endif // STUDENTWORLD_H_
