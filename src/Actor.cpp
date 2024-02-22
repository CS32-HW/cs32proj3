#include "Actor.h"
#include "StudentWorld.h"

bool Actor::isAt(int x, int y) const
{
	if (getX() == x && getY() == y)
		return true;
	else
		return false;
}

void Avatar::move()
{
	int key;
	if (getWorld()->getKey(key)) {
		switch (key) {
		case KEY_PRESS_LEFT:
			if (!getWorld()->containsActor(getX()-1, getY()))
				moveTo(getX()-1, getY());
			setDirection(180);
			break;
		case KEY_PRESS_RIGHT:
			if (!getWorld()->containsActor(getX()+1, getY()))
				moveTo(getX()+1, getY());
			setDirection(0);
			break;
		case KEY_PRESS_UP:
			if (!getWorld()->containsActor(getX(), getY()+1))
				moveTo(getX(), getY()+1);
			setDirection(90);
			break;
		case KEY_PRESS_DOWN:
			if (!getWorld()->containsActor(getX(), getY()-1))
				moveTo(getX(), getY()-1);
			setDirection(270);
			break;
		}
	}
}
