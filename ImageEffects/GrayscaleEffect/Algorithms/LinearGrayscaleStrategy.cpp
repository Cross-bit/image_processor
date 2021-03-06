//
// Created by kriz on 20.04.2022.
//

#include "LinearGrayscaleStrategy.h"
#include <cstring>
#include <math.h>
LinearGrayscaleStrategy::LinearGrayscaleStrategy() :
    _redCoef(0.2126),
    _greenCoef(0.7152),
    _blueCoef(0.0722) { }

LinearGrayscaleStrategy::LinearGrayscaleStrategy(float redCoef, float greenCoef, float blueCoef) :
    _redCoef(redCoef),
    _greenCoef(greenCoef),
    _blueCoef(blueCoef) { }

void LinearGrayscaleStrategy::SetLinearParameters(float red, float green, float blue) {
    _redCoef = red;
    _greenCoef = green;
    _blueCoef = blue;
}

std::unique_ptr<ImageData> LinearGrayscaleStrategy::TransformToGrayscale(ImageData &inputData) const {

    auto imageCopy = std::make_unique<ImageData>(inputData);

    for (int i = 0; i < inputData.DataSize; i += inputData.Channels)
    {

        float res;
        res = _redCoef * ImageData::sRGBGammaExpansion(inputData.Data[i] / (float) 255);
        res += _greenCoef * ImageData::sRGBGammaExpansion(inputData.Data[i + 1] / (float) 255);
        res += _blueCoef * ImageData::sRGBGammaExpansion(inputData.Data[i + 2] / (float) 255);

        std::memset(&imageCopy->Data[i], ImageData::sRGBGammaCompression(res) * 255, imageCopy->ColorChannels);
    }

    return std::move(imageCopy);
}