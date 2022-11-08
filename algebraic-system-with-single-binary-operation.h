//
// Created by jens on 22/10/22.
//

#ifndef INC_ALGBRAIC_SYSTEM_ALGEBRAIC_SYSTEM_WITH_SINGLE_BINARY_OPERATION_H
#define INC_ALGBRAIC_SYSTEM_ALGEBRAIC_SYSTEM_WITH_SINGLE_BINARY_OPERATION_H

#include <iostream>
#include "set.h"
#include "triple.h"
template<typename SType>
class AlgebraicSystem {
    // an operation on a set is a function from S x S to S
    // it should be closed, thus we only need to store one S
    // this is implemented using a matrix structure which is dense, and is better

protected:
    using _t_triple = Triple<SType, SType, SType>;
    using _t_self = AlgebraicSystem<SType>;
    Set<SType> _s;
    int *_opMat;

    bool _safeToInsert(int x, int y, int z) {
        return x!=-1 && y!=-1 && z!=-1;
    }

    int _findIdx(const SType &elem) {
        return _s.findPos(elem);
    }

    bool _isAssociative() {
        int size = _s.size();
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                for (int z = 0; z < size; z++) {
                    if (_opMat[_opMat[x*size+y]*size + z] != _opMat[x*size + _opMat[y*size+z]])
                        return false;
                }
            }
        }
        return true;
    }

    bool _isCommutative() {
        int size = _s.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (_opMat[i*size + j] != _opMat[j*size + i])
                    return false;
            }
        }
        return true;
    }

//#define _elemCheck(var1, var2, var3) \
//    int size = _s.size(); \
//    for (int var1 = 0; var1 < size; var1++) { \
//        bool flag = true; \
//        for (int var2 = 0; var2 < size; var2++) { \
//            if (_opMat[x*size + y] != var3) \
//                flag = false; \
//        } \
//        if (flag) \
//        return var1; \
//    } \
//    return -1;

#define _elemCheck(var1, var2, var3) \
    std::vector<int> elems; \
    int size = _s.size(); \
    for (int var1 = 0; var1 < size; var1++) { \
        bool flag = true; \
        for (int var2 = 0; var2 < size; var2++) { \
            if (_opMat[x*size + y] != var3) \
                flag = false; \
        } \
        if (flag) elems.push_back(var1); \
    } \
    return elems;

    std::vector<int> _leftIdentityElement() {
        _elemCheck(x, y, y)
//        std::vector<int> elems;
//        int size = _s.size();
//        for (int x = 0; x < size; x++) {
//            bool idElem = true;
//            for (int y = 0; y < size; y++) {
//                if (_opMat[x*size + y] != y)
//                    idElem = false;
//            }
//            if (idElem)
//                elems.push_back(x);
//        }
//        return elems;
    }

    std::vector<int> _rightIdentityElement() {
        _elemCheck(y, x, x)
//        std::vector<int> elems;
//        int size = _s.size();
//        for (int y = 0; y < size; y++) {
//            bool idElem = true;
//            for (int x = 0; x < size; x++) {
//                if (_opMat[x*size + y] != x)
//                    idElem = false;
//            }
//            if (idElem)
//                elems.push_back(y);
//        }
//        return elems;
    }


    std::vector<int> _leftNullElement() {
        _elemCheck(x, y, x)
//        std::vector<int> elems;
//        int size = _s.size();
//        for (int x = 0; x < size; x++) {
//            bool nullElem = true;
//            for (int y = 0; y < size; y++) {
//                if (_opMat[x*size + y] != x)
//                    nullElem = false;
//            }
//            if (nullElem)
//                elems.push_back(x);
//        }
//        return elems;
    }

    std::vector<int> _rightNullElement() {
        _elemCheck(x, y, y)
//        std::vector<int> elems;
//        int size = _s.size();
//        for (int y = 0; y < size; y++) {
//            bool nullElem = true;
//            for (int x = 0; x < size; x++) {
//                if (_opMat[x*size + y] != y)
//                    nullElem = false;
//            }
//            if (nullElem)
//                elems.push_back(y);
//        }
//        return elems;
    }

