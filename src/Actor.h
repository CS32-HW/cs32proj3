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

	virtual bool isPlayer() const = 0;
	virtual bool isMovable() const = 0;

	virtual bool move(int dir);

protected:
	StudentWorld* getWorld() const { return m_world; }
	Actor* getActorInDirection(int dir) const;

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

	virtual bool isPlayer() const { return true; }
	virtual bool isMovable() const { return false; }

private:
	void pushForward();
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

	virtual bool isPlayer() const { return false; }
	virtual bool isMovable() const { return false; }
private:
};

class Marble : public Actor
{
public:
	Marble(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_MARBLE, x, y)
	{
		setHP(10);
	}

	// marbles don't do anything
	virtual void doSomething() {}

	virtual bool isPlayer() const { return false; }
	virtual bool isMovable() const { return true; }


private:
};

#endif // ACTOR_H_
