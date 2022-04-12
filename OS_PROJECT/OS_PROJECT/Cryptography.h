#ifndef CRYPTOGRAPHY_H_INCLUDED
#define CRYPTOGRAPHY_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;

namespace example
{
    class encdec
    {
        int key,k=0;
        string file;
        string s="";
        char c;
    public:
        void encrypt();
        void md5encrypt();
        void decrypt();
    };
}

#endif
