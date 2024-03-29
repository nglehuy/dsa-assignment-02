/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa
 * University
 * Description : library for Assignment 2 - Data structures and Algorithms -
 * Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "requestLib.h"

void loadRequests (char *fName, L1List<VM_Request> &rList) {
    // TODO: write your code to load requests. Each request is separated by a
    // whitespace
    ifstream f (fName);
    if (f) {
        string line;
        while (getline (f, line)) {
            if (line == "") continue;
            stringstream ss (line);
            string       s;
            while (ss >> s) {
                if (s[s.length () - 1] == ';') s.pop_back ();
                VM_Request rq (s);
                rList.insertTail (rq);
            }
        }
        f.close ();
    }
    else
        cout << "The file is not found!\n";
}
