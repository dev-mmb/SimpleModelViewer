#pragma once

class UserInterface;

class Widget
{
public:
	Widget(UserInterface* u);

	virtual void render() {}

	void hide();
	void show();

	static void setUserInterface(UserInterface* u);
private:
	int id;

protected:
	static UserInterface* userInterface;
};

