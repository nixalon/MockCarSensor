#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

int main() {
    int i;
    int x;
    for (x = 1; x < 11; x++) {
        ofstream outfile(string("Sensors") + to_string(x) + ".txt");
        sleep(1);
        for (i = 1; i < 237; i++) {
            if (x == 1){
                outfile << i << ":false;";
            }
            else if (i%20 == x - 1){
                outfile << i << ":true;";
            }
            else{
            outfile << i << ":false;";
            }
        }
        outfile.close();
    }



    return 0;
}
