/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_20480568_INCLUDED
#define BINARYDATA_H_20480568_INCLUDED

namespace BinaryData
{
    extern const char*   tkicon128_png;
    const int            tkicon128_pngSize = 3871;

    extern const char*   tkicon256_png;
    const int            tkicon256_pngSize = 7689;

    extern const char*   tkicon512_png;
    const int            tkicon512_pngSize = 16001;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
