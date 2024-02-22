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

private:
	std::list<Actor*> m_actors;
	Level m_level;
};

#endif // STUDENTWORLD_H_
