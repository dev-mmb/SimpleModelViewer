#include "Editor.h"

int main()
{
	Editor* e = new Editor(1920, 1080);
	e->run();
	delete e;
}


