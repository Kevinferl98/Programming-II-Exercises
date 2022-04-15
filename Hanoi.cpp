#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void Hanoi(int discs, int from, int to, int intermediate, int &moves, const int stop){
    if(discs==1){
        moves++;
        if(moves==stop)
            out << from << " " << to << endl;
    }
    else{
        Hanoi(discs-1, from, intermediate, to, moves, stop);
        moves++;
        if(moves==stop)
            out << from << " " << to << endl;
        Hanoi(discs-1, intermediate, to, from, moves, stop);
    }
}

int main()
{
    int discs; int stop;
    for(int i=0; i<100; i++){
        in>>discs; in>>stop;
        int moves=0;
        Hanoi(discs, 1, 3, 2, moves, stop);
    }
    return 0;
}
