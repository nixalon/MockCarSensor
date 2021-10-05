#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <bitset>

using namespace std;

void compareSensorData(array<bool, 236> sensorData, int fileNumber);

string getFileName(int i){
    string fileName = string("Sensors") + to_string(i) + ".txt";
    return fileName;
}

template <typename T>
string bin_str8(T n) {
    bitset<8> bs(n);
    return bs.to_string();
}

// bits =  0 1 0 1 0 1 0 1
// cnt = 4
// bit = 0 0 0 1 0 0 0 0
unsigned char* playWithData(array<bool, 236> currentSensorData) {
    int bitCount = 0;
    int byteCount = 0;
    auto *sensorBytes = new unsigned char[30];
    for(auto value : currentSensorData) {
        if(value) {
            int bit = (1) << bitCount;
            sensorBytes[byteCount] |= bit;
        }
        if(bitCount++ >= 8) {
            byteCount++;
            bitCount = 0;
        }
    }
    return sensorBytes;
}

void readFile(){
    string line;
    int fileNumber = 1;
    while(fileNumber < 11){
        //auto sensorData = new bool[236];
        array<bool, 236> sensorData{};
        ifstream myFile(getFileName(fileNumber));
        if (myFile.is_open()) {
            while (getline(myFile, line, ';')) {
                auto sensorNumber = stoi(
                        line.substr(0, line.find(':')));       //returns number on Sensor in form of an int
                auto sensorValue = line.substr(line.find(':') + 1) == "true";   //returns "false" or "true"
                sensorData[sensorNumber - 1] = sensorValue;
            }
            myFile.close();
            auto sensors = (unsigned char*)playWithData(sensorData);
            for(int i = 0; i < 30; i++) {
                cout << bin_str8(sensors[i]) << endl;
            }
            compareSensorData(sensorData, fileNumber);
            delete sensors;
        } else cout << "Unable to open file";
        fileNumber++;
    }
}


void compareSensorData(array<bool, 236> currentSensorData, int fileNumber) {
    static array<bool, 236> lastSensorData;
    if(fileNumber == 1){
        lastSensorData = currentSensorData;
    }
    if(fileNumber >= 2){
        int sensorIndex;
        for(sensorIndex = 0; sensorIndex < 236; sensorIndex++)
            if(lastSensorData[sensorIndex] != currentSensorData[sensorIndex]){
                cout << "WARNING!! NO NEED TO PANIC BUT SENSOR NUMBER " << sensorIndex << " HAS CHANGED IT'S VALUE TO " << currentSensorData[sensorIndex] << endl;
            }
        lastSensorData = currentSensorData;
    }
}


int main () {
    readFile();
    return 0;
}