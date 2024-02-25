#include "Actor.h"
#include "StudentWorld.h"
#include <math.h>

bool Actor::isAt(int x, int y) const
{
	if (fabs(getX()-x) < 0.5 && fabs(getY()-y) < 0.5)
		return true;
	else
		return false;
}

bool Actor::move(int dir)
{
	bool retval = true;
	int prev_dir = getDirection();
	setDirection(dir);

	int newX = getXInDir(dir);
	int newY = getYInDir(dir);

	if (!getWorld()->containsActor(newX, newY) || getWorld()->containsFillableActor(newX, newY))
		moveForward();
	else
		retval = false;

	std::cerr << retval;
	Actor* test = getWorld()->getActor(newX, newY);
	if (test != nullptr)
		std::cerr << test->isFillable();

	setDirection(prev_dir);
	return retval;
}

int Actor::getXInDir(int dir) const
{
	if (dir == left)
		return getX()-1;
	else if (dir == right)
		return getX()+1;
	else
		return getX();
}

int Actor::getYInDir(int dir) const
{
	if (dir == down)
		return getY()-1;
	else if (dir == up)
		return getY()+1;
	else
		return getY();
}

void Avatar::doSomething()
{
	if (!isAlive())
		return;

	int key;
	if (getWorld()->getKey(key)) {
		switch (key) {
		case KEY_PRESS_ESCAPE:
			setHP(0);
			break;
		case KEY_PRESS_SPACE:
			firePea();
			break;
		case KEY_PRESS_LEFT:
			setDirection(left);
			pushForward();
			break;
		case KEY_PRESS_RIGHT:
			setDirection(right);
			pushForward();
			break;
		case KEY_PRESS_UP:
			setDirection(up);
			pushForward();
			break;
		case KEY_PRESS_DOWN:
			setDirection(down);
			pushForward();
			break;
		}
	}
}

void Avatar::pushForward()
{
	int dir = getDirection();
	int newX = getXInDir(dir);
	int newY = getYInDir(dir);
	Actor* actor = getWorld()->getActor(newX, newY);

	if (actor == nullptr) {
		moveForward();
	} else if (actor->isMovable()) {
		if (actor->move(dir))
			moveForward();
	}

	return;
}

void Avatar::firePea()
{
	if (getPeaCount() <= 0)
		return;

	int dir = getDirection();

	Actor* pea = new Pea(getWorld(), getXInDir(dir), getYInDir(dir), dir);
	getWorld()->addActor(pea);

	setPeaCount(getPeaCount()-1);
	return;
}

void Pea::doSomething()
{
	if (!isAlive())
		return;

	if (getWorld()->attackActors(getX(), getY(), 2)) {
		setHP(0);
		return;
	}

	moveForward();

	if (getWorld()->attackActors(getX(), getY(), 2))
		setHP(0);

	return;
}

void Pit::doSomething()
{
	if (!isAlive())
		return;

	if (getWorld()->containsMovableActor(getX(), getY()))
		getWorld()->killActors(getX(), getY());
}
