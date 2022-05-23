#ifndef APPLICATION_H
#define APPLICATION_H
class Application
{
private:

	Application() {}
	Application(const Application&);
	Application& operator = (Application&);

public:

	static Application* instance();

	void start();
	void run();

private:

	bool isRunning;

};
#endif

