#ifndef   VPR_OBF_UT_HEADER
#define   VPR_OBF_UT_HEADER

#include <cstdint>

struct local_callback {
    constexpr inline auto operator () (auto& dest, const auto& src, std::size_t size) const {
        for (std::size_t i = 0; i < size; ++i) {
            dest[i] = static_cast<uint8_t>(src[i] ^ 0x11);
        }
        return dest;
    }
};

#endif // VPR_OBF_UT_HEADER
