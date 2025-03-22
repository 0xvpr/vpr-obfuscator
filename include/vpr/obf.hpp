/**
 *
 * Version:     1.0.0
 *
 * Creator:     VPR
 * Contact:     admin@0xvpr.io
 *
 * Created:     March 21st, 2025
 * Updated:     March 22nd, 2025
 *
 * Description: A single-header-only library for compile-time obfuscated strings.
 *
 * License:     MIT -> https://mit-license.org/
 * Copyright:   VPR, 2025
 *
**/


#ifndef   VPR_OBF_HEADER
#define   VPR_OBF_HEADER

#ifndef   VPR_OBF_KEY
#define   VPR_OBF_KEY "DEFINE YOUR KEY"
#endif // VPR_OBF_KEY


#include  <cstdint>
#include  <array>


namespace vpr {
namespace obf {


template <typename Fptr>
concept is_callable = requires(Fptr fptr, std::uint8_t* dest, const std::uint8_t* src, std::size_t size) {
    { fptr(dest, src, size) } -> std::same_as<std::uint8_t *>;
};
template <typename Fptr>
concept is_destroyer = requires(Fptr fptr, std::uint8_t* dest, std::size_t size) {
    { fptr(dest, size) };
};


struct default_obfuscation_callback {
    constexpr inline auto operator () (auto& dest, const auto& src, std::size_t size) const {
        for (std::size_t i = 0; i < size; ++i) {
            dest[i] = static_cast<std::uint8_t>( ~(src[i] ^ static_cast<uint8_t>(VPR_OBF_KEY[i % sizeof(VPR_OBF_KEY)])) );
        }

        return dest;
    }
};
struct default_destruction_callback {
    constexpr inline auto operator () (auto& dest, std::size_t size) const {
        for (std::size_t i = 0; i < size; ++i) {
            dest[i] = 0;
        }
    }
};


template <std::size_t  size,
          typename     obfuscation_callback   = default_obfuscation_callback,
          typename     deobfuscation_callback = default_obfuscation_callback,
          typename     destruction_callback   = default_destruction_callback> requires is_callable<obfuscation_callback>   &&
                                                                                       is_callable<deobfuscation_callback> &&
                                                                                       is_destroyer<destruction_callback>
class [[nodiscard]] obfuscator {
    using data_t = std::array<std::uint8_t, size+1>;
public:
    consteval inline obfuscator(const char (&string)[size])
    : data{ [string]() -> auto {
                data_t tmp{};
                return obfuscation_callback{}(tmp, string, size);
            }() }
    , data_unenc{}
    {}

    constexpr inline ~obfuscator() {
        wipe();
    }

    constexpr inline void wipe() const {
        destruction_callback{}(data_unenc, size+1);
    }

    [[nodiscard]]
    volatile inline const char* operator () (bool force = false) const {
        if (force || data_unenc[0] == 0) {
            deobfuscation_callback{}(data_unenc, data, size+1);
        }

        return data_unenc;
    }
private:
    const data_t data;
    mutable volatile char data_unenc[size+1];
};


} // namespace obf
} // namespace vpr

#endif // VPR_OBF_HEADER
