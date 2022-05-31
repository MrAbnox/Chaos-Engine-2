#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <fstream>
#include <vector>

enum Logs
{
	LOG = 1, ALERT, WARNING, DEBUG, SUCCESS
};
class Debug
{

public:

	static Debug* Log(const std::string& debuglog, Logs l = LOG);
	static Debug* Instance();

public:

	void Error(const std::string& errorlog);

public:

	void Clear();
	void Stack();
	void ShowWarning();
	void ShowError();

public:

	static const std::vector<std::string> GetWarnings();
	static const std::vector<std::string> GetAlerts();
	static const std::vector<std::string> GetLogs();

public:

	bool GetShowingWarnings();
	bool GetShowingAlerts();

private:

	Debug()
	{
		warnings.push_back("Showing Warnings!");
		alerts.push_back("Showing Alerts!");
	};

	Debug(const Debug&);
	Debug& operator=(const Debug&);

public:

	void CheckOpenGLErrors();

private:

	std::ofstream logFile;

private:

	static std::vector<std::string> logs;
	static std::vector<std::string> alerts;
	static std::vector<std::string> warnings;

private:

	bool isShowingWarnings = true;
	bool isShowingErrors = true;
};

#endif