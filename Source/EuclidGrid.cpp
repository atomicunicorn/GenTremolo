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
    
    randObj = Random::Random();
    
    patternStep = 0;
    
    for (int i = 0; i < numParts; i++) {
        euclideanStep.push_back(defaultEuclideanStep);
        perterbation.push_back(defaultPerterbation);
        density.push_back(defaultDensity);
        euclideanLength.push_back(defaultEuclideanLength);
        amplitude.push_back(defaultAmplitude);
    }
    
    isOffNoteBool = defaultIsOffNoteBool;
    
    node_0.push_back(255);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(145);
    node_0.push_back(0);
    
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(218);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    
    node_0.push_back(72);
    node_0.push_back(36);
    node_0.push_back(0);
    node_0.push_back(182);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    
    node_0.push_back(109);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(72);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    
    node_0.push_back(36);
    node_0.push_back(0);
    node_0.push_back(109);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(8);
    node_0.push_back(0);
    
    node_0.push_back(255);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(72);
    node_0.push_back(0);
    
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(182);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(36);
    node_0.push_back(0);
    
    node_0.push_back(218);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(145);
    node_0.push_back(0);
    node_0.push_back(0);
    node_0.push_back(0);
    
    node_0.push_back(170);
    node_0.push_back(0);
    node_0.push_back(113);
    node_0.push_back(0);
    node_0.push_back(255);
    node_0.push_back(0);
    node_0.push_back(56);
    node_0.push_back(0);
    
    node_0.push_back(170);
    node_0.push_back(0);
    node_0.push_back(141);
    node_0.push_back(0);
    node_0.push_back(198);
    node_0.push_back(0);
    node_0.push_back(56);
    node_0.push_back(0);
    
    node_0.push_back(170);
    node_0.push_back(0);
    node_0.push_back(113);
    node_0.push_back(0);
    node_0.push_back(226);
    node_0.push_back(0);
    node_0.push_back(28);
    node_0.push_back(0);
    
    node_0.push_back(170);
    node_0.push_back(0);
    node_0.push_back(113);
    node_0.push_back(0);
    node_0.push_back(198);
    node_0.push_back(0);
    node_0.push_back(85);
    node_0.push_back(0);
    
    beat_map.push_back(node_0);
    
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
    randObj = Random::Random();
    
    if (euclideanStep.size() == numParts && perterbation.size() == numParts && density.size() == numParts && euclideanLength.size() == numParts && amplitude.size() == numParts) {
        for (int i = 0; i < numParts; i++) {
            euclideanStep[i] = defaultEuclideanStep;
            perterbation[i] = defaultPerterbation;
            density[i] = defaultDensity;
            euclideanLength[i] = defaultEuclideanLength;
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
            euclideanLength.push_back(defaultEuclideanLength);
            amplitude.push_back(defaultAmplitude);
        }
    }
}

// TODO pass in the min and max beat values here to dicate return value range a bit
/* returns the length that the input audio will be played (think of as note duration) 
 * returned value represents the number of samples the "note" lasts. */
bool EuclidGrid::runGrid(long playHeadLocationBy32Notes, int samplesPerQuarterNote, int noteSampleLength, EuclidNote& noteStruct) {
    if (playHeadLocationBy32Notes < 0) {
        resetToDefault();
        return false;
    }
    
    patternStep = playHeadLocationBy32Notes % 32;
    state = 0;
    evaluatePattern();
    /* increment euclidean clock */
    for (int i = 0; i < numParts; i++) {
        euclideanStep[i] = (euclideanStep[i] + 1) % euclideanStep[i];
    }
    
    int noteLength = noteSampleLength;
    noteStruct.noteOn = true;
    
    if ((state & 1) > 0) { /* originally this would trigger the kick drum */
        noteLength += 1; // dummy placeholder
    }
    if ((state & 2) > 0) { /* originally this would trigger the snare drum */
        noteStruct.noteOn = true;
        noteLength += noteSampleLength*2;
    }
    if ((state & 4) > 0) { /* originally this would trigger the high hat */
//        generatedNoteLengthInSamples += samplesPerPatternStep*4;
        noteLength += noteSampleLength*4;
    }
    
    noteStruct.lengthInSamples = noteLength;
    return true;
}

/* TODO maybe add more randomness to the instMask and accentBits? 
 * Also is instMask even needed? */
void EuclidGrid::evaluatePattern() {
    if (patternStep == 0) {
        for (int i = 0; i < numParts; i++) {
            randomness = randomness >> 2;
//            unsigned int randSeed = (unsigned int)rand();
            unsigned int randSeed = (unsigned int)randObj.nextInt();
            unsigned int randTwo = randSeed%256;
            perterbation[i] = (randTwo*randomness) >> 8;
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
//          amplitude[i] = level / 2;   // not actually used right now
            state |= instMask;
        }
        instMask <<= 1;
    }
    
    state |= accentBits << 3;
}

int EuclidGrid::readPatternMap(int index) { // originally referred to as readDrumMap
    int i = (int)floor(mapX*3.0 / 127);
    int j = (int)floor(mapY*3.0 / 127);
    int offset = (index * stepsPerPattern) + patternStep;

    uint32_t a = getLevelFromBeatMap(i, j, offset);
    uint32_t b = getLevelFromBeatMap(i + 1, j, offset);
    uint32_t c = getLevelFromBeatMap(i, j + 1, offset);
    uint32_t d = getLevelFromBeatMap(i + 1, j + 1, offset);
    
    /* Below the inline assignment of r is what was used in the max patch.
     * The uncommented assignment of r follows more with the U8Mix function
     * that is used on the grids hardware. */
    
    uint32_t r = (
                  (a * mapX + b * (maxValue - mapX)) * mapY
                  + (c * mapX + d * (maxValue - mapX)) * (maxValue - mapY)
                  ) / maxValue / maxValue;
//    uint32_t r = u32Mix(u32Mix(a, b, mapX << 2), u32Mix(c, d, mapX << 2), mapY << 2);
    
    return r;
}

uint32_t EuclidGrid::getLevelFromBeatMap(int i, int j, int offset) {
    /* i is the beatmap's row, j is the column, and offset is the index within a given node */
    if (i > 4 || j > 4 || i < 0 || j < 0 || offset > 95 || offset < 0) {
        return 0;
    }
    int beatMapOffset = i*5 + j;
    if (beat_map.empty() || beat_map.size() <= beatMapOffset) {
        return 0;
    }
    if (beat_map.empty() || beat_map[beatMapOffset].size() <= offset) {
        return 0;
    }
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
    if (index < 0 || index > numParts || index >= euclideanLength.size())
        return;
    if (euclidLength > 0 && euclidLength <= 32)
        euclideanLength[index] = euclidLength;
}

std::vector<uint32_t> EuclidGrid::getNodeFromBeatMap(int i, int j) {
    /* variable i is synonymous to the row, j to the column */
//    int nodeIndex = (i*5) + j;
//    return EuclidGrid::beat_map[nodeIndex];
    return node_0;
}

