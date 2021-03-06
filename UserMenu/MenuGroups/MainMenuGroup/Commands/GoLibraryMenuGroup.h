//
// Created by kriz on 26.04.2022.
//

#ifndef MAIN_CPP_GOLIBRARYMENUGROUP_H
#define MAIN_CPP_GOLIBRARYMENUGROUP_H


#include "../../../OtherMenuCommands/MenuOption.h"

class GoLibraryMenuGroup : public MenuOption {
public:
    GoLibraryMenuGroup();

    std::unique_ptr<MenuGroup> CreateNextGroup(UserMenu &userMenu) override;
};



#endif //MAIN_CPP_GOLIBRARYMENUGROUP_H
