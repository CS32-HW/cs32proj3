#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(StudentWorld* sw, int imageID, int x, int y, int dir = 0)
	: GraphObject(imageID, x, y, dir)
	{
		m_world = sw;
		setVisible(true);
	}

	bool isAt(int x, int y) const;
	virtual void move() = 0;

protected:
	StudentWorld* getWorld() const { return m_world; }

private:
	StudentWorld* m_world;
};

class Avatar : public Actor
{
public:
	Avatar(StudentWorld* sw, int x, int y, int dir = 0)
	: Actor(sw, IID_PLAYER, x, y, dir)
	{
	}

	virtual void move();
private:
};

class Wall : public Actor
{
public:
	Wall(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_WALL, x, y, 0)
	{
	}

	// walls don't do anything
	virtual void move()
	{
	}
private:
};

#endif // ACTOR_H_
