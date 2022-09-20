#include <string>

#include <exchange.h>


int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }

    Exchange::process(argv[1], argv[2], std::string(argv[3]) == "last");
}
