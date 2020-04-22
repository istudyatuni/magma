#include <iostream>
#include <cmath>
using namespace std;

//ullong require ull in the end, max = 18446744073709551615ull
typedef unsigned long long ullong;  //64b
typedef unsigned long ulong;        //32b

class int256 {
    ullong bits[4];
public:
    int256(ullong b0, ullong b1, ullong b2, ullong b3):bits{b0, b1, b2, b3}{}
    ullong get(int i) {
        return bits[i];
    }
};

class Magma {
    int256 key;
    ullong mod32 = 0xffffffff;
    ulong keys[8];
    const int piBlock[8][16] = {
        {12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
        {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
        {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
        {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
        {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
        {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
        {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
        {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}
    };
    void setKeys() {
        for (int i = 0; i < 4; ++i) {
            ullong left = key.get(i);
            ullong right = left & mod32;
            left >>= 32;
            keys[i * 2] = left;
            keys[i * 2 + 1] = right;
        }
    }
    ulong f(ullong a, ullong x, int pi) {
        a += x;
        a &= mod32;
        int un[8];
        for (int i = 0; i < 8; ++i){
            x = a & 0xf;//4 numbers
            un[i] = x;
            a >>= 4;
        }
        for (int i = 0; i < 8; ++i) {
            un[i] = piBlock[pi][un[i]];
        }
        a = 0;
        for (int i = 0; i < 8; ++i) {
            a += un[i];
            a <<= 4;
        }
        a <<= 11;
        a &= mod32;
        return a;
    }
public:
    Magma(int256 key): key{key}{
        setKeys();
    }
    ullong encrypt(ullong data){
        ullong left = data;
        ullong right = left & mod32;
        left >>= 32;
        ulong xkey[32];
        for (int i = 0; i < 24; ++i) {
            xkey[i] = keys[i % 8];
        }
        for (int i = 7; i >= 0; --i) {
            xkey[32 - i - 1] = keys[i];
        }
        //rounds
        for (int i = 0; i < 31; ++i) {
            /* code */
        }
        return data;
    }
    int256 getKey() {
        return key;
    }
};

int main(){
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    Magma a(key);
    ullong message = a.encrypt(0xfedcba9876543210);
    //cout << "data = " << hex << message;
    return 0;
}//ru.wikipedia.org/wiki/ГОСТ_28147-89#Режим_простой_замены