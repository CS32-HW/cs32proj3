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

	Actor* actor = getActorInDirection(dir);

	if (actor == nullptr)
		moveForward();
	else
		retval = false;

	setDirection(prev_dir);
	return retval;
}

Actor* Actor::getActorInDirection(int dir) const
{
	Actor* actor;

	if (dir == left)
		actor = getWorld()->getActor(getX()-1, getY());
	else if (dir == right)
		actor = getWorld()->getActor(getX()+1, getY());
	else if (dir == up)
		actor = getWorld()->getActor(getX(), getY()+1);
	else if (dir == down)
		actor = getWorld()->getActor(getX(), getY()-1);
	else
		actor = nullptr; // invalid direction

	return actor;
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
	Actor* actor = getActorInDirection(getDirection());

	if (actor == nullptr) {
		moveForward();
	} else if (actor->isMovable()) {
		if (actor->move(getDirection()))
			moveForward();
	}

	return;
}
