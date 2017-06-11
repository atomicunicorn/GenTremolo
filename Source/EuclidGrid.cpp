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
    state = defaultState;
    
    patternStep = 0;
    
    for (int i = 0; i < numParts; i++) {
        euclideanStep.push_back(defaultEuclideanStep);
        perterbation.push_back(defaultPerterbation);
        density.push_back(defaultDensity);
        amplitude.push_back(defaultAmplitude);
    }
    euclideanLength.push_back(5);
    euclideanLength.push_back(7);
    euclideanLength.push_back(11);
    
    isOffNoteBool = defaultIsOffNoteBool;
    buildBeatMap();
    
}

EuclidGrid::~EuclidGrid()
{
}

void EuclidGrid::resetToDefault() {
    mapX = defaultMapX;
    mapY = defaultMapY;
    randomness = defaultRandomness;
    patternStep = defaultPatternStep;
    isOffNoteBool = defaultIsOffNoteBool;
    state = defaultState;
    
    if (euclideanStep.size() == numParts && perterbation.size() == numParts && density.size() == numParts && euclideanLength.size() == numParts && amplitude.size() == numParts) {
        for (int i = 0; i < numParts; i++) {
            euclideanStep[i] = defaultEuclideanStep;
            perterbation[i] = defaultPerterbation;
            density[i] = defaultDensity;
            amplitude[i] = defaultAmplitude;
        }
    } else {
        euclideanStep.clear();
        perterbation.clear();
        density.clear();
        euclideanLength.clear();
        amplitude.clear();
        for (int i = 0; i < numParts; i++) {
            euclideanStep.push_back(defaultEuclideanStep);
            perterbation.push_back(defaultPerterbation);
            density.push_back(defaultDensity);
            amplitude.push_back(defaultAmplitude);
        }
    }
    euclideanLength.clear();
    euclideanLength.push_back(5);
    euclideanLength.push_back(7);
    euclideanLength.push_back(11);
}

// TODO pass in the min and max beat values here to dicate return value range a bit
/* returns the length that the input audio will be played (think of as note duration) 
 * returned value represents the number of samples the "note" lasts. */
void EuclidGrid::runGrid(const int playHeadLocationBy32Notes, const int noteSampleLength, EuclidNote& noteStruct) {
    if (playHeadLocationBy32Notes < 0) {
        resetToDefault();
        noteStruct.success = false;
        noteStruct.noteOn = false;
        noteStruct.lengthInSamples = 0;
        return;
    }
    noteStruct.noteOn = false;
    noteStruct.lengthInSamples = 0;
    
    patternStep = playHeadLocationBy32Notes % 32;
    state = 0;
    evaluatePattern();
    
    /* increment euclidean clock */
    for (int i = 0; i < numParts; i++) {
        euclideanStep[i] = (euclideanStep[i] + 1) % euclideanLength[i];
    }
    
    int noteLength = noteSampleLength;
    if ((state & 1) > 0) {                /* originally this would trigger the kick drum */
        noteLength += noteSampleLength;
        noteStruct.noteOn = true;
    }
    if ((state & 2) > 0) {               /* originally this would trigger the snare drum */
        noteLength = noteSampleLength;
        noteStruct.noteOn = true;
    }
    if ((state & 4) > 0) {              /* originally this would trigger the high hat */
        if (state % 2 == 0) {
            noteLength = noteSampleLength << 2;
        } else {
            noteLength = noteSampleLength >> 2;
        }
        noteStruct.noteOn = true;
    }
    noteStruct.lengthInSamples = (const int)noteLength;
    noteStruct.success = true;
}

void EuclidGrid::evaluatePattern() {
    if (patternStep == 0) {
        for (int i = 0; i < numParts; i++) {
            randomness = randomness >> 2;
            unsigned int randSeed = ((unsigned int)rand())%256;
            perterbation[i] = (randSeed*randomness) >> 8;
        }
    }
    unsigned int instMask = 1;
    unsigned int accentBits = 0;
    
    for (int i = 0; i < numParts; i++) {
        unsigned int level = readPatternMap(i);
        if (level < (255 - perterbation[i])) {
            level += perterbation[i];
        } else {
            level = 255;
        }
        unsigned int threshold = 255 - (density[i]*2);
        if (level > threshold) {
            if (level > 192) {
                accentBits |= instMask;
            }
            amplitude[i] = level / 2;   // not actually used right now
            state |= instMask;
        }
        instMask <<= 1;
    }
    
    state |= accentBits << 3;
}

