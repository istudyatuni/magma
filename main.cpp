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
    void setKeys() {
        for (int i = 0; i < 4; ++i) {
            ullong left = key.get(i);
            ullong right = left & mod32;
            left >>= 32;
            keys[i] = left;
            keys[i + 1] = right;
        }
    }
    ulong f(ullong a, ullong x) {
        //lose original a and x
        a += x;
        a &= mod32;
        int un[8];
        for (int i = 0; i < 8; ++i){
            x = a & 0xf;//4 numbers
            un[i] = x;
            a >>= 4;
        }
        int testSblosk[16] = {1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12};
        for (int i = 0; i < 8; ++i) {
            un[i] = testSblosk[un[i]];
        }
        cout << "a = " << a << endl;
        a = 0;
        for (int i = 0; i < 8; ++i) {
            a += un[i];
            a <<= 4;
        }
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
            xkey[i] = keys[i % 7];
        }
        for (int i = 7; i >= 0; --i) {
            xkey[32 - i -1] = keys[i];
        }
        data = f(left, xkey[0]);
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
    cout << "data = " << message;
    return 0;
}//ru.wikipedia.org/wiki/ГОСТ_28147-89#Режим_простой_замены