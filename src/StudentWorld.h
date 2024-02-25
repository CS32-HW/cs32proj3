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
	bool containsMovableActor(int x, int y) const;
	bool containsFillableActor(int x, int y) const;
	void addActor(Actor* actor);
	bool attackActors(int x, int y, int damage);
	bool killActors(int x, int y);

private:
	std::list<Actor*> m_actors;
	Level m_level;
	int m_bonus;
};

#endif // STUDENTWORLD_H_
