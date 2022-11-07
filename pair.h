//
// Created by jens on 12/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_PAIR_H
#define INC_ALGEBRAIC_SYSTEM_PAIR_H

template <typename First, typename Second>
class OrderedPair {
    // an ordered pair is demoted as <a, b> := {a, {b}}
    // typename First and Second are the types of the first element and second element
protected:
    using _t_ord_pair = OrderedPair<First, Second>;
    First _first;
    Second _second;

public:

    OrderedPair(const First &a, const Second &b) {
        this->_first = a;
        this->_second = b;
    }


    const First& getFirst() const {
        return this->_first;
    }
    const Second& getSecond() const {
        return this->_second;
    }
    void setFirst(const First &a) {
        this->_first = a;
    }
    void setSecond(const Second &b) {
        this->_second = b;
    }

    bool operator==(_t_ord_pair another) {
        return this->_first == another.getFirst() && this->_second == another.getSecond();
    }

    bool operator==(_t_ord_pair another) const {
        return this->_first == another.getFirst() && this->_second == another.getSecond();
    }

    bool operator!=(_t_ord_pair another) {
        return !operator==(another);
    }

    friend std::ostream &operator<<(std::ostream &os, const OrderedPair<First, Second> &obj) {
        os << "<" << obj._first << ", " << obj._second << ">";
        return os;
    }

};

#endif //INC_ALGEBRAIC_SYSTEM_PAIR_H