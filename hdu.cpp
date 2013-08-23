#include <iostream>
using namespace std;

int log[100005];
void init(int n){
    log[1] = 0;
    for(int i = 2; i <= n; i++){
        log[i] = 31 - __builtin_clz(i-1);
    }
}
int main(){
}
