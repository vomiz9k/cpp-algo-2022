#include <stdio.h>

class Prism {
    double height;
public:
    Prism(double height) : height(height) {}
    virtual double Square() const = 0;
    double Volume() const {
        return height * Square();
    }
    // К этому классу есть одно замечание.
    // В качестве подсказки рекомендую еще раз посмотреть презентацию к первой лекции.
};

class Box: public Prism {
    double side;
public:
    Box(double height, double side)
        : Prism(height), side(side) {}

    virtual double Square() const override {
        return side * side;
    }
};

class Cube: public Box {
public:
    Cube(double side) : Box(side, side) {}
};

int main() {
    const Prism *p, *q, *r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);
    p = &a; q = &b; r = &c;
    printf("Squares: %3.3lf %3.3lf %3.3lf\n",p->Square(),q->Square(),r->Square());
    printf("Volumes: %3.3lf %3.3lf %3.3lf\n",p->Volume(),q->Volume(),r->Volume());
}
