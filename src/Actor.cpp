#include "Actor.h"
#include "StudentWorld.h"

void Avatar::move()
{
	int key;
	if (getWorld()->getKey(key)) {
		switch (key) {
		case KEY_PRESS_LEFT:
			moveTo(getX() - 1, getY());
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 1, getY());
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() + 1);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 1);
			break;
		}
	}
}
