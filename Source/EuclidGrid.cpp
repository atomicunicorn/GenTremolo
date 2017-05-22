//
//  Euclid.cpp
//  GenTremolo
//
//  Created by Zachary Gottesman on 5/21/17.
//
//

/* comments with "!!!" denote the changes from a 3-part drum sequencer to 
 * a 1-part effect (essentially amplitude being the only part) */

#include "EuclidGrid.h"

EuclidGrid::EuclidGrid()
{
    /* maybe map these to a different set of initializer constants? */
    mapX = defaultMapX;
    mapY = defaultMapY;
    randomness = defaultRandomness;
    patternStep = defaultPatternStep;
    perterbation = defaultPerterbation;
    density = defaultDensity;
    euclideanLength = defaultEuclideanLength;
    amplitude = defaultAmplitude;
    isOffNoteBool = defaulIsOffNoteBool;
}

EuclidGrid::~EuclidGrid()
{
}

void EuclidGrid::resetToDefault() {
    mapX = defaultMapX;
    mapY = defaultMapY;
    randomness = defaultRandomness;
    patternStep = defaultPatternStep;
    perterbation = defaultPerterbation;
    density = defaultDensity;
    euclideanLength = defaultEuclideanLength;
    amplitude = defaultAmplitude;
    isOffNoteBool = defaulIsOffNoteBool;
}

void EuclidGrid::reset() {
    euclideanStep = 0;
    patternStep = 0;
    state = 0;
    isOffNoteBool = false;
}

// TODO pass in the min and max beat values here to dicate return value range a bit
/* returns the length that the input audio will be played (think of as note duration) 
 * returned value represents the number of samples the "note" lasts. */
bool EuclidGrid::runGrid(long playHeadLocationBy32Notes, int samplesPerQuarterNote, euclidNote& noteStruct) {
    if (playHeadLocationBy32Notes < 0) {
        resetToDefault();
        return false;
    }
    isOffNoteBool = !isOffNoteBool; // TODO be careful of possible race condition here when the processor checks this value...
    
    noteStruct.isMuted = isOffNoteBool;
    
    patternStep = (int)(playHeadLocationBy32Notes % 32);
    state = 0;
    evaluatePattern();
    output();
    const int samplesPerPatternStep = samplesPerQuarterNote/stepsPerPattern;
    
    /* increment euclidean clock */
    euclideanStep = (euclideanStep + 1) % euclideanLength;
    
    int generatedNoteLengthInSamples = 0;
    if ((state & 1) > 0) { /* originally this would trigger the kick drum */
        generatedNoteLengthInSamples += samplesPerPatternStep*2;
    }
    if ((state & 2) > 0) { /* originally this would trigger the snare drum */
        generatedNoteLengthInSamples += samplesPerPatternStep*2;
    }
    if ((state & 4) > 0) { /* originally this would trigger the high hat */
        generatedNoteLengthInSamples += samplesPerPatternStep*4;
    }
//    return generatedNoteLengthInSamples;
    
    noteStruct.lengthInSamples = generatedNoteLengthInSamples;
    return true;
}

/* TODO maybe add more randomness to the instMask and accentBits? 
 * Also is instMask even needed? */
void EuclidGrid::evaluatePattern() {
    if (patternStep == 0) {
        randomness = randomness >> 2;
        unsigned int randSeed = (unsigned int)rand();
        unsigned int randTwo = randSeed%256;
        perterbation = (randTwo*randomness) >> 8;
    }
    unsigned int instMask = 1;
    unsigned int accentBits = 0;
    unsigned int level = readPatternMap();
    if (level < (255 - perterbation)) {
        level += perterbation;
    } else {
        level = 255;
    }
    unsigned int threshold = 255 - (density*2);
    if (level > threshold) {
        if (level > 192) {
            accentBits |= instMask;
        }
//        amplitude = level / 2;   // not actually used right now
        state |= instMask;
    }
    instMask <<= 1;
    state |= accentBits << 3;
}

