#include "UserInterface.h"

std::string UserInterface::GetInput_String(const std::string &Message, const bool &InputPoint, const int &MaxCharacters) const {return GetInput_String({Message}, 0, InputPoint, 0, 0, MaxCharacters);}

std::string UserInterface::GetInput_String(const std::vector<std::string> &MessageList, const bool &OutputToLower, const bool &InputPoint, const bool &DisplayNumbers, const bool &NewLineSplit, const int &MaxCharacters) const {
	Print_Array(MessageList, DisplayNumbers, false, NewLineSplit);
	if (InputPoint) Print({">"}, 1, 0);
	char InputBuffer[MaxCharacters];
    std::string Input;
	bool isValid{ true };
	do {
		if (!isValid) std::cout << "Please only use letters\n>";
		isValid = true;
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		std::cin.getline(InputBuffer, sizeof(InputBuffer));
        Input = std::string(InputBuffer);
		for (unsigned int i{ 0 }; i < Input.size(); i++) {
			if (!(Input.at(i) >= UI_CAPITAL_LETTER_MIN && Input.at(i) <= UI_CAPITAL_LETTER_MAX) && !(Input.at(i) >= UI_LOWER_LETTER_MIN && Input.at(i) <= UI_LOWER_LETTER_MAX) && !(Input.at(i) == UI_WHITESPACE)) isValid = false;
		}
	} while (!isValid);
	if (OutputToLower) ConvertToLower(Input);
	return Input;
}

int UserInterface::GetInput_Int(const std::string &Message, const bool &InputPoint, const int &Min, const int &Max, const bool &PrintRange) const {return GetInput_Int({Message}, Min, Max, InputPoint, 0, 0, 0, PrintRange);}

int UserInterface::GetInput_Int(const std::vector<std::string> &MessageList, const int &Min, const int &Max, const bool &InputPoint, const bool &DisplayNumbers, const bool &HasTitle, const bool &NewLineSplit, const bool &PrintRange) const {
	if (PrintRange) Print("Range: " + std::to_string(Min) + " - " + std::to_string(Max), 1, 1);
	Print_Array(MessageList, DisplayNumbers, HasTitle, NewLineSplit);
	int input;
	while (1) {
	if (InputPoint) Print(">", 0, 0);
        while (!(std::cin >> input)) {
            Print("That is not a valid number.", 0, 1);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            if (InputPoint) Print(">", 0, 1);
        }
        if (input >= Min && input <= Max) return input;
        else Print(std::to_string(input) + " is out of range.", 0, 1);
    }
    return -1;
}

void UserInterface::Print(const std::string &Message, const unsigned int &LinesBefore, const unsigned int &LinesAfter) const {
	for (unsigned int i{ 0 }; i < LinesBefore; i++) {
		std::cout << std::endl;
	}
    std::cout << Message;
	for (unsigned int i{ 0 }; i < LinesAfter; i++) {
		std::cout << std::endl;
	}
}

void UserInterface::Print(const char &Character, const unsigned int &LinesBefore, const unsigned int &LinesAfter) const {
    Print(std::string(1, Character), LinesBefore, LinesAfter);
}

void UserInterface::Print_Array(const std::vector<std::string> &MessageList, const bool &DisplayNumbers, const bool &HasTitle, const bool &NewLineSplit) const {
	int i{ 1 };
	bool PrintTitle {HasTitle};
	for (const std::string &element : MessageList) {
        if (DisplayNumbers && element != "") {
            if (!PrintTitle) std::cout << i++ << ") ";
            Print(element, 0, 1);
        }
		else if (element!= "") Print(element, 0, NewLineSplit);
        PrintTitle = false;
	}
}

void UserInterface::Print_Name(const std::vector<std::string> &NameComponents) const {
    for (std::string element : NameComponents) {
        ConvertToUpper(element, {0});
        Print(element + " ", 0, 0);
    }
}

void UserInterface::Print_NewLines(const unsigned int &Count) const {
    Print("", 0, Count);
}

void UserInterface::Print_Bool(const bool &Value) const {
    std::cout << std::boolalpha << Value << std::noboolalpha;
}

bool UserInterface::CheckInputForCommands(const std::vector<std::string> Input, const std::vector<std::string> Checklist, unsigned int &NumberFound, std::vector<int> &LocationsFound) const {
	bool found{false};
	unsigned int nFound{ 0 };
	std::vector<int> locFound(UI_COMMANDS_MAX);
	unsigned int locFound_itteration{ 0 };

	for (unsigned int x{ 0 }; x < Input.size(); x++) {                                  // need to completely rework this code
		for (unsigned int i{ 0 }; i < Checklist.size(); i++) {                          // take the max number of words necessary in any command and search/commpare with those
			if (Input.at(x) == Checklist.at(i)) {
				found = true;
				nFound++;
				if (locFound_itteration < UI_COMMANDS_MAX) {	// pretty sure this logic is good**
					locFound.at(locFound_itteration) = i;
				}
			}
		}
	}

#ifdef _DEBUG
std::cout << "nFound = " << nFound << "\nlocFound = " << locFound[0] << std::endl;
#endif // _DEBUG

	NumberFound = nFound;
	LocationsFound = locFound;

	return found;
}

void UserInterface::ConvertToUpper(std::string &String) const {
	for (char &Element : String) {
		GetUpper(Element);
	}
}

void UserInterface::ConvertToUpper(std::string &String, const std::vector<int>ToSwitch) const {
	for (unsigned int i{ 0 }; i < ToSwitch.size(); i++) {     // Try to convert to for-each sometime???
		GetUpper(String.at(ToSwitch.at(i)));
	}
}

void UserInterface::ConvertToLower(std::string &String) const {
	for (char &Element : String) {
		GetLower(Element);
	}
}

void UserInterface::ConvertToLower(std::string &String, const std::vector<int>ToSwitch) const {
	for (unsigned int i{ 0 }; i < ToSwitch.size(); i++) {     // for-each in future???
		GetLower(String.at(ToSwitch.at(i)));
	}
}

void UserInterface::GetUpper(char &Char) const {
	if (Char >= UI_LOWER_LETTER_MIN && Char <= UI_LOWER_LETTER_MAX) {
		Char -= 32;
	}
	else if (Char != UI_WHITESPACE) {
		if (!(Char >= UI_CAPITAL_LETTER_MIN && Char <= UI_CAPITAL_LETTER_MAX)) {
			throw "This character is not a letter.";
		}
	}
}

void UserInterface::GetLower(char &Char) const {
	if (Char >= UI_CAPITAL_LETTER_MIN && Char <= UI_CAPITAL_LETTER_MAX) {
		Char += 32;
	}
	else if (Char != UI_WHITESPACE) {
		if (!(Char >= UI_LOWER_LETTER_MIN && Char <= UI_LOWER_LETTER_MAX)) {
			throw "This character is not a letter.";
		}
	}
}
