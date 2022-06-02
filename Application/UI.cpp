#include "UI.h"

UI* UI::instance()
{
	static UI* ui = new UI;
	return ui;
}

void UI::initialize()
{
}

//Add ingame UI
//Such as health bar and such
void UI::run()
{
}