int EuclidGrid::readPatternMap(int index) { // originally referred to as readDrumMap
    int i = (int)floorf(((float)mapX)*3.0f / 127.0f);
    int j = (int)floorf(((float)mapY)*3.0f / 127.0f);
    int offset = (index * stepsPerPattern) + patternStep;
    if (i > 3 || j > 3 || i < 0 || j < 0 || offset > 95 || offset < 0) {
        return 0;
    }

    uint32_t a = getLevelFromBeatMap(i, j, offset);
    uint32_t b = getLevelFromBeatMap(i + 1, j, offset);
    uint32_t c = getLevelFromBeatMap(i, j + 1, offset);
    uint32_t d = getLevelFromBeatMap(i + 1, j + 1, offset);
    
    /* Below the inline assignment of r is what was used in the max patch.
     * The uncommented assignment of r follows more with the U8Mix function
     * that is used on the grids hardware. */
    
    uint32_t r = (
                  (a * mapX + b * (maxValue - mapX)) * mapY + (c * mapX + d * (maxValue - mapX)) * (maxValue - mapY)
                  ) / maxValue / maxValue;
//    uint32_t r = u32Mix(u32Mix(a, b, mapX << 2), u32Mix(c, d, mapX << 2), mapY << 2);
    
    return r;
}

uint32_t EuclidGrid::getLevelFromBeatMap(int i, int j, int offset) {
    /* i is the beatmap's row, j is the column, and offset is the index within a given node */
    int beatMapOffset = i*5 + j;
    return beat_map[beatMapOffset][offset];
}

