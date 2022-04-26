//
// Created by kriz on 06.03.2022.
//

#ifndef IMAGEPROCESSOR_GOSECONDMENUOPTION_H
#define IMAGEPROCESSOR_GOSECONDMENUOPTION_H


#include "MenuOption.h"

class GoSecondMenuOption : public MenuOption {
public:
    GoSecondMenuOption();

    std::unique_ptr<MenuGroup> CreateNextGroup(MenuGroupFactory & groupFactory) override;
};


#endif //IMAGEPROCESSOR_GOSECONDMENUOPTION_H
