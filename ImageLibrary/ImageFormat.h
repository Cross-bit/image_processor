//
// Created by kriz on 08.03.2022.
//

#ifndef MAIN_CPP_IMAGEFORMAT_H
#define MAIN_CPP_IMAGEFORMAT_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

#include "Image/ImageData.h"

class ImageFormat {
public:
    virtual ImageData LoadImageData() const = 0;
    virtual bool SaveImageData() const = 0;
};


#endif //MAIN_CPP_IMAGEFORMAT_H
