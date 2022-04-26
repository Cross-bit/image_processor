//
// Created by kriz on 06.03.2022.
//

#ifndef IMAGEPROCESSOR_GOIDLEMENUOPTION_H
#define IMAGEPROCESSOR_GOIDLEMENUOPTION_H

#include "MenuOption.h"

class GoIdleMenuOption : public MenuOption {
public:
    GoIdleMenuOption();

    std::unique_ptr<MenuGroup> CreateNextGroup(MenuGroupFactory & groupFactory) override;
};

#endif //IMAGEPROCESSOR_GOIDLEMENUOPTION_H