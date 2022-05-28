//
// Created by kriz on 06.03.2022.
//

#include <unordered_set>
#include "MenuGroupFactory.h"

#include "../MenuCommands/GoFiltersMenuGroup.h"
#include "../MenuCommands/GoMainMenuOption.h"
#include "../MenuCommands/GoLibraryMenuGroup.h"

#include "FiltersMenuGroup/FiltersMenuGroup.h"
#include "FiltersMenuGroup/Comands/ApplyLinearGrayscaleOption.h"
#include "FiltersMenuGroup/Comands/ApplyAverageGrayscaleOption.h"
#include "FiltersMenuGroup/Comands/ApplyGaussianBlurOption.h"
#include "FiltersMenuGroup/Comands/ApplyBoxBlurOption.h"
#include "FiltersMenuGroup/Comands/ApplyNegativeOption.h"
#include "FiltersMenuGroup/Comands/ApplyFlipTransformOption.h"
#include "FiltersMenuGroup/Comands/ApplySobelOption.h"
#include "FiltersMenuGroup/Comands/ApplyASCIIArtEffect.h"
#include "../MenuCommands/EndApplicationOption.cpp"

#include "LibraryMenuGroup/Commands/ListAllImagesOption.h"
#include "LibraryMenuGroup/Commands/AddImageToLibrary.h"
#include "LibraryMenuGroup/Commands/AddAllImagesFromDirOption.h"


#include "queue"

MenuGroupFactory::MenuGroupFactory(ImagesLibrary& imageLib) : ImageLibrary(imageLib) { }

std::unique_ptr<MenuGroup> MenuGroupFactory::CreateMainMenuGroup() {
    auto newMainMenuGroup = std::make_unique<MainMenuGroup>();
    newMainMenuGroup->AddMenuOption("a", std::make_unique<GoLibraryMenuGroup>());
    newMainMenuGroup->AddMenuOption("b", std::make_unique<GoFiltersMenuGroup>(ImageLibrary));
    newMainMenuGroup->AddMenuOption("c", std::make_unique<EndApplicationOption>());
    return std::move(newMainMenuGroup);
}

std::unique_ptr<MenuGroup> MenuGroupFactory::CreateFiltersMenuGroup(std::unordered_set<int> &&libraryIndexesToWorkWith) {
    std::vector<std::unique_ptr<MenuOption>> options;

    options.emplace_back(std::make_unique<ApplyLinearGrayscaleOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyAverageGrayscaleOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyGaussianBlurOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplySobelOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyBoxBlurOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyNegativeOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyFlipTransformOption>(libraryIndexesToWorkWith, ImageLibrary));
    options.emplace_back(std::make_unique<ApplyASCIIArtEffect>(libraryIndexesToWorkWith, ImageLibrary));


    auto newFiltersMenuGroup = std::make_unique<FiltersMenuGroup>();

    newFiltersMenuGroup->AddMenuOptions(options, MenuGroup::ALPHABET_LOWER);
    newFiltersMenuGroup->AddMenuOption("ch", std::make_unique<GoMainMenuOption>());
    return std::move(newFiltersMenuGroup);
}

std::unique_ptr<MenuGroup> MenuGroupFactory::CreateLibraryMenuGroup() {
    auto newLibraryMenuGroup = std::make_unique<LibraryMenuGroup>();
    newLibraryMenuGroup->AddMenuOption("a", std::make_unique<ListAllImagesOption>(ImageLibrary));
    newLibraryMenuGroup->AddMenuOption("b", std::make_unique<AddImageToLibrary>(ImageLibrary));
    newLibraryMenuGroup->AddMenuOption("c", std::make_unique<AddAllImagesFromDirOption>(ImageLibrary));
    newLibraryMenuGroup->AddMenuOption("d", std::make_unique<GoMainMenuOption>());
    return std::move(newLibraryMenuGroup);
}