uint32_t EuclidGrid::u32Mix(uint32_t first, uint32_t second, uint32_t maxVal) {
    if (maxVal == 255) {
        return second;
    }
    return maxVal*second + (255 - maxVal) * (first >> 8);
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

int EuclidGrid::getDensity(int index) {
    if (index < 0 || index > numParts || index >= density.size())
        return -1;
    return density[index];
}

int EuclidGrid::getEuclideanLength(int index) {
    if (index < 0 || index > numParts || index >= euclideanLength.size())
        return -1;
    return euclideanLength[index];
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

void EuclidGrid::setDensity(int d, int index) {
    if (index < 0 || index > numParts || index >= density.size())
        return;
    if (d >= 0 && d <= 127)
        density[index] = d;
}

void EuclidGrid::setEuclideanLength(int euclidLength, int index) {
    if (index <= 0 || index > numParts || index >= euclideanLength.size())
        return;
    if (euclidLength > 0 && euclidLength <= 32)
        euclideanLength[index] = euclidLength;
}

/* Defines the contents of each node and the ordering of the beat map */
void EuclidGrid::buildBeatMap() {
    node_0 = {
        255,      0,      0,      0,      0,      0,    145,      0,
        0,      0,      0,      0,    218,      0,      0,      0,
        72,      0,     36,      0,    182,      0,      0,      0,
        109,      0,      0,      0,     72,      0,      0,      0,
        36,      0,    109,      0,      0,      0,      8,      0,
        255,      0,      0,      0,      0,      0,     72,      0,
        0,      0,    182,      0,      0,      0,     36,      0,
        218,      0,      0,      0,    145,      0,      0,      0,
        170,      0,    113,      0,    255,      0,     56,      0,
        170,      0,    141,      0,    198,      0,     56,      0,
        170,      0,    113,      0,    226,      0,     28,      0,
        170,      0,    113,      0,    198,      0,     85,      0
    };
    node_1  = {
        229,      0,     25,      0,    102,      0,     25,      0,
        204,      0,     25,      0,     76,      0,      8,      0,
        255,      0,      8,      0,     51,      0,     25,      0,
        178,      0,     25,      0,    153,      0,    127,      0,
        28,      0,    198,      0,     56,      0,     56,      0,
        226,      0,     28,      0,    141,      0,     28,      0,
        28,      0,    170,      0,     28,      0,     28,      0,
        255,      0,    113,      0,     85,      0,     85,      0,
        159,      0,    159,      0,    255,      0,     63,      0,
        159,      0,    159,      0,    191,      0,     31,      0,
        159,      0,    127,      0,    255,      0,     31,      0,
        159,      0,    127,      0,    223,      0,     95,      0
    };
    node_2 = {
        255,      0,      0,      0,    127,      0,      0,      0,
        0,      0,    102,      0,      0,      0,    229,      0,
        0,      0,    178,      0,    204,      0,      0,      0,
        76,      0,     51,      0,    153,      0,     25,      0,
        0,      0,    127,      0,      0,      0,      0,      0,
        255,      0,    191,      0,     31,      0,     63,      0,
        0,      0,     95,      0,      0,      0,      0,      0,
        223,      0,      0,      0,     31,      0,    159,      0,
        255,      0,     85,      0,    148,      0,     85,      0,
        127,      0,     85,      0,    106,      0,     63,      0,
        212,      0,    170,      0,    191,      0,    170,      0,
        85,      0,     42,      0,    233,      0,     21,      0
    };
    node_3 = {
        255,      0,    212,      0,     63,      0,      0,      0,
        106,      0,    148,      0,     85,      0,    127,      0,
        191,      0,     21,      0,    233,      0,      0,      0,
        21,      0,    170,      0,      0,      0,     42,      0,
        0,      0,      0,      0,    141,      0,    113,      0,
        255,      0,    198,      0,      0,      0,     56,      0,
        0,      0,     85,      0,     56,      0,     28,      0,
        226,      0,     28,      0,    170,      0,     56,      0,
        255,      0,    231,      0,    255,      0,    208,      0,
        139,      0,     92,      0,    115,      0,     92,      0,
        185,      0,     69,      0,     46,      0,     46,      0,
        162,      0,     23,      0,    208,      0,     46,      0
    };
    node_4 = {
        255,      0,     31,      0,     63,      0,     63,      0,
        127,      0,     95,      0,    191,      0,     63,      0,
        223,      0,     31,      0,    159,      0,     63,      0,
        31,      0,     63,      0,     95,      0,     31,      0,
        8,      0,      0,      0,     95,      0,     63,      0,
        255,      0,      0,      0,    127,      0,      0,      0,
        8,      0,      0,      0,    159,      0,     63,      0,
        255,      0,    223,      0,    191,      0,     31,      0,
        76,      0,     25,      0,    255,      0,    127,      0,
        153,      0,     51,      0,    204,      0,    102,      0,
        76,      0,     51,      0,    229,      0,    127,      0,
        153,      0,     51,      0,    178,      0,    102,      0
    };
    node_5 = {
        255,      0,     51,      0,     25,      0,     76,      0,
        0,      0,      0,      0,    102,      0,      0,      0,
        204,      0,    229,      0,      0,      0,    178,      0,
        0,      0,    153,      0,    127,      0,      8,      0,
        178,      0,    127,      0,    153,      0,    204,      0,
        255,      0,      0,      0,     25,      0,     76,      0,
        102,      0,     51,      0,      0,      0,      0,      0,
        229,      0,     25,      0,     25,      0,    204,      0,
        178,      0,    102,      0,    255,      0,     76,      0,
        127,      0,     76,      0,    229,      0,     76,      0,
        153,      0,    102,      0,    255,      0,     25,      0,
        127,      0,     51,      0,    204,      0,     51,      0
    };
    node_6 = {
        255,      0,      0,      0,    223,      0,      0,      0,
        31,      0,      8,      0,    127,      0,      0,      0,
        95,      0,      0,      0,    159,      0,      0,      0,
        95,      0,     63,      0,    191,      0,      0,      0,
        51,      0,    204,      0,      0,      0,    102,      0,
        255,      0,    127,      0,      8,      0,    178,      0,
        25,      0,    229,      0,      0,      0,     76,      0,
        204,      0,    153,      0,     51,      0,     25,      0,
        255,      0,    226,      0,    255,      0,    255,      0,
        198,      0,     28,      0,    141,      0,     56,      0,
        170,      0,     56,      0,     85,      0,     28,      0,
        170,      0,     28,      0,    113,      0,     56,      0
    };
    node_7 = {
        223,      0,      0,      0,     63,      0,      0,      0,
        95,      0,      0,      0,    223,      0,     31,      0,
        255,      0,      0,      0,    159,      0,      0,      0,
        127,      0,     31,      0,    191,      0,     31,      0,
        0,      0,      0,      0,    109,      0,      0,      0,
        218,      0,      0,      0,    182,      0,     72,      0,
        8,      0,     36,      0,    145,      0,     36,      0,
        255,      0,      8,      0,    182,      0,     72,      0,
        255,      0,     72,      0,    218,      0,     36,      0,
        218,      0,      0,      0,    145,      0,      0,      0,
        255,      0,     36,      0,    182,      0,     36,      0,
        182,      0,      0,      0,    109,      0,      0,      0
    };
    node_8 = {
        255,      0,      0,      0,    218,      0,      0,      0,
        36,      0,      0,      0,    218,      0,      0,      0,
        182,      0,    109,      0,    255,      0,      0,      0,
        0,      0,      0,      0,    145,      0,     72,      0,
        159,      0,      0,      0,     31,      0,    127,      0,
        255,      0,     31,      0,      0,      0,     95,      0,
        8,      0,      0,      0,    191,      0,     31,      0,
        255,      0,     31,      0,    223,      0,     63,      0,
        255,      0,     31,      0,     63,      0,     31,      0,
        95,      0,     31,      0,     63,      0,    127,      0,
        159,      0,     31,      0,     63,      0,     31,      0,
        223,      0,    223,      0,    191,      0,    191,      0
    };
    node_9 = {
        226,      0,     28,      0,     28,      0,    141,      0,
        8,      0,      8,      0,    255,      0,      8,      0,
        113,      0,     28,      0,    198,      0,     85,      0,
        56,      0,    198,      0,    170,      0,     28,      0,
        8,      0,     95,      0,      8,      0,      8,      0,
        255,      0,     63,      0,     31,      0,    223,      0,
        8,      0,     31,      0,    191,      0,      8,      0,
        255,      0,    127,      0,    127,      0,    159,      0,
        115,      0,     46,      0,    255,      0,    185,      0,
        139,      0,     23,      0,    208,      0,    115,      0,
        231,      0,     69,      0,    255,      0,    162,      0,
        139,      0,    115,      0,    231,      0,     92,      0
    };
    node_10 = {
        145,      0,      0,      0,      0,      0,    109,      0,
        0,      0,      0,      0,    255,      0,    109,      0,
        72,      0,    218,      0,      0,      0,      0,      0,
        36,      0,      0,      0,    182,      0,      0,      0,
        0,      0,    127,      0,    159,      0,    127,      0,
        159,      0,    191,      0,    223,      0,     63,      0,
        255,      0,     95,      0,     31,      0,     95,      0,
        31,      0,      8,      0,     63,      0,      8,      0,
        255,      0,      0,      0,    145,      0,      0,      0,
        182,      0,    109,      0,    109,      0,    109,      0,
        218,      0,      0,      0,     72,      0,      0,      0,
        182,      0,     72,      0,    182,      0,     36,      0
    };
    node_11 = {
        255,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    218,      0,     72,     36,
        0,      0,    182,      0,      0,      0,    145,    109,
        0,      0,    127,      0,      0,      0,     42,      0,
        212,      0,      0,    212,      0,      0,    212,      0,
        0,      0,      0,      0,     42,      0,      0,      0,
        255,      0,      0,      0,    170,    170,    127,     85,
        145,      0,    109,    109,    218,    109,     72,      0,
        145,      0,     72,      0,    218,      0,    109,      0,
        182,      0,    109,      0,    255,      0,     72,      0,
        182,    109,     36,    109,    255,    109,    109,      0
    };
    node_12 = {
        255,      0,      0,      0,    255,      0,    191,      0,
        0,      0,      0,      0,     95,      0,     63,      0,
        31,      0,      0,      0,    223,      0,    223,      0,
        0,      0,      8,      0,    159,      0,    127,      0,
        0,      0,     85,      0,     56,      0,     28,      0,
        255,      0,     28,      0,      0,      0,    226,      0,
        0,      0,    170,      0,     56,      0,    113,      0,
        198,      0,      0,      0,    113,      0,    141,      0,
        255,      0,     42,      0,    233,      0,     63,      0,
        212,      0,     85,      0,    191,      0,    106,      0,
        191,      0,     21,      0,    170,      0,      8,      0,
        170,      0,    127,      0,    148,      0,    148,      0
    };
    node_13 = {
        255,      0,      0,      0,      0,      0,     63,      0,
        191,      0,     95,      0,     31,      0,    223,      0,
        255,      0,     63,      0,     95,      0,     63,      0,
        159,      0,      0,      0,      0,      0,    127,      0,
        72,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,      0,      0,      0,      0,
        72,      0,     72,      0,     36,      0,      8,      0,
        218,      0,    182,      0,    145,      0,    109,      0,
        255,      0,    162,      0,    231,      0,    162,      0,
        231,      0,    115,      0,    208,      0,    139,      0,
        185,      0,     92,      0,    185,      0,     46,      0,
        162,      0,     69,      0,    162,      0,     23,      0
    };
    node_14 = {
        255,      0,      0,      0,     51,      0,      0,      0,
        0,      0,      0,      0,    102,      0,      0,      0,
        204,      0,      0,      0,    153,      0,      0,      0,
        0,      0,      0,      0,     51,      0,      0,      0,
        0,      0,      0,      0,      8,      0,     36,      0,
        255,      0,      0,      0,    182,      0,      8,      0,
        0,      0,      0,      0,     72,      0,    109,      0,
        145,      0,      0,      0,    255,      0,    218,      0,
        212,      0,      8,      0,    170,      0,      0,      0,
        127,      0,      0,      0,     85,      0,      8,      0,
        255,      0,      8,      0,    170,      0,      0,      0,
        127,      0,      0,      0,     42,      0,      8,      0
    };
    node_15 = {
        255,      0,      0,      0,      0,      0,      0,      0,
        36,      0,      0,      0,    182,      0,      0,      0,
        218,      0,      0,      0,      0,      0,      0,      0,
        72,      0,      0,      0,    145,      0,    109,      0,
        36,      0,     36,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    182,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,    109,
        218,      0,      0,      0,    145,      0,     72,     72,
        255,      0,     28,      0,    226,      0,     56,      0,
        198,      0,      0,      0,      0,      0,     28,     28,
        170,      0,      0,      0,    141,      0,      0,      0,
        113,      0,      0,      0,     85,     85,     85,     85
    };
    node_16 = {
        255,      0,      0,      0,      0,      0,     95,      0,
        0,      0,    127,      0,      0,      0,      0,      0,
        223,      0,     95,      0,     63,      0,     31,      0,
        191,      0,      0,      0,    159,      0,      0,      0,
        0,      0,     31,      0,    255,      0,      0,      0,
        0,      0,     95,      0,    223,      0,      0,      0,
        0,      0,     63,      0,    191,      0,      0,      0,
        0,      0,      0,      0,    159,      0,    127,      0,
        141,      0,     28,      0,     28,      0,     28,      0,
        113,      0,      8,      0,      8,      0,      8,      0,
        255,      0,      0,      0,    226,      0,      0,      0,
        198,      0,     56,      0,    170,      0,     85,      0
    };
    node_17 = {
        255,      0,      0,      0,      8,      0,      0,      0,
        182,      0,      0,      0,     72,      0,      0,      0,
        218,      0,      0,      0,     36,      0,      0,      0,
        145,      0,      0,      0,    109,      0,      0,      0,
        0,      0,     51,     25,     76,     25,     25,      0,
        153,      0,      0,      0,    127,    102,    178,      0,
        204,      0,      0,      0,      0,      0,    255,      0,
        0,      0,    102,      0,    229,      0,     76,      0,
        113,      0,      0,      0,    141,      0,     85,      0,
        0,      0,      0,      0,    170,      0,      0,      0,
        56,     28,    255,      0,      0,      0,      0,      0,
        198,      0,      0,      0,    226,      0,      0,      0
    };
    node_18 = {
        255,      0,      8,      0,     28,      0,     28,      0,
        198,      0,     56,      0,     56,      0,     85,      0,
        255,      0,     85,      0,    113,      0,    113,      0,
        226,      0,    141,      0,    170,      0,    141,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,      0,      0,    127,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        63,      0,      0,      0,    191,      0,      0,      0,
        255,      0,      0,      0,    255,      0,    127,      0,
        0,      0,     85,      0,      0,      0,    212,      0,
        0,      0,    212,      0,     42,      0,    170,      0,
        0,      0,    127,      0,      0,      0,      0,      0
    };
    node_19 = {
        255,      0,      0,      0,      0,      0,    218,      0,
        182,      0,      0,      0,      0,      0,    145,      0,
        145,      0,     36,      0,      0,      0,    109,      0,
        109,      0,      0,      0,     72,      0,     36,      0,
        0,      0,      0,      0,    109,      0,      8,      0,
        72,      0,      0,      0,    255,      0,    182,      0,
        0,      0,      0,      0,    145,      0,      8,      0,
        36,      0,      8,      0,    218,      0,    182,      0,
        255,      0,      0,      0,      0,      0,    226,      0,
        85,      0,      0,      0,    141,      0,      0,      0,
        0,      0,      0,      0,    170,      0,     56,      0,
        198,      0,      0,      0,    113,      0,     28,      0
    };
    node_20  = {
        255,      0,      0,      0,    113,      0,      0,      0,
        198,      0,     56,      0,     85,      0,     28,      0,
        255,      0,      0,      0,    226,      0,      0,      0,
        170,      0,      0,      0,    141,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,
        255,      0,    145,      0,    109,      0,    218,      0,
        36,      0,    182,      0,     72,      0,     72,      0,
        255,      0,      0,      0,      0,      0,    109,      0,
        36,      0,     36,      0,    145,      0,      0,      0,
        72,      0,     72,      0,    182,      0,      0,      0,
        72,      0,     72,      0,    218,      0,      0,      0,
        109,      0,    109,      0,    255,      0,      0,      0
    };
    node_21 = {
        255,      0,      0,      0,    218,      0,      0,      0,
        145,      0,      0,      0,     36,      0,      0,      0,
        218,      0,      0,      0,     36,      0,      0,      0,
        182,      0,     72,      0,      0,      0,    109,      0,
        0,      0,      0,      0,      8,      0,      0,      0,
        255,      0,     85,      0,    212,      0,     42,      0,
        0,      0,      0,      0,      8,      0,      0,      0,
        85,      0,    170,      0,    127,      0,     42,      0,
        109,      0,    109,      0,    255,      0,      0,      0,
        72,      0,     72,      0,    218,      0,      0,      0,
        145,      0,    182,      0,    255,      0,      0,      0,
        36,      0,     36,      0,    218,      0,      8,      0
    };
    node_22 = {
        255,      0,      0,      0,     42,      0,      0,      0,
        212,      0,      0,      0,      8,      0,    212,      0,
        170,      0,      0,      0,     85,      0,      0,      0,
        212,      0,      8,      0,    127,      0,      8,      0,
        255,      0,     85,      0,      0,      0,      0,      0,
        226,      0,     85,      0,      0,      0,    198,      0,
        0,      0,    141,      0,     56,      0,      0,      0,
        170,      0,     28,      0,      0,      0,    113,      0,
        113,      0,     56,      0,    255,      0,      0,      0,
        85,      0,     56,      0,    226,      0,      0,      0,
        0,      0,    170,      0,      0,      0,    141,      0,
        28,      0,     28,      0,    198,      0,     28,      0
    };
    node_23 = {
        255,      0,      0,      0,    229,      0,      0,      0,
        204,      0,    204,      0,      0,      0,     76,      0,
        178,      0,    153,      0,     51,      0,    178,      0,
        178,      0,    127,      0,    102,     51,     51,     25,
        0,      0,      0,      0,      0,      0,      0,     31,
        0,      0,      0,      0,    255,      0,      0,     31,
        0,      0,      8,      0,      0,      0,    191,    159,
        127,     95,     95,      0,    223,      0,     63,      0,
        255,      0,    255,      0,    204,    204,    204,    204,
        0,      0,     51,     51,     51,     51,      0,      0,
        204,      0,    204,      0,    153,    153,    153,    153,
        153,      0,      0,      0,    102,    102,    102,    102
    };
    node_24 = {
        170,      0,      0,      0,      0,    255,      0,      0,
        198,      0,      0,      0,      0,     28,      0,      0,
        141,      0,      0,      0,      0,    226,      0,      0,
        56,      0,      0,    113,      0,     85,      0,      0,
        255,      0,      0,      0,      0,    113,      0,      0,
        85,      0,      0,      0,      0,    226,      0,      0,
        141,      0,      0,      8,      0,    170,     56,     56,
        198,      0,      0,     56,      0,    141,     28,      0,
        255,      0,      0,      0,      0,    191,      0,      0,
        159,      0,      0,      0,      0,    223,      0,      0,
        95,      0,      0,      0,      0,     63,      0,      0,
        127,      0,      0,      0,      0,     31,      0,      0
    };
    
    beat_map = {
        node_10, node_8, node_0, node_9, node_11,
        node_15, node_7, node_13, node_12, node_6,
        node_18, node_14, node_4, node_5, node_3,
        node_23, node_16, node_21, node_1, node_2,
        node_24, node_19, node_17, node_20, node_22
    };
    
}

/* for hand-testing only. comment out the main function during plugin generation.
 * build via         g++ -std=c++11 EuclidGrid.cpp -o egTest                      */

//int main() {
//    printf("Creating EuclidGrid object...\n");
//    int samplesPerQuarterNote = 22050;
//    int samplesPer16thNote = (int)floorf((float)samplesPerQuarterNote/4.0f);
//    int egNoteLength = 0;
//    EuclidGrid eg = EuclidGrid();
//    EuclidGrid::EuclidNote noteStruct = {};
//    std::vector<std::vector<uint32_t>> nodes;
//    nodes = {
//        eg.node_0,
//        eg.node_1,
//        eg.node_2,
//        eg.node_3,
//        eg.node_4,
//        eg.node_5,
//        eg.node_6,
//        eg.node_7,
//        eg.node_8,
//        eg.node_9,
//        eg.node_10,
//        eg.node_11,
//        eg.node_12,
//        eg.node_13,
//        eg.node_14,
//        eg.node_15,
//        eg.node_16,
//        eg.node_17,
//        eg.node_18,
//        eg.node_19,
//        eg.node_20,
//        eg.node_21,
//        eg.node_22,
//        eg.node_23,
//        eg.node_24
//    };
//    /* Examine size of each node */
//    for (int i = 0; i < 25; i++) {
//        printf("nodes[%d] size: %d\n", i, (int)nodes[i].size());
//    }
//    /* Examine return values for one pattern run (one bar) */
//    for (int i = 0; i < 64; i++) {
//        printf("\n");
//        printf("calling runGrid on pattern step %d\n", i);
//        noteStruct = {};
//        eg.runGrid(i, samplesPer16thNote, noteStruct);
//        egNoteLength = noteStruct.lengthInSamples;
//        printf("grid state variable: %d\n", eg.state);
//        printf("noteStruct.isOn: ");
//        printf(noteStruct.noteOn ? "true\n" : "false\n");
//        printf("noteStruct.lengthInSamples: %d\n", noteStruct.lengthInSamples);
//        printf("noteStruct.success: %d\n", noteStruct.success);
//        printf("note length from runGrid call on step %d", i);
//        printf(": %d\n", egNoteLength);
//    }
//    printf("samplesPer16thNote: %d\n", samplesPer16thNote);
//    printf("node_0 length: %d\n", (int)eg.node_0.size());
//    printf("beat_map size: %d\n", (int)eg.beat_map.size());
//    printf("done.\n");
//    return 0;
//}

