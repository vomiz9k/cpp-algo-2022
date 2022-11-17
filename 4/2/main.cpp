import Example;

int main() {
    MyNamespace::A a;
    a.f();

    MyNamespace::B b;
    b.g();

    // MyNamespace::f_internal(); CE
}