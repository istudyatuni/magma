#include <iostream>
#include <cmath>
using namespace std;
//ulong require ull in the end, max = 18446744073709551615ull

class Magma {
    ulong key;
public:
    Magma(ulong key): key{key}{};
    ulong encrypt(ulong data){
        return data;
    }
};

int main(){
    Magma a(0x3f43def);
    ulong message = a.encrypt(0x3428);
    cout << message;
    return 0;
}