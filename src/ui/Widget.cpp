#include "Widget.h"
#include "UserInterface.h"

UserInterface* Widget::userInterface = nullptr;

Widget::Widget(UserInterface* u)
{
	id = -1;
	show();
}

void Widget::hide()
{
	if (id != -1) return;
	userInterface->removeComponent(id);
	id = -1;
}

void Widget::show()
{
	id = userInterface->addComponent(this);
}

void Widget::setUserInterface(UserInterface* u)
{
	userInterface = u;
}

