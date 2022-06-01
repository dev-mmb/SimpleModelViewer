#include "Editor.h"

int main()
{
	Editor* e = new Editor(1000, 800);
	e->run();
	delete e;
}


