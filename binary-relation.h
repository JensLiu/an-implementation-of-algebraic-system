//
// Created by jens on 12/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H
#define INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H

#include "pair.h"
#include "set.h"

template <typename DomainType, typename CodomainType>
class BinaryRelation : protected Set<OrderedPair<DomainType, CodomainType>> {
    // binary relations are sets of ordered paris whose first element is in the domain
    // and second in the codomain. note that the codomain set is not necessarily its range

public:
    using _t_ord_pair = OrderedPair<DomainType, CodomainType>; // refers to the type of the ordered pairs
    // that makes up the set
    using _t_dom_set = Set<DomainType>; // refers to the type of its domain set
    using _t_cod_set = Set<CodomainType>; // refers to the type of its codomain
    using _t_pair_set = Set<_t_ord_pair>; // the set that stores the ordered pair

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
    BinaryRelation(const _t_dom_set& domainSet, const _t_cod_set& codomainSet) {
        _domainSet = domainSet;
        _codomainSet = codomainSet;
    }

    /**
     * insert an ordered pair <a,b> in R
     * @param pair
     * @return
     */
    bool insert(const _t_ord_pair &pair) override {
        std::cout << "[debug]: insert pair " << pair << std::endl;
        if (_valid_ord_pair(pair)) { // if the pair is valid
            // insert the pair into the ordered pair set
            // using the check function of Set<OrderedPair<DomainType, DocomainType>>
            // that checks if the ordered pair is already in the set
            std::cout << "[debug]: VALID" << std::endl;
            return _t_pair_set::insert(pair);
        }
        std::cout << "[debug]: INVALID" << std::endl;
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

};

#endif //INC_ALGEBRAIC_SYSTEM_BINARY_RELATION_H