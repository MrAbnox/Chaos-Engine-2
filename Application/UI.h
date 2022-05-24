#ifndef UI_H
#define	UI_H


class UI
{
private:

	UI() {}
	UI(const UI&);
	UI& operator = (UI&);


public:
	static UI* instance();
	void initialize();
	void run();

};

#endif // !
