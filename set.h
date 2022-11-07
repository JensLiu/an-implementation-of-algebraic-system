//
// Created by jens on 12/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_SET_H
#define INC_ALGEBRAIC_SYSTEM_SET_H

#include <vector>

template<typename T>
class Set {
protected:
    using _t_set_vec = std::vector<T>;
    using _t_std_vec_itr = typename std::vector<T>::iterator;

    _t_set_vec _s;

    /**
     * this function finds the iterator to the element in the set
     * @param e
     * @return
     */
    _t_std_vec_itr _findItr(const T &e) {
        _t_std_vec_itr itr;
        for (itr = _s.begin(); itr != _s.end(); itr++) {
            if (*itr == e)
                break;
        }
        return itr;
    }

    /**
     * this function finds the index of the element in the set
     * @param elem
     * @return
     */
    int _findPos(const T &elem) const {
        int i;
        for (i = 0; i < _s.size(); i++) {
            if (_s[i] == elem)
                return i;
        }
        return -1;
    }

public:
    /**
     * this function insert one element to the set
     * it checks if the element is already in the set using == operator, please overload it
     * if you want to distinguish between two elements that has the same value
     * @param elem element
     * @return true if successful, false otherwise
     */
    virtual bool insert(const T &elem) {
        if (_findItr(elem) == _s.end()) { // if element is not in the set
            _s.push_back(elem); // add to it
            return true;
        }

        return false;
    }


    /**
     * this function removes one element from the set
     * it does not delete the element
     * please pass the exact element ( == returns true)
     * @param elem
     * @return true is successful, false otherwise
     */
     virtual bool remove(const T &elem) {
        _t_std_vec_itr itr = _findItr(elem);
        if (itr != _s.end()) { // if found
            _s.erase(itr); // remove
            return true;
        }
        return false;
    }

    /**
     * this function returns if an element is in the set
     * using the == operator. the set is unordered even though
     * it is implemented using std::vector<T> for convenience
     * @param elem
     * @return true if it is in the set, false otherwise
     */
    bool find(const T &elem) {
        return _findItr(elem) != _s.end();
    }

    /**
     * this function returns the size of the set
     * @return
     */
    int size() const {
        return _s.size();
    }

    /**
     * this function uses << operator to display each element in a row
     * @param os
     * @param obj
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Set<T> &obj) {
        for (int i = 0; i < obj._s.size(); i++)
            os << obj._s[i] << " ";
        return os;
    }

    /**
     * return the position in the set representation.
     * position may change if any element is removed
     * do not use it as the identifier
     * @param elem
     * @return
     */
    int findPos(const T &elem) const { // Cannot use a protected method when its child overrides a virtual function, why
        return _findPos(elem);
    }

    _t_set_vec getVector() const {
        return _s;
    }

    const T &elemAt(int idx) const {
        if (idx < 0 || idx > _s.size())
            return T();
        return _s.at(idx);
    }

    std::vector<T> getElements() const {
        return _s;
    }

};

#endif //INC_ALGEBRAIC_SYSTEM_SET_H