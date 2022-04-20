//
// Created by kriz on 19.04.2022.
//

#ifndef MAIN_CPP_GRAYSCALEEFFECT_H
#define MAIN_CPP_GRAYSCALEEFFECT_H

#include "../ImageEffect.h"

#include "Algorithms/GrayscaleStrategyBase.h"


class GrayscaleEffect : public ImageEffect{
public:
    GrayscaleEffect(ImageData& _imageData, GrayscaleStrategyBase& grayscaleStrategy);

    GrayscaleEffect(ImageData& _imageData, GrayscaleStrategyBase& grayscaleStrategy, float r, float g, float b);

    void ApplyEffect() override;

private:
    GrayscaleStrategyBase& _effectStrategy;
};


#endif //MAIN_CPP_GRAYSCALEEFFECT_H