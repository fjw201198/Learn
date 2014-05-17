#include <iostream>
#include "basic_atom.h"

int main() {
    using atom_int=basic_atom<int>;
    atom_int x;
    std::cout << ++x << std::endl;
    return 0;
}
