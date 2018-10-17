#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include <string>
#include <vector>
#include <limits>

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
	std::string GetInput_String(const std::vector<std::string> &MessageList, const bool &ToLower, const bool &InputPoint, const bool &DisplayNumbers, const bool &NewLineSplit) const;
	int GetInput_Int(const std::vector<std::string> &MessageList, const int &Min, const int &Max, const bool &InputPoint, const bool &DisplayNumbers, const bool &HasTitle, const bool &NewLineSplit) const;
	void Print(const std::string &Message, const unsigned int &LinesBefore, const unsigned int &LinesAfter) const;
	void Print(const char &Character, const unsigned int &LinesBefore, const unsigned int &LinesAfter) const;
	void Print_Array(const std::vector<std::string> &MessageList, const bool &DisplayNumbers, const bool &HasTitle, const bool &NewLineSplit) const;
	void Print_Name(const std::vector<std::string> &NameComponents) const;
	void Print_NewLines(const unsigned int &Count) const;
	void Print_Bool(const bool &Value) const;
	bool CheckInputForCommands(const std::vector<std::string> Input, const std::vector<std::string> Checklist, unsigned int &NumberFound, std::vector<int> &LocationsFound) const;  //rework this
};
#endif // !USER_INTERFACE_H
