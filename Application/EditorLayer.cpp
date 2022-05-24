#include "EditorLayer.h"

EditorLayer* EditorLayer::instance()
{
	static EditorLayer* editorLayer = new EditorLayer;
	return editorLayer;
}

void EditorLayer::initialize()
{

}

void EditorLayer::run()
{

}