// TODO maybe switch all these values over to uint8_t
int EuclidGrid::readPatternMap() { // originally referred to as readDrumMap
    unsigned int i = (unsigned int)floor(mapX*3.0 / 127);
    unsigned int j = (unsigned int)floor(mapY*3.0 / 127);
    
    uint32_t* mapA = beat_map[i][j];
    uint32_t* mapB = beat_map[i + 1][j];
    uint32_t* mapC = beat_map[i][j + 1];
    uint32_t* mapD = beat_map[i + 1][j + 1];
    
    int offset = stepsPerPattern + patternStep;
    uint32_t a = mapA[offset];
    uint32_t b = mapB[offset];
    uint32_t c = mapC[offset];
    uint32_t d = mapD[offset];
    uint32_t maxValue = 127;
    
    /* Below the non-function-call assignment of r is what was on the max patch version.
     * The uncommented assignment of r follows more in line with the U8Mix function
     * that is used on the grids hardware. */
    
    uint32_t r = (
                  (a * mapX + b * (maxValue - mapX)) * mapY
                  + (c * mapX + d * (maxValue - mapX)) * (maxValue - mapY)
                  ) / maxValue / maxValue;
//    uint32_t r = u32Mix(u32Mix(a, b, mapX << 2), u32Mix(c, d, mapX << 2), mapY << 2);
    return r;
}

uint32_t EuclidGrid::u32Mix(uint32_t first, uint32_t second, uint32_t maxVal) {
    if (maxVal == 255) {
        return second;
    }
    return maxVal*second + (255 - maxVal) * (first >> 8);
}

void EuclidGrid::output() {
}

int EuclidGrid::getMapX() {
    return mapX;
}

int EuclidGrid::getMapY() {
    return mapY;
}

int EuclidGrid::getRandomness() {
    return randomness;
}

int EuclidGrid::getDensity() {
    return density;
}

int EuclidGrid::getEuclideanLength() {
    return euclideanLength;
}

bool EuclidGrid::isOffNote() {
    return isOffNoteBool;
}

void EuclidGrid::setMapX(int x) {
    if (x >= 0 && x <= 127)
        mapX = (x % 256);
}

void EuclidGrid::setMapY(int y) {
    if (y >= 0 && y <= 127)
        mapY = y;
}

void EuclidGrid::setRandomness(int r) {
    if (r >= 0 && r <= 127)
        randomness = r;
}

void EuclidGrid::setDensity(int d) {
    if (d >= 0 && d <= 127)
        density = d;
}

void EuclidGrid::setEuclideanLength(int euclidLength) {
    if (euclidLength > 0 && euclidLength <= 32)
        euclideanLength = euclidLength;
}

uint32_t* EuclidGrid::getNodeByIndex(int index) {
    if (index < 0 || index > 24) {
        return nullptr;
    }
    switch (index) {
        case 0:
            return node_0;
        case 1:
            return node_1;
        case 2:
            return node_2;
        case 3:
            return node_3;
        case 4:
            return node_4;
        case 5:
            return node_5;
        case 6:
            return node_6;
        case 7:
            return node_7;
        case 8:
            return node_8;
        case 9:
            return node_9;
        case 10:
            return node_10;
        case 11:
            return node_11;
        case 12:
            return node_12;
        case 13:
            return node_13;
        case 14:
            return node_14;
        case 15:
            return node_15;
        case 16:
            return node_16;
        case 17:
            return node_17;
        case 18:
            return node_18;
        case 19:
            return node_19;
        case 20:
            return node_20;
        case 21:
            return node_21;
        case 22:
            return node_22;
        case 23:
            return node_23;
        case 24:
            return node_24;
        default:
            return nullptr;
    }
}

//uint32_t* EuclidGrid::getBeatMap() {
//    return beat_map;
//}

