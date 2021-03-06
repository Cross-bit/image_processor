//
// Created by kriz on 26.04.2022.
//

#include "AddAllImagesFromDirOption.h"
#include <iostream>
#include <filesystem>

#include "../../../UserMenu.h"
#include "../../MenuGroupFactory.h"

AddAllImagesFromDirOption::AddAllImagesFromDirOption(ImagesLibrary& imagesLibrary, std::string sourceDir) :
_imagesLibrary(imagesLibrary),
_sourceDir(sourceDir)
{
    _itemContent = "Add all images from dir";
}

void AddAllImagesFromDirOption::Execute(UserMenu& userMenu) {

    PrintLine("Enter full path to directory: ");

    _sourceDir = _sourceDir == "" ? ReadUserInput() : _sourceDir;

    if(!std::filesystem::is_directory(_sourceDir)){
        PrintError("Invalid directory!");
        return;
    }

    for (const auto & entry : std::filesystem::directory_iterator(_sourceDir)) {

        if(_imagesLibrary.CheckIfRecordExists(entry.path()))
            continue;

        // load format
        std::string fileExtension = ImagesLibrary::ParseFileExstention(entry.path());

        auto imgFormat = _formatFactory.CreateImageFormat(fileExtension);
        std::string imgName = ImageFormat::ParseFileName(entry.path());

        if (imgFormat == nullptr){
            PrintError("Not able to load: " + ImageFormat::ParseFileName(entry.path()));
            continue;
        }

        auto imageData = imgFormat->LoadImageData(entry.path());

        if (imageData == nullptr) {
            PrintError("Not able to load: " + ImageFormat::ParseFileName(entry.path()));
            continue;
        }

        _imagesLibrary.AddRecord(std::move(entry.path()), std::move(imageData));

        PrintSuccess("Img:" + imgName + " OK ");
    }

    PrintSuccess("Loading done.");
}

std::unique_ptr<MenuGroup> AddAllImagesFromDirOption::CreateNextGroup(UserMenu & userMenu) {
    return std::move(userMenu.GroupsFac.CreateLibraryMenuGroup());
}


