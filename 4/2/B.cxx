export module Example:B;

import Example:internals;

namespace MyNamespace {

export class B {
public:
    void g() {
        g_internal();
    }
};

}
