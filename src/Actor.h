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
		setVisible(true);
		m_world = sw;
		m_hp = 0;
	}

	bool isAt(int x, int y) const;
	virtual void doSomething() = 0;

	virtual bool isAlive() const { return m_hp > 0; }
	int getHP() const { return m_hp; }
	void setHP(int hp) { m_hp = hp; }

protected:
	StudentWorld* getWorld() const { return m_world; }

private:
	StudentWorld* m_world;
	int m_hp;
};

class Avatar : public Actor
{
public:
	Avatar(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_PLAYER, x, y, 0)
	{
		setHP(20);
	}

	virtual void doSomething();
private:
};

class Wall : public Actor
{
public:
	Wall(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_WALL, x, y)
	{
	}

	// walls don't do anything
	virtual void doSomething() {}

	// walls can't die
	virtual bool isAlive() const { return true; }
private:
};

#endif // ACTOR_H_
