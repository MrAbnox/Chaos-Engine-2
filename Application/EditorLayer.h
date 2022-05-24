#ifndef EDITORLAYER_H
#define EDITORLAYER_H

class EditorLayer
{
private:

	EditorLayer() {}
	EditorLayer(const EditorLayer&);
	EditorLayer& operator = (EditorLayer&);

public:

	static EditorLayer* instance();

	void initialize();
	void run();

private:

	void LoadStates() {} //Load Specified State
	void SaveState() {} //Save current State
};

#endif

