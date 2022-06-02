#include "Editor.h"

Editor* Editor::instance()
{
	static Editor* editorLayer = new Editor;
	return editorLayer;
}

void Editor::initialize()
{

}
//Add editor only camera
//Add inspector
//Add Hierarchy of objects
//Make objects selectable
void Editor::run()
{

}
