//
// Created by kriz on 22.04.2022.
//

#include "AsciiArtEffect.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

AsciiArtEffect::AsciiArtEffect(ImageData &imageData, std::string &inputAlphabet, int colsX, float scale, std::ostream &outputStream) :
        ImageEffect(imageData),
        _inputAlphabet(inputAlphabet),
        _alphabetSize(inputAlphabet.size()-1),
        _valuesPerLine(imageData.Width * imageData.Channels),
        _outputStream(outputStream)
{
    SetTileWidthByRowLen(colsX);
    SetTileHeightByScalingFactor(scale);
}

AsciiArtEffect::AsciiArtEffect(ImageData &imageData, std::string &inputAlphabet, int tileWidth, int tileHeight, std::ostream &outputStream) :
        ImageEffect(imageData),
        _inputAlphabet(inputAlphabet),
        _alphabetSize(inputAlphabet.size()-1),
        _valuesPerLine(imageData.Width * imageData.Channels),
        _outputStream(outputStream)
{
    SetTileWidth(tileWidth);
    SetTileHeight(tileHeight);
}

void AsciiArtEffect::SetTileWidthByRowLen(int numOfCharsPerLine) {
    assert(("Too large number of letters per row!", numOfCharsPerLine <= _imageData.Width));
    _tileWidth = (_imageData.Width + numOfCharsPerLine - 1) / (numOfCharsPerLine);

}

void AsciiArtEffect::SetTileHeightByScalingFactor(float scalingFactor) {
    assert(("Given scaling factor is not allowed!", scalingFactor > 0 && scalingFactor <= 1));
    _tileHeight = _tileWidth / scalingFactor;
}

void AsciiArtEffect::SetTileHeight(int tileHeight) {
    assert(("Tile height is not valid!", tileHeight > 0 && tileHeight <= _imageData.Height));
    _tileHeight = tileHeight;
}

void AsciiArtEffect::SetTileWidth(int tileWidth) {
    assert(("Tile width is not valid!", tileWidth > 0 && tileWidth <= _imageData.Height));
    _tileHeight = tileWidth;
}
void AsciiArtEffect::ProcessImageData() {

    for (int i = 0; i < _imageData.Height; i += _tileHeight) {
        // per img line
        for (int j = 0; j < _valuesPerLine; j += _tileWidth * _imageData.Channels) {
            // convoluted data of matrix starting(top left value is) at j, i
            int averagedValue = ProcessTile(j, i);
            char outputChar = GetOutputCharMapping(averagedValue);
            // put calculated char into the output
            bool isLastTile = j +  _tileWidth * _imageData.Channels >= _valuesPerLine;
            PutCharacterToOutput(outputChar ,isLastTile);
        }
    }
}

int AsciiArtEffect::ProcessTile(int tileLeftX, int tileTopY) {
    // average the tiles pixel value and find letter in alphabet
    int sum = 0;

    int lastTilePixelY = tileTopY + _tileHeight;
    int lastTilePixelX = tileLeftX +  _tileWidth * _imageData.Channels;

    int offsetPosition = 0;
    for (int y = tileTopY; y < lastTilePixelY; ++y) {
        for (int x = tileLeftX; x < lastTilePixelX; x += _imageData.Channels) {
            offsetPosition = tileTopY * _valuesPerLine + x;

            sum += _imageData.Data[offsetPosition];
        }
    }

    // return averaged value
    return sum /(double) (_tileHeight * _tileWidth);
}

void AsciiArtEffect::PutCharacterToOutput(char outputLetter, bool isEnd) {

    _outputStream << outputLetter;

    if (isEnd)
        _outputStream << std::endl;
}

char AsciiArtEffect::GetOutputCharMapping(int value) {

    int alphabetIndex = (int)((value * (_alphabetSize-1)) /(double) _imageData.MaxChannelValue);
    assert(("Value is out of range", alphabetIndex < _alphabetSize && alphabetIndex >= 0));

    return _inputAlphabet[alphabetIndex];
}
