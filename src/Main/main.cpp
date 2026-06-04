#include "Game.hpp"
#include <locale>
#include <wchar.h>

int main() {
    std::locale::global(std::locale(""));
    
    Game().Play();

    return 0;
}