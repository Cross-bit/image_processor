//
// Created by kriz on 06.03.2022.
//

#include "MenuOption.h"
#include <algorithm>
#include <string>
#include <memory>
#include <iostream>

void MenuOption::Render(){
    std::cout << _itemContent;
}

void MenuOption::Execute(UserMenu& userMenu) { }

void MenuOption::PrintError(const std::string& callbackMessage) {
    std::cout << red << "Error: " << callbackMessage << std::endl << reset;
}

void MenuOption::PrintWarning(const std::string& callbackMessage) {
    std::cout << yellow << "Warning: " << callbackMessage << std::endl << reset;
}

void MenuOption::Print(const std::string& messageToPrint) {
    std::cout << messageToPrint;
}

void MenuOption::PrintSuccess(const std::string& messageToPrint) {
    std::cout << green << messageToPrint << std::endl << reset;
}

void MenuOption::PrintLine(const std::string& messageToPrint) {
    std::cout << messageToPrint << std::endl;
}

void MenuOption::PrintList(const std::vector<std::string>& messagesToPrint, std::string optionalBullet) {
    for (auto &message : messagesToPrint) {
        Print(optionalBullet);
        PrintLine(message);
    }
}

std::string MenuOption::ReadUserInput() const {
    std::string input;
    getline(std::cin, input);

    return std::move(MenuOption::TrimInputWhiteSpaces(input));
}

bool MenuOption::ReadUserInputNaturalNum(int& userInput, const unsigned int min, const unsigned int max) const {
    userInput = -1;
    std::string rawInput = ReadUserInput();

    if (!CheckIfStringIsNaturalNumber(rawInput))
        return false;

    int converted = std::stoi(rawInput);

    if (converted < min || converted > max)
        return false;

    userInput = converted;

    return true;
}

bool MenuOption::CheckIfStringIsNaturalNumber(std::string& stringToCheck) {
    return (stringToCheck.find_first_not_of("0123456789" ) == std::string::npos && stringToCheck.length() >= 1);
}

bool MenuOption::ReadUserInputDecimal(double& userInput, const double min, const double max) const {

    auto rawInput = ReadUserInput();
    char* endptr = 0;

    userInput = strtod(&rawInput[0], &endptr);

    if (*endptr != '\0' || endptr == rawInput) {
        userInput = 0;
        return false;
    }

    if (userInput < min || userInput > max){
        userInput = 0;
        return false;
    }


    return true;
}


bool MenuOption::ReadUserChoice(const std::string& expected, std::string& inputValue) const {
    inputValue = ReadUserInput();
    return (inputValue == expected);
}

bool MenuOption::ReadUserChoices(const std::vector<std::string>& possibleInputs, std::string& inputValue) const {
    inputValue = ReadUserInput();
    return std::find(possibleInputs.begin(), possibleInputs.end(), inputValue) != possibleInputs.end();
}

bool MenuOption::ReadUserYesNo(bool& result) const {
    result = false;
    std::string inputValue = ReadUserInput();

    bool isInvalid = inputValue.length() > 1 || inputValue == "" || std::string("yn").find(tolower(inputValue[0])) == std::string::npos;
    if (isInvalid) return false;

    result = std::tolower(inputValue[0]) == 'y';

    return true;
}

template <typename T>
void MenuOption::PrintInputFallback(const T& fallbackValue) const {
    // it is up to user to specify all value types convertible to string(by to_string) in fallback arg, in ff declaration below
    std::cout << GetFallbackMessage(std::to_string(fallbackValue)) << std::endl;
}

// ff declaration for fallback prints (add if some more needed in the future)
template void MenuOption::PrintInputFallback<int>(const int&) const;
template void MenuOption::PrintInputFallback<double>(const double&) const;
template void MenuOption::PrintInputFallback<float>(const float&) const;

void MenuOption::PrintInputFallback(const char& fallbackValue) const {
    std::cout << GetFallbackMessage(std::string(1, fallbackValue)) << std::endl;
}

void MenuOption::PrintInputFallback(const std::string& fallbackValue) const {
    std::cout << GetFallbackMessage(fallbackValue) << std::endl;
}

std::string MenuOption::GetFallbackMessage(const std::string& defValue) const {
    return cyan + "No input provided, or the input is invalid. "
                  "Default value will be used instead. (def.: "
           + defValue + ")" + reset;
}
// -- static helper functions
const std::string MenuOption::WHITESPACE = " \n\r\t\f\v";

bool MenuOption::CheckStringIsEmpty(const std::string &inputToCheck) {
    return inputToCheck == "" || inputToCheck.find_first_not_of(MenuOption::WHITESPACE) == std::string::npos;
}

std::string MenuOption::TrimInputWhiteSpaces(const std::string& inputToTrim) {
    return MenuOption::TrimInputWhiteSpacesFront(MenuOption::TrimInputWhiteSpacesBack(inputToTrim));
}

std::string MenuOption::TrimInputWhiteSpacesFront(const std::string& inputToTrim){
    size_t start = inputToTrim.find_first_not_of(MenuOption::WHITESPACE);
    return (start == std::string::npos) ? "" : inputToTrim.substr(start);
}

std::string MenuOption::TrimInputWhiteSpacesBack(const std::string& inputToTrim){
    size_t end = inputToTrim.find_last_not_of(MenuOption::WHITESPACE);
    return (end == std::string::npos) ? "" : inputToTrim.substr(0, end + 1);
}

MenuOption::~MenuOption() { }
