#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//ulong require ull in the end, max = 18446744073709551615ull
typedef unsigned long long ullong;
typedef unsigned long ulong;

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
    std::vector<char> v;
    //ullong getFromTo(const ullong data, int left, int right) {

    //}

public:
    Magma(int256 key): key{key}{};
    ullong encrypt(const ullong input){
        ullong left = input;
        ullong right = left & 0xffffffff;
        left >>= 32;
        return right;
    }
    int256 getKey() {
        return key;
    }
};

int main(){
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    Magma a(key);
    ullong message = a.encrypt(0b010101011010101);

    return 0;
}