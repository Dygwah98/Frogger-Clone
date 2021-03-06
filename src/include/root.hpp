#ifndef ROOT_HPP
#define ROOT_HPP

#include<iostream>
#include<cmath>
#include<cassert>
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<memory>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

enum struct PanelType : int {EXIT = -1, MENU = 0, LEVEL = 1, OPTIONS = 2, WIN = 3, LOSS = 4};
enum struct Event : int { nd = -1, Exit = 0, Execute = 1, Redraw = 2, Pause = 3 };
enum struct Keys : int { nd = -1, UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, ENTER = 4 };
enum struct Collision : int { nd = -1, Log = 0, Deadly = 1, Arrival = 2 };

template<class T>
inline bool in_range(T lower, T val, T upper, bool loweq = true, bool upeq = true) {
    return (loweq ? val >= lower : val > lower) and (upeq ? upper >= val : upper > val);
}

template<class K, class V>
inline bool contains(const std::map<K, V>& map, const K& key) {
    return map.find(key) != map.end();
}

template<class V>
inline bool contains(const std::vector<V>& vec, int key) {
    return in_range<int>(0, key, vec.size(), true, false);
}

#endif