//
// Created by jens on 12/10/22.
//

#ifndef INC_LGEBRAIC_SYSTEM_FUNCTION_H
#define INC_LGEBRAIC_SYSTEM_FUNCTION_H

#include "binary-relation.h"

template<typename DomainType, typename CodomainType>
class BinaryFunction : protected BinaryRelation<DomainType, CodomainType> {
    // a function is a special binary relation which requires:
    // forall x1, x2: (x1 = x1 -> f(x1) = f(x2))

protected:
    using _t_bin_rel = BinaryRelation<DomainType, CodomainType>;    // binary relation type
    using _t_dom_set = typename _t_bin_rel::_t_dom_set;             // domain set type
    using _t_cod_set = typename _t_bin_rel::_t_cod_set;             // codomain set type
    using _t_ord_pair = typename _t_bin_rel::_t_ord_pair;           // ordered pair type
    using _t_2d_arr = typename std::vector<std::vector<int>>;       // 2d array of the binary relation type
    using _t_self = BinaryFunction<DomainType, CodomainType>;

    //    this->_domainSet: _t_dom_set;
    //    this->_codomainSet: _t_cod_set;
    //    this->_set: std::vector<OrderedPair<DomainType, CodomainType>>

    /**
     * checks is the given binary relation matrix is a function
     * forall x1, x2: (x1 = x2 -> f(x1) = f(x2))
     * @param a
     * @return
     */
    static bool _checkIsFunction(const _t_2d_arr &a) {
        for (int i = 0; i < a.size(); i++) { // for all x
            int per_row_count = 0;
            for (int j = 0; j < a[i].size(); j++) { // there can only be 1 y _s.t. f(x) = y
                if (a[i][j] == 1)                   // y1 != y2 -> (x1 != x2)
                    per_row_count++;
            }
            if (per_row_count != 1)
                return false;
        }
        return true;
    }

    /**
     * checks if the given binary relation matrix is injective
     * forall x1, x2: (x1 != x2 -> f(x1) != f(x2))
     * or
     * forall x1, x2: (f(x1) = f(x2) -> x1 = x2)
     * @param a
     * @return
     */
    static bool _checkInjective(const _t_2d_arr &a) {
        for (int j = 0; j < a[0].size(); j++) { // for all y
            int per_col_count = 0;
            for (int i = 0; i < a.size(); i++) { // there cannot be two xs that have the same y
                if (a[i][j] == 1)                // x1 != x2 -> f(x1) != f(x2)
                    per_col_count++;
            }
            if (per_col_count > 1)
                return false;
        }
        return true;
    }

    /**
     * checks if the given binary relation matrix is surjective
     * for all y: (exists only one x: (f(x) = y))
     * @param a
     * @return
     */
    static bool _checkSurjective(const _t_2d_arr &a) {
        for (int j = 0; j < a[0].size(); j++) { // for all y
            int per_col_count = 0;
            for (int i = 0; i < a.size(); i++) { // there must be an x _s.t. f(x) = y
                if (a[i][j] == 1)
                    per_col_count++;
            }
            if (per_col_count == 0)
                return false;
        }
        return true;
    }

    /**
     * count the number of y mapped from x given index in the relation matrix
     * @param x_idx index of x in the domain set
     * @param a relational matrix
     * @return
     */
    static int _yCountGivenX(int x_idx, const _t_2d_arr &a) {
        int count = 0;
        for (int j = 0; j < a[x_idx].size(); j++) {
            if (a[x_idx][j] == 1)
                count++;
        }
        return count;
    }


public:
    /**
     * construct a function from domain to codomain.
     * this function generates an empty relation from the given domain
     * to the given codomain which is not theoretically a function
     * if you wish to use it as a function, check your relation using functionReady()
     * @param domainSet
     * @param codomainSet
     */
    BinaryFunction(const _t_dom_set &domainSet, const _t_cod_set &codomainSet)
            : _t_bin_rel(domainSet, codomainSet) { // initialise its parent binary relation

    }

    /**
     * creates a binary function from the given binary relation
     * if the relation is not a function, it creates a null relation
     * use functionReady() to check is if it is a function
     * @param relation
     */
    BinaryFunction(const _t_bin_rel &relation): _t_bin_rel(relation.getDomainSet(), relation.getCodomainSet()) {
        if (_t_self::relationIsAFunction(relation)) {
            this->_s = relation.getRelationVector();
        }
    }

    /**
     * insert a pair into the relation.
     * only checks if <x,y> x in Domain and y in Codomain
     * it does not check is there are multiple map from pair.first i.e. x to y
     * use functionReady() function to check if the relation after modification is a function
     * @param pair
     * @return
     */
    virtual bool insertUnsafely(const _t_ord_pair &pair) {
        return _t_bin_rel::insert(pair);
    }

    /**
     * insert a pair into the function
     * it makes sure that there is only one map from pair.first to y
     * @param pair
     * @return
     */
    virtual bool insertSafely(const _t_ord_pair &pair) {
        int x_idx = this->_domainSet.findPos(pair.getFirst()); // find the index of x in the domain set 1d array
        if (_yCountGivenX(x_idx, _t_bin_rel::_transformRelation()) == 0) { // count the number of x in the relation matrix
            return insertUnsafely(pair);
        }
        return false;
    }

    /**
     * removes the given pair from the relation
     * it does not check if the domain' = domain i.e.
     * there may exists x in domain _s.t. x is not mapped to any element in the codomain
     * use functionReady() function to check if the relation after modification is a function
     * @param pair
     * @return
     */
    virtual bool removeUnsafely(const _t_ord_pair &pair) {
        return _t_bin_rel::remove(pair);
    }

    /**
     * remove the given pair from the relation
     * it makes sure the domain does not change after deletion
     * @param pair
     * @return
     */
    virtual bool removeSafely(const _t_ord_pair &pair) {
        int x_idx = this->_domainSet.findPos(pair.getFirst());
        if (_yCountGivenX(x_idx, _t_bin_rel::_transformRelation()) > 1) {
            return removeUnsafely(pair);
        }
        return false;
    }

    bool alter(const _t_ord_pair &pair) {
        return true;
    }

    /**
     * checks is this is a function
     * @return
     */
    bool isFunction() {
        return _checkIsFunction(_t_bin_rel::_transformRelation());
    }

    /**
     * checks is the function is injective
     * @return
     */
    bool isInjective() {
        return _checkInjective(_t_bin_rel::_transformRelation());
    }

    /**
     * checks if the function is surjective
     * @return
     */
    bool isSurjective() {
        return _checkSurjective(_t_bin_rel::_transformRelation());
    }

    friend std::ostream &operator<<(std::ostream &os, const _t_self &obj) {
        os << "doamin: " << obj._domainSet << std::endl;
        os << "codomain: " << obj._codomainSet << std::endl;
        for (int i = 0; i < obj._s.size(); i++) {
            os << obj._s[i] << " ";
        }
        return os;
    }

    /**
     * checks it the relation is a function
     * @param relation
     * @return
     */
    static bool relationIsAFunction(const _t_bin_rel &relation) {
        return _checkIsFunction(relation.toMatrix());
    }

    /**
     * checks if it is a function
     * might not be a function after creation, insertion or deletion
     * @return
     */
    bool functionReady() {
        return _checkIsFunction(_t_bin_rel::_transformRelation());
    }

};

#endif //INC_LGEBRAIC_SYSTEM_BINARY_FUNCTION_H
