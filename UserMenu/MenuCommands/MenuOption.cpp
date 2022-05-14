//
// Created by kriz on 06.03.2022.
//

#include "MenuOption.h"

void MenuOption::Render(){
    std::cout << _itemContent;
}

void MenuOption::Execute() { }

void MenuOption::PrintError(const std::string& callbackMessage) {
    std::cout << "Error: " << callbackMessage << std::endl;
}

void MenuOption::PrintWarning(const std::string& callbackMessage) {
    std::cout << "Warning: " << callbackMessage << std::endl;
}

std::string MenuOption::ReadUserInput() const {
    std::string input;
    getline(std::cin, input);

    return std::move(MenuOption::TrimInputWhiteSpaces(input));
}

template <typename T>
void MenuOption::PrintInputFallback(const T& fallbackValue) {
    // it is up to user to specify all value types convertible to string(by to_string) in fallback arg, in ff declaration below
    std::cout << "No input provided, or the input is invalid. "
                 "Default value will be used instead. (def.:"
                 << fallbackValue << std::to_string(fallbackValue) << ")" << std::endl;
}

// ff declaration for fallback prints (add if some more needed in the future)
template void MenuOption::PrintInputFallback<int>(const int&);
template void MenuOption::PrintInputFallback<double>(const double&);

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
