#ifndef EDITOR_H
#define EDITOR_H

class Editor
{
private:

	Editor() {}
	Editor(const Editor&);
	Editor& operator = (Editor&);

public:

	static Editor* instance();

	void initialize();
	void run();

private:

	void LoadStates() {} //Load Specified State
	void SaveState() {} //Save current State
};

#endif