#define _bothSideElement(type) std::vector<int> left = _left ## type ## Element(); \
    std::vector<int> right = _right ## type ## Element(); \
    if (left.size() == 1 && right.size() == 1) return left[0]; \
    return -1;

    int _identityElement() {
//        std::vector<int> left = _leftIdentityElement();
//        std::vector<int> right = _rightIdentityElement();
//        if (left.size() == 1 && right.size() == 1)
//            return left[0];
//        return -1;
        _bothSideElement(Identity)
    }

    int _nullElement() {
//        std::vector<int> left = _leftNullElement();
//        std::vector<int> right = _rightNullElement();
//        if (left.size() == 1 && right.size() == 1)
//            return left[0];
//        return -1;
        _bothSideElement(Null)
    }


    std::vector<int> _leftInverseElement(int x, int idElem) {
        std::vector<int> elems;
        int size = _s.size();
        for (int y = 0; y < size; y++) {
            if (_opMat[x*size + y] == idElem)
                elems.push_back(y);
        }
        return elems;
    }

    std::vector<int> _rightInverseElement(int y, int idElem) {
        std::vector<int> elems;
        int size = _s.size();
        for (int x = 0; x < size; x++) {
            if (_opMat[x*size + y] == idElem)
                elems.push_back(x);
        }
        return elems;
    }

    int _inverseElem(int x, int idElem) {
        std::vector<int> left = _leftInverseElement(x, idElem);
        std::vector<int> right = _rightInverseElement(x, idElem);
        if (left.size() == 1 && right.size() == 1)
            return left[0];
        return -1;
    }

    bool _allElemHasInverse(int idElem) {
        int size = _s.size();
        for (int i = 0; i < size; i++) {
            if (_inverseElem(i, idElem) == -1)
                return false;
        }
        return true;
    }

public:
    AlgebraicSystem(const Set<SType> &set) {
        _s = set;
        int size = _s.size();
        _opMat = new int[size*size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                _opMat[i*size + j] = -1;
            }
        }
    }

    bool isFullyInitialised() {
        return isClosed();
    }

    bool alter(const _t_triple &triple) {
        int x = _findIdx(triple.getX());
        int y = _findIdx(triple.getY());
        int z = _findIdx(triple.getZ());
        if (_safeToInsert(x, y, z)) {
            _opMat[x*_s.size() + y] = z;
            return true;
        }
        return false;
    }

    bool isClosed() {
        int size = _s.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (_opMat[i*size + j] == -1)
                    return false;
            }
        }
        return true;
    }

    bool isAssociative() {
        return _isAssociative();
    }

    bool isCommutative() {
        return _isCommutative();
    }

    bool isSemigroup() {
        return _isAssociative();
    }

    bool isMonoid() {
        return isSemigroup() && _identityElement() != -1;
    }

    bool isGroup() {
        return isMonoid() && _allElemHasInverse(_identityElement());
    }

    bool identityElement(SType &identity) {
        int i = _identityElement();
        if (i == -1)
            return false;
        identity = _s.elemAt(i);
        return true;
    }

    bool inverseElement(const SType &element, SType &inverse) {
        int idElem = _identityElement();
        if (idElem == -1)
            return false;
        int e_idx = _s.findPos(element);
        if (e_idx == -1)
            return false;
        int i = _inverseElem(e_idx, idElem);
        if (i == -1)
            return false;
        inverse = _s.elemAt(i);
        return true;
    }

    bool nullElement(SType &nullElement) {
        int i = _nullElement();
        if (i == -1)
            return false;
        nullElement = _s.findPos(i);
        return true;
    }


    friend std::ostream &operator<<(std::ostream &os, const _t_self &obj) {
        os << "algebraic system on set " << obj._s << std::endl;
        int size = obj._s.size();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                int z = obj._opMat[i*size + j];
                if (z == -1) {
                    os << "N ";
                } else {
                    os << obj._s.elemAt(z) << " ";
                }
            }
            os << std::endl;
        }
        return os;
    }



    ~AlgebraicSystem() {
        delete[] _opMat;
    }

};

#endif //INC_ALGBRAIC_SYSTEM_ALGEBRAIC_SYSTEM_WITH_SINGLE_BINARY_OPERATION_H
