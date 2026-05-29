#include "Game.hpp"
#include <locale>
#include <wchar.h>

int main() {
    std::locale::global(std::locale(""));
    game();
    return 0;
}