#pragma once

class UserInterface;

class UserInterfaceComponent
{
public:
	UserInterfaceComponent(UserInterface* u);

	virtual void render() {}

	static void setUserInterface(UserInterface* u);
private:
	int id;

protected:
	static UserInterface* userInterface;
};

