//
// Created by jens on 21/10/22.
//

#ifndef INC_ALGEBRAIC_SYSTEM_INPUTPARSE_H
#define INC_ALGEBRAIC_SYSTEM_INPUTPARSE_H

#include <iostream>
#include <cstring>
#include "set.h"
#include "pair.h"
using std::cout;
using std::endl;

const int BUFSIZE = 100;

#ifndef INT32_MAX
#define INT32_MAX 2147483647
#endif

Set<int> parseToIntSet(const char * input) {
    const int BUFSIZE = 100;
    char buf[BUFSIZE];
    Set<int> s;

    int i = 0;
    // find the start of the ordered pair
    while (input[i] != '{' && input[i] != '\0')
        i++;
    if (input[i] == '\0')
        return s;
    i++; // now i is the start of the first number

    while (input[i] != '\0') {
        int j = i;
        // find j that is the index of the first ','
        while (input[j] != ',' && input[j] != '}' && input[j] != '\0')
            j++;
        if (input[j] == '\0')
            return s;
        j--; // now j in the end of the number

//        cout << "[debug]: i=" << i << " j=" << j << endl;

        if (j-i+1 > BUFSIZE)
            cout << "[BUFFER ERROR]: too big" << endl;

        memcpy(buf, &input[i], j-i+1);
        buf[j-i+1] = '\0';

//        cout << "[debug]: buf " << buf << endl;
        // start parsing ----------------------------------------------------------------------
        int num;
        if (j == i && buf[0] == '0') {
            num = 0;
            s.insert(num);
        } else {
            num = atoi(buf);
            if (num == 0) {
                cout << "[INPUT ERROR]: '" << buf << "' is not a number, skip" << endl;
            } else {
                s.insert(num);
            }
        }

        if (input[j+1] == '}')
            break;

        // end parsing ---------------------------------------------------------------------

        i = j + 2;

        // skip spaces
        while (input[i] == ' ')
            i++;
    }
    return s;
}

/**
 * this function parses "<x, y>" string into an pair
 * @param s
 * @return
 */
bool __parseToIntPair(const char *s, OrderedPair<int, int> &toPair) {
    char buf[BUFSIZE];

    if (s[0] != '<') {
        return false;
    }

    // copy sub string into local buffer
    int len = strlen(s);
    if (len < 5 || s[len-1] != '>') // should have lease 5 characters
        return false;
    memcpy(buf, s, len);
    buf[len-1] = '\0';

    // find index of comma in the string i.e. <123123123,-1>
    int idx_comma = 1;
    while (buf[idx_comma] != ',' && buf[idx_comma] != '\0')
        idx_comma++;
    buf[idx_comma] = '\0';

    // now, buf is "<x\0y\0>", &buf[1] is "x\0" , &buf[idx_comma+1] is 'y\0"

    int x;
    if (buf[1] == '0' && idx_comma == 2) {
        x = 0;
    } else {
        x = atoi(&buf[1]);
        if (x == 0) {
            std::cout << "[ERROR]: " << &buf[1] << " not a number" << std::endl;
            x = INT32_MAX - 1;
        }
    }

    int y;
    if (buf[idx_comma+1] == '0' && buf[idx_comma+2] == '\0') {
        y = 0;
    } else {
        y = atoi(&buf[idx_comma+1]);
        if (y == 0) {
            std::cout << "[ERROR]: " << &buf[idx_comma+1] << " not a number" << std::endl;
            y = INT32_MAX - 1;
        }
    }

    toPair.setFirst(x);
    toPair.setSecond(y);

    return true;

}

OrderedPair<int, int> parseToIntPair(const char *s) {
    OrderedPair<int, int> p(INT32_MAX-1, INT32_MAX-1);
    if (__parseToIntPair(s, p)) {
        return p;
    }
    cout << "wrong";
    return p;
}

Set<OrderedPair<int, int>> parseToIntPairSet(const char *input) {
    char buf[BUFSIZE];
    Set<OrderedPair<int, int>> s;

    int i = 0;
    // find the start of the ordered pair
    while (input[i] != '{' && input[i] != '\0')
        i++;
    if (input[i] == '\0')
        return s;
    i++; // now i is the start of the first pair

    while (input[i] != '\0') {
        int j = i;
        while (input[i] != '<' && input[i] != '\0')
            i++;

        // find j that is the index of the first ','
//        while (input[j] != '{' && input[j] != '}' && input[j] != '\0')
        while (input[j] != '>' && input[j] != '\0')
            j++;
        if (input[j] == '\0')
            return s;
//        j--; // now j in the end of the pair
        // now j in the end of the pair

        if (j-i+1 > BUFSIZE)
            cout << "[BUFFER ERROR]: too big" << endl;

        memcpy(buf, &input[i], j-i+1);
        buf[j-i+1] = '\0';

        OrderedPair<int, int> pair = parseToIntPair(buf);
        if (pair.getFirst() != INT32_MAX-1 && pair.getSecond() != INT32_MAX-1) {
            s.insert(pair);
        }

        i = j + 2;

        // skip spaces
        while (input[i] == ' ')
            i++;
    }
    return s;
}

#endif //INC_ALGEBRAIC_SYSTEM_INPUTPARSE_H