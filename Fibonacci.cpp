#include <iostream>
#include <fstream>
#define MAX 60

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

long long int memo[MAX];

long long int fibonacci(long long int n){
    if(n==2 || n==1)
        return 1;
    if(memo[n]!=0)
        return memo[n];
    memo[n]=fibonacci(n-1)+fibonacci(n-2);
    return memo[n];
}

int main()
{
    long long int n;
    for(int i=0; i<100; i++){
        in>>n;
        out << fibonacci(n) << endl;
    }
    return 0;
}
