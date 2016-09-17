#include <iostream>
#include <sstream>
using namespace std;

int main() {

    short int enterVal;
    cout << "enter a number to say: " << endl;
    cin >> enterVal;
    ostringstream buff;
    buff << "say " << enterVal;
    system(buff.str().c_str());

    return 0;
}