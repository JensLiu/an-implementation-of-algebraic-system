//
// Created by jens on 12/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H
#define INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H

#include "pair.h"
#include "set.h"

template<typename DomainType, typename CodomainType>
class BinaryRelation : public Set<OrderedPair<DomainType, CodomainType>> {
    // binary relations are sets of ordered paris whose first element is in the domain
    // and second in the codomain. note that the codomain set is not necessarily its range

protected:
    using _t_ord_pair = OrderedPair<DomainType, CodomainType>; // refers to the type of the ordered pairs
    // that makes up the set
    using _t_self = Set<OrderedPair<DomainType, CodomainType>>;
    using _t_dom_set = Set<DomainType>; // refers to the type of its domain set
    using _t_cod_set = Set<CodomainType>; // refers to the type of its codomain
    using _t_pair_set = Set<_t_ord_pair>; // the set that stores the ordered pair
    using _t_2d_arr = std::vector<std::vector<int>>; // matrix rep of binary relation, A[x1][y1] = 1 means <x1,y1> in R
    using _t_const_std_vector = typename _t_self::_t_set_vec;

    _t_dom_set _domainSet;
    _t_cod_set _codomainSet;
    // this->_set: std::vector<OrderedPair<DomainType, CodomainType>>

    /**
     * this function returns if the pair inserted to this binary relation is valid
     * by checking if the corresponding first and second value
     * @param pair
     * @return
     */
    bool _valid_ord_pair(const _t_ord_pair &pair) {
        // a binary relation in on ComainSet x CodomainSet
        std::cout << "[debug]: domain check: " << _domainSet.find(pair.getFirst()) << std::endl;
        std::cout << "[debug]: codomain check: " << _codomainSet.find(pair.getSecond()) << std::endl;
        return _domainSet.find(pair.getFirst()) && _codomainSet.find(pair.getSecond());
    }

    /**
     * create an matrix with size |Domain| x |Codomain|
     * @return
     */
    _t_2d_arr _createMatrix() const {
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
    _t_2d_arr _transformRelation() const {
        _t_2d_arr a = _createMatrix();
        for (int i = 0; i < this->_s.size(); i++) { // O(relation*domain + relation*codomain)
            _t_ord_pair pair = this->_s[i];
            int x_idx = this->_domainSet.findPos(pair.getFirst()); // O(domain)
            int y_idx = this->_codomainSet.findPos(pair.getSecond()); // O(codomain)
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


public:
    /**
     * create a binary relationship from domain to codomain
     * it uses the copy constructor of each set
     * usually its a shallow copy
     * the set implementation uses std::vector<T>
     * so the copy of the set should be a deep copy
     * @param domainSet
     * @param codomainSet
     */
    BinaryRelation(const _t_dom_set &domainSet, const _t_cod_set &codomainSet) {
        _domainSet = domainSet;
        _codomainSet = codomainSet;
    }

    /**
     * insert an ordered pair <a,b> in R
     * @param pair
     * @return
     */
    bool insert(const _t_ord_pair &pair) override {
//        std::cout << "[debug]: insert pair " << pair << std::endl;
        if (_valid_ord_pair(pair)) { // if the pair is valid
            // insert the pair into the ordered pair set
            // using the check function of Set<OrderedPair<DomainType, DocomainType>>
            // that checks if the ordered pair is already in the set
//            std::cout << "[debug]: VALID" << std::endl;
            return _t_pair_set::insert(pair);
        }
//        std::cout << "[debug]: INVALID" << std::endl;
        return false;
    }

    /**
     * remove an ordered pair <a, b> from R
     * @param pair
     * @return
     */
    bool remove(const _t_ord_pair &pair) override {
        // no check needed, uses the remove function from Set<OrderedPair<DomainType, DocomainType>>
        return _t_pair_set::remove(pair);
    }

    friend std::ostream &operator<<(std::ostream &os, const BinaryRelation<DomainType, CodomainType> &obj) {
        os << "doamin: " << obj._domainSet << std::endl;
        os << "codomain: " << obj._codomainSet << std::endl;
        for (int i = 0; i < obj._s.size(); i++) {
            os << obj._s[i] << " ";
        }
        return os;
    }

    _t_dom_set getDomainSet() const {
        return _domainSet;
    }

    _t_cod_set getCodomainSet() const {
        return _codomainSet;
    }

    _t_const_std_vector getRelationVector() const {
        return this->_s;
    }

    _t_2d_arr toMatrix() const {
        return _transformRelation();
    }

};

#endif //INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H