/**
 * Creator:     VPR
 * Created:     March 20th, 2025
 * Updated:     March 20th, 2025
 *
 * Description: C++20 and onwards Obfuscator PoC for compile-time obfuscated strings.
 *              - Works on g++ using -Ofast/O3 optimization.
 *              - Does not use any stdlibc++ objects for linking.
 *
 * Disclaimer:  This program was designed as a proof-of-concept. It doesn't do
 *              anything malicious and it is not intended to do so. Don't try
 *              to use it for any malicious or illegal activity.
**/

#include "vpr/obf.hpp"

#include <cstdio>

int main() {
    fprintf(stdout, "Obfuscated text: %s\n", vpr::obf::obfuscator("A-very-obvious-string-that-would-be-noticable")() ); // invisible to grep -i Obfuscator-version-3

    return 0; 
}
