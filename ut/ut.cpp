#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include "vpr/obf.hpp"
#include "ut/ut.hpp"

#include <string>

TEST_CASE("Basic obfuscation and deobfuscation") {
    constexpr const char original[] = "Hello, world!";
    vpr::obf::obfuscator obf(original);

    auto* decoded = obf();
    CHECK(std::string_view((char *)decoded) == original);
}

TEST_CASE("Multiple calls return same string") {
    constexpr const char original[] = "same_same_but_different";
    vpr::obf::obfuscator obf(original);

    auto* first = obf();
    auto* second = obf();
    CHECK(std::string_view((char *)first) == std::string_view((char *)second));
}

TEST_CASE("Wipe destroys decrypted data") {
    constexpr const char original[] = "wipe_me_down"; // shoutout to Boosie
    vpr::obf::obfuscator obf(original);

    auto* first = obf();
    obf.wipe();
    CHECK(std::string_view((char *)first).empty());
}

TEST_CASE("Obfuscator object destroys unencrypted data when leaving scope") {
    constexpr const char original[] = "the_destroyer_of_worlds";
    volatile char* data = nullptr;
    {
        vpr::obf::obfuscator obf(original);
        data = (char*)obf();
    }

    CHECK(std::string_view(const_cast<char *>(data)) != original);
}

TEST_CASE("Obfuscator object supports different encryption methods (asymmetric)") {
    constexpr const char original[] = "encode_deez";
    vpr::obf::obfuscator<sizeof(original),
                         local_callback>
                             obf(original);
    auto data = obf();

    CHECK(std::string_view(const_cast<char *>(data)) != original);
}

TEST_CASE("Obfuscator object supports different decryption methods") {
    constexpr const char original[] = "decode_deez";
    vpr::obf::obfuscator<sizeof(original),
                         vpr::obf::default_obfuscation_callback,
                         local_callback>
                             obf(original);

    auto data = obf();
    CHECK(std::string_view(const_cast<char *>(data)) != original);
}

