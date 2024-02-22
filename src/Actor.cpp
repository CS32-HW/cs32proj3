#include "Actor.h"
#include "StudentWorld.h"

void Avatar::move()
{
	int key;
	if (getWorld()->getKey(key)) {
		switch (key) {
		case KEY_PRESS_LEFT:
			moveTo(getX() - 1, getY());
			setDirection(180);
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 1, getY());
			setDirection(0);
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() + 1);
			setDirection(90);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 1);
			setDirection(270);
			break;
		}
	}
}
