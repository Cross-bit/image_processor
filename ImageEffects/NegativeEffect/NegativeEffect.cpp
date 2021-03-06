//
// Created by kriz on 21.04.2022.
//

#include "NegativeEffect.h"

#include "cassert"
#include "math.h"

NegativeEffect::NegativeEffect(ImageData& imageData) :
ImageEffect(imageData) {
SetIntensityCoef(1);
}

NegativeEffect::NegativeEffect(ImageData &imageData, float intensityCoef) : ImageEffect(imageData)
{
    SetIntensityCoef(intensityCoef);
}

void NegativeEffect::SetIntensityCoef(float value){
    if(value < 0 || value > 1)
        assert("Intensity coefficient must be in interval [0, 1]!");

    _intensityCoef = value;
}

void NegativeEffect::ProcessImageData() {

    if(_imageData.DataSize == 0)
        return;

    // create copy of original data
    _processedImage = std::make_unique<ImageData>(_imageData);

    for (int i = 0; i < _imageData.DataSize; ++i) {
        int dataTmp = _imageData.Data[i];
        _processedImage->Data[i] = dataTmp - _intensityCoef*(2*dataTmp - 255);
    }
}