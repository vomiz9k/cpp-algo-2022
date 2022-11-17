// module;


// #include <iostream>

module Example:internals;

import <iostream>;

namespace MyNamespace {

void f_internal() { std::cout << "f_internal\n"; }
void g_internal() { std::cout << "g_internal\n"; }

}
