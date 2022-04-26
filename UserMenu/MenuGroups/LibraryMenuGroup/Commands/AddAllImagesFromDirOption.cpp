//
// Created by kriz on 26.04.2022.
//

#include "AddAllImagesFromDirOption.h"
#include <iostream>
#include <filesystem>

AddAllImagesFromDirOption::AddAllImagesFromDirOption(ImagesLibrary& imagesLibrary) : _imagesLibrary(imagesLibrary)
{

    _itemContent = "Add all images from dir";
}

void AddAllImagesFromDirOption::Execute() {

    std::cout << "Enter full path to directory: " << std::endl;

    std::string dirPath;

    getline(std::cin, dirPath);

    if(!std::filesystem::is_directory(dirPath)){
        std::cout << "Invalid directory!" << std::endl;
        return;
    }

    for (const auto & entry : std::filesystem::directory_iterator(dirPath)) {

        if(_imagesLibrary.CheckIfRecordExists(entry.path()))
            continue;

        // load format
        std::string fileExtension = ImagesLibrary::ParseFileExstention(entry.path());

        auto imgFormat = _formatFactory.CreateImageFormat(fileExtension);
        std::string imgName = ImageFormat::ParseFileName(entry.path());

        if (imgFormat == nullptr){
            PrintWarning("Not able to load: " + ImageFormat::ParseFileName(entry.path()));
            continue;
        }

        auto imageData = imgFormat->LoadImageData(entry.path());

        _imagesLibrary.AddRecord(std::move(entry.path()), std::move(imageData));

        std::cout << "Immage: " << imgName << "added successfully!" << std::endl;
    }

    std::cout << "Loading done." << std::endl;
}

std::unique_ptr<MenuGroup> AddAllImagesFromDirOption::CreateNextGroup(MenuGroupFactory &groupFactory) {

}

