/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   VCR_OSD_MONO_1_001_ttf;
    const int            VCR_OSD_MONO_1_001_ttfSize = 75864;

    extern const char*   VT323Regular_ttf;
    const int            VT323Regular_ttfSize = 153116;

    extern const char*   AlienEncountersBold_ttf;
    const int            AlienEncountersBold_ttfSize = 20140;

    extern const char*   AlienEncountersSolidBold_ttf;
    const int            AlienEncountersSolidBold_ttfSize = 17920;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 4;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
