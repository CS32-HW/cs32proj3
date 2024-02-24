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
		m_peaCount = 0;
	}

	bool isAt(int x, int y) const;
	virtual void doSomething() = 0;

	int getHP() const { return m_hp; }
	void setHP(int hp) { m_hp = hp; }
	virtual bool isAlive() const { return m_hp > 0; }
	virtual bool attack(int damage) { m_hp -= damage; return true; }

	virtual bool isPlayer() const { return false; }
	virtual bool isMovable() const { return false; }
	virtual bool isPea() const { return false; }

	virtual int getPeaCount() const { return m_peaCount; }
	virtual void setPeaCount(int peaCount) { m_peaCount = peaCount; }

	// move actor in direction, returns false if failed
	virtual bool move(int dir);

protected:
	StudentWorld* getWorld() const { return m_world; }
	Actor* getActorInDirection(int dir) const;

private:
	StudentWorld* m_world;
	int m_hp;
	int m_peaCount;
};

class Avatar : public Actor
{
public:
	Avatar(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_PLAYER, x, y, 0)
	{
		setHP(20);
		setPeaCount(20);
	}

	virtual void doSomething();

	virtual bool isPlayer() const { return true; }

private:
	void pushForward();
	void firePea();
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

	// walls can't die or take damage
	virtual bool isAlive() const { return true; }
	virtual bool attack(int damage) { return true; }

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

	virtual bool isMovable() const { return true; }

private:
};

class Pea : public Actor
{
public:
	Pea(StudentWorld* sw, int x, int y, int dir)
	: Actor(sw, IID_PEA, x, y, dir)
	{
		setHP(1);
	}

	virtual void doSomething();
	virtual bool isPea() const { return true; }
	virtual bool attack(int damage) { return false; }

private:
};

class Pit : public Actor
{
public:
	Pit(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_PIT, x, y)
	{
	}

	virtual void doSomething() {}
	virtual bool isAlive() const { return true; }
	virtual bool attack(int damage) { return false; }

private:
};

#endif // ACTOR_H_
