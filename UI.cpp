#include "UI.h"

UI* UI::instance()
{
	static UI* ui = new UI;
	return ui;
}

void UI::initialize()
{
}

void UI::run()
{
}
