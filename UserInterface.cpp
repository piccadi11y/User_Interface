#include "UserInterface.h"

std::string UserInterface::getInput_str(const std::vector<std::string> messageList, const bool toLower, const bool DisplayInputPoint, const bool DisplayLineIncrements, const bool NewLineEachElement) const {
	print_Array(messageList, DisplayLineIncrements, false, NewLineEachElement);
	if (DisplayInputPoint) print({">"}, 0, 0);
	std::string input;
	bool isValid{ true };
	do {
		if (!isValid) std::cout << "Please only use letters\n>";
		isValid = true;
		std::cin >> input;
		for (unsigned int i{ 0 }; i < input.size(); i++) {
			//std::cout << input.at(i) << std::endl;
			if (!(input.at(i) >= UI_CAPITAL_LETTER_MIN && input.at(i) <= UI_CAPITAL_LETTER_MAX) && !(input.at(i) >= UI_LOWER_LETTER_MIN && input.at(i) <= UI_LOWER_LETTER_MAX)) isValid = false;
		}
	} while (!isValid);
	if (toLower) ConvertToLower(input);
	return input;
}

int UserInterface::getInput_int(const std::vector<std::string> messageList, const int minimum, const int maximum, const bool DisplayInputPoint, const bool DisplayLineIncrements, const bool IncludesTitle, const bool NewLineEachElement) const {
	if (!DisplayLineIncrements) print("Range: " + std::to_string(minimum) + " - " + std::to_string(maximum), 1, 1);
	print_Array(messageList, DisplayLineIncrements, IncludesTitle, NewLineEachElement);
	if (DisplayInputPoint) print(">", 0, 0);
	int input;
	bool inRange{ true };
	do {
		if (!inRange) print("Please enter a number within the range.\n>", 0, 0);
		while (!(std::cin >> input)) {
			print("Please only input numbers.\n>", 0, 0);
			std::cin.clear();
			std::cin.ignore(1000000, '\n');
		}
		inRange = false;
		std::cin.ignore(1000000, '\n');
	} while (!(input >= minimum && input <= maximum));
	return input;
}

void UserInterface::print(const std::string message, const unsigned int newLineCount_before, const unsigned int newLineCount_after) const {
	for (unsigned int i{ 0 }; i < newLineCount_before; i++) {
		std::cout << std::endl;
	}
    std::cout << message;
	for (unsigned int i{ 0 }; i < newLineCount_after; i++) {
		std::cout << std::endl;
	}
}

void UserInterface::print(const char character, const unsigned int newLineCount_before, const unsigned int newLineCount_after) const {
    print(std::string(1, character), newLineCount_before, newLineCount_after);
}

void UserInterface::print_Array(const std::vector<std::string> messageList, const bool printNumbers, const bool IncludesTitle, const bool NewLineEachElement) const {
	int i{ 1 };
	bool Title {IncludesTitle};
	for (const std::string &element : messageList) {
        if (printNumbers && element != "") {
            if (!Title) std::cout << i++ << ") ";
            print(element, 0, 1);
        }
		else if (element!= "") print(element, 0, NewLineEachElement);
		Title = false;
	}
}

void UserInterface::print_Name(const std::vector<std::string> NameComponents) {
    for (std::string element : NameComponents) {
        ConvertToUpper(element, {0});
        print(element + " ", 0, 0);
    }
}

void UserInterface::print_NewLines(const unsigned int NewLineCount) const {
    print("", 0, NewLineCount);
}

void UserInterface::print_Bool(const bool value) const {
    std::cout << std::boolalpha << value << std::noboolalpha;
}

bool UserInterface::checkInputForCommands(const std::vector<std::string> input, std::vector<std::string> checklist, unsigned int &numberFound, std::vector<int> &locationsFound) const {
	bool found{false};
	unsigned int nFound{ 0 };
	std::vector<int> locFound(UI_COMMANDS_MAX);
	unsigned int locFound_itteration{ 0 };

	for (unsigned int x{ 0 }; x < input.size(); x++) {                                  // need to completely rework this code
		for (unsigned int i{ 0 }; i < checklist.size(); i++) {                          // take the max number of words necessary in any command and search/commpare with those
			if (input.at(x) == checklist.at(i)) {
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

	numberFound = nFound;
	locationsFound = locFound;

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
	else {
		if (!(Char >= UI_CAPITAL_LETTER_MIN && Char <= UI_CAPITAL_LETTER_MAX)) {
			throw "This character is not a letter.";
		}
	}
}

void UserInterface::GetLower(char &Char) const {
	if (Char >= UI_CAPITAL_LETTER_MIN && Char <= UI_CAPITAL_LETTER_MAX) {
		Char += 32;
	}
	else {
		if (!(Char >= UI_LOWER_LETTER_MIN && Char <= UI_LOWER_LETTER_MAX)) {
			throw "This character is not a letter.";
		}
	}
}
