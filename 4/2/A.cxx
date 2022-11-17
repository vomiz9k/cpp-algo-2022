export module Example:A;

import Example:internals;

namespace MyNamespace {

export class A {
public:
    void f() {
        f_internal();
    }
};

}