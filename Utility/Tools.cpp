#include "Tools.h"

//Parse text function into a vector
//-------------------------------------------------------------------------------
void ParseText(std::string& sentence, char& token, std::vector<std::string>& vector)
{
	int n = 0;

	n = sentence.find(token);

	if (n != std::string::npos)
	{

		std::string tempString = sentence.substr(0, n);
		sentence.erase(0, n + 1);
		vector.push_back(tempString);
		vector.push_back(sentence);
	}
}
