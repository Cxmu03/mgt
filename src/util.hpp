#include <algorithm>

template <typename C, typename V>
constexpr inline bool contains(const C& container, V value) {
    return std::find(container.begin(), container.end(), value) != container.end();    
}
