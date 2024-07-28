#include "lib/game.hpp"
#include <fcntl.h>
#include <io.h>
#include <wchar.h>

int main() {
    _setmode(_fileno(stdout), _O_U8TEXT);
    game();
    return 0;
}