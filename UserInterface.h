#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include <string>
#include <vector>

#define UI_CAPITAL_LETTER_MIN 65
#define UI_CAPITAL_LETTER_MAX 90
#define UI_LOWER_LETTER_MIN 97
#define UI_LOWER_LETTER_MAX 122
#define UI_COMMANDS_MAX 1

class UserInterface {
private:
	void ConvertToUpper(std::string &String) const;                                         // potentially make public
	void ConvertToUpper(std::string &String, const std::vector<int>ToSwitch) const;         // potentially make public
	void ConvertToLower(std::string &String) const;                                         // potentially make public
	void ConvertToLower(std::string &String, const std::vector<int>ToSwitch) const;         // potentially make public
	void GetUpper(char &Char) const;
	void GetLower(char &Char) const;

public:
    //~UserInterface() {print("Destroyed", 0);}     for testing purposes
	std::string getInput_str(const std::vector<std::string> messageList, const bool toLower, const bool DisplayInputPoint, const bool DisplayLineIncrements, const bool NewLineEachElement) const;
	int getInput_int(const std::vector<std::string> messageList, const int minimum, const int maximum, const bool DisplayInputPoint, const bool DisplayLineIncrements, const bool IncludesTitle, const bool NewLineEachElement) const;
	void print(const std::string message, const unsigned int newLineCount_before, const unsigned int newLineCount_after) const;
	void print(const char character, const unsigned int newLineCount_before, const unsigned int newLineCount_after) const;
	void print_Array(const std::vector<std::string> messageList, const bool printNumbers, const bool IncludesTitle, const bool NewLineEachElement) const;
	void print_Name(const std::vector<std::string> NameComponents);
	void print_NewLines(const unsigned int NewLineCount) const;
	void print_Bool(const bool value) const;
	bool checkInputForCommands(const std::vector<std::string> input, const std::vector<std::string> checklist, unsigned int &numberFound, std::vector<int> &locationsFound) const;  //rework this
};
#endif // !USER_INTERFACE_H
