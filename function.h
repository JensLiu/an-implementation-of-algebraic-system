//
// Created by jens on 12/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_FUNCTION_H
#define INC_ALGEBRAIC_SYSTEM_FUNCTION_H

#include "binary-relation.h"

template<typename DomainType, typename CodomainType>
class Function : protected BinaryRelation<DomainType, CodomainType> {
    // a function is a special binary relation which requires:
    // forall x1, x2, x3: (x1 = x1 -> f(x1) = f(x2))

protected:
    using _t_bin_rel = BinaryRelation<DomainType, CodomainType>; // binary relation type
    using _t_dom_set = typename _t_bin_rel::_t_dom_set; // domain set type
    using _t_cod_set = typename _t_bin_rel::_t_cod_set; // codomain set type
    using _t_ord_pair = typename _t_bin_rel::_t_ord_pair; // ordered pair type
    using _t_2d_arr = typename std::vector<std::vector<int>>; // 2d array of the binary relation type
    using _t_self = Function<DomainType, CodomainType>;

    /**
     * create an 2d matrix matching its size |Domain| x |Codomain|
     * @return
     */
    _t_2d_arr _create2DArray() {
        _t_2d_arr a;
        a.resize(this->_domainSet.size()); // resize rows to the size of the domain
        for (int i = 0; i < a.size(); i++) {
            a[i].resize(this->_codomainSet.size()); // each row, resize to the size of the codomain
        }
        return a;
    }

    /**
     * this function converts the set representation of the function
     * to the matrix representation of the function and uses the index of elements
     * in _domainSet: std::vector and _codomainSet: std::vector as the index in the matrix
     * @return
     */
    _t_2d_arr _transformRelation() {
        _t_2d_arr a = _create2DArray();
        for (int i = 0; i < this->_s.size(); i++) {
            _t_ord_pair pair = this->_s[i];
            int x_idx = this->_domainSet.findPos(pair.getFirst()); // O(size)
            int y_idx = this->_codomainSet.findPos(pair.getSecond()); // O(size)
            a[x_idx][y_idx] = 1;
        }
        for (int i = 0; i < this->_domainSet.size(); i++) {
            for (int j = 0; j < this->_codomainSet.size(); j++) {
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return a;
    }


    static bool _checkIsFunction(const _t_2d_arr &a) {
        for (int i = 0; i < a.size(); i++) {
            int per_row_count = 0;
            for (int j = 0; j < a[i].size(); j++) {
                if (a[i][j] == 1)
                    per_row_count++;
            }
            if (per_row_count != 1)
                return false;
        }
        return true;
    }

    static bool _checkInjective(const _t_2d_arr &a) {
        for (int j = 0; j < a[0].size(); j++) {
            int per_col_count = 0;
            for (int i = 0; i < a.size(); i++) {
                if (a[i][j] == 1)
                    per_col_count++;
            }
            if (per_col_count > 1)
                return false;
        }
        return true;
    }

    static bool _checkSurjective(const _t_2d_arr &a) {
        for (int j = 0; j < a[0].size(); j++) {
            int per_col_count = 0;
            for (int i = 0; i < a.size(); i++) {
                if (a[i][j] == 1)
                    per_col_count++;
            }
            if (per_col_count == 0)
                return false;
        }
        return true;
    }

    /**
     * count the number of x given index in the relation matrix
     * @param x_idx index of x in the domain set
     * @param a relational matrix
     * @return
     */
    static int _xCount(int x_idx, const _t_2d_arr &a) {
        int count = 0;
        for (int j = 0; j < a[x_idx].size(); j++) {
            if (a[x_idx][j] == 1)
                count++;
        }
        return count;
    }


public:
    /**
     * construct a function from domain to codomain
     * @param domainSet
     * @param codomainSet
     */
    Function(const _t_dom_set &domainSet, const _t_cod_set &codomainSet)
        : _t_bin_rel(domainSet, codomainSet) { // initialise its parent binary relation

    }

    /**
     * insert a pair into the function
     * @param pair
     * @return
     */
    bool insert(const _t_ord_pair &pair) {
        int x_idx = this->_domainSet.findPos(pair.getFirst()); // find the index of x in the domain set 1d array
        if (_xCount(x_idx, _transformRelation()) == 0) { // count the number of x in the relation matrix
            return _t_bin_rel::insert(pair);
        }
        return false;
    }

    // solve: this function does not work, you cannot remove an x since it maps to one and only one y
    bool remove(const _t_ord_pair &pair) {
        int x_idx = this->_domainSet.findPos(pair.getFirst());
        if (_xCount(x_idx, _transformRelation()) > 1) {
            return _t_bin_rel ::remove(pair);
        }
        return false;
    }

    bool alter(const _t_ord_pair &pair) {
        return false;
    }

    bool isFunction() {
        return _checkIsFunction(_transformRelation());
    }

    bool isInjective() {
        return _checkInjective(_transformRelation());
    }

    bool isSurjective() {
        return _checkSurjective(_transformRelation());
    }
    

    friend std::ostream &operator<<(std::ostream &os, const _t_self &obj) {
        os << "doamin: " << obj._domainSet << std::endl;
        os << "codomain: " << obj._codomainSet << std::endl;
        for (int i = 0; i < obj._s.size(); i++) {
            os << obj._s[i] << " ";
        }
        return os;
    }

};

#endif //INC_ALGEBRAIC_SYSTEM_FUNCTION_H