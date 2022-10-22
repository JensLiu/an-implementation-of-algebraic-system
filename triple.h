//
// Created by jens on 22/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_TRIPLE_H
#define INC_ALGEBRAIC_SYSTEM_TRIPLE_H
#include "pair.h"

template<typename X, typename Y, typename Z>
class Triple {
protected:
    X _x;
    Y _y;
    Z _z;

public:
    Triple(X x, Y y, Z z) : _x(x), _y(y), _z(z) {
    }

    void setX(int x) {
        _x = x;
    }

    void setY(int y) {
        _y = y;
    }

    void setZ(int z) {
        _z = z;
    }

    X getX() {
        return _x;
    }

    Y getY() {
        return _y;
    }

    Z getZ() {
        return _z;
    }

    X getX() const {
        return _x;
    }

    Y getY() const {
        return _y;
    }

    Z getZ() const {
        return _z;
    }

    OrderedPair<OrderedPair<X, Y>, Z> toPair() {
        OrderedPair<X, Y> f(_x, _y);
        return OrderedPair<OrderedPair<X, Y>, Z>(f, _z);
    }

};

#endif //INC_ALGEBRAIC_SYSTEM_TRIPLE_H
