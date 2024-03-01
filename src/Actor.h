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
		m_hp = 1;
		m_peaCount = 0;
	}

	virtual void doSomething() = 0;
	bool isAt(int x, int y) const;

	int getHP() const { return m_hp; }
	void setHP(int hp) { m_hp = hp; }
	virtual bool isAlive() const { return m_hp > 0; }
	virtual bool attack(int damage) { m_hp -= damage; return true; }

	virtual bool isMovable() const { return false; }
	virtual bool isFillable() const { return false; }
	virtual bool isPickupable() const { return false; }

	virtual int getPeaCount() const { return m_peaCount; }
	virtual void setPeaCount(int peaCount) { m_peaCount = peaCount; }

	// move actor in direction, returns false if failed
	virtual bool move(int dir);

protected:
	StudentWorld* getWorld() const { return m_world; }
	int getXInDir(int dir) const;
	int getYInDir(int dir) const;

private:
	StudentWorld* m_world;
	int m_hp;
	int m_peaCount;
};

class Avatar : public Actor
{
public:
	Avatar(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_PLAYER, x, y)
	{
		setHP(20);
		setPeaCount(20);
	}

	virtual void doSomething();

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

	// marbles can be moved by the player
	virtual bool isMovable() const { return true; }

private:
};

class Pea : public Actor
{
public:
	Pea(StudentWorld* sw, int x, int y, int dir)
	: Actor(sw, IID_PEA, x, y, dir)
	{
		firstFrame = true;
	}

	virtual void doSomething();
	// peas can't be attacked
	virtual bool attack(int damage) { return false; }

private:
	bool firstFrame;
};

class Pit : public Actor
{
public:
	Pit(StudentWorld* sw, int x, int y)
	: Actor(sw, IID_PIT, x, y)
	{
	}

	virtual void doSomething();
	virtual bool attack(int damage) { return false; }
	virtual bool isFillable() const { return true; }

private:
};

class Item : public Actor
{
public:
	Item(StudentWorld* sw, int imageID, int x, int y)
	: Actor(sw, imageID, x, y)
	{
	}

	virtual bool isPickupable() const { return true; }
	// items can't be attacked
	virtual bool attack(int damage) { return false; }

private:
};

class Crystal : public Item
{
public:
	Crystal(StudentWorld* sw, int x, int y)
	: Item(sw, IID_CRYSTAL, x, y)
	{
	}

	virtual void doSomething();

private:
};

#endif // ACTOR_H_
