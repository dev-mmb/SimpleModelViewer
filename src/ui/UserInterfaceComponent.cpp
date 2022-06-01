#include "UserInterfaceComponent.h"
#include "UserInterface.h"

UserInterface* UserInterfaceComponent::userInterface = nullptr;

UserInterfaceComponent::UserInterfaceComponent(UserInterface* u)
{
	u->addComponent(this);
}

void UserInterfaceComponent::setUserInterface(UserInterface* u)
{
	userInterface = u;
}

