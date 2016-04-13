#include <string>
#include <locale>
#include <codecvt>

template <typename T>
std::string toUTF8(
    const std::basic_string<T, std::char_traits<T>, std::allocator<T>>& source
) {
    std::string result;

    std::wstring_convert<std::codecvt_utf8_utf16<T>, T> convertor;
    result = convertor.to_bytes(source);

    return result;
}
