#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <bitset>
#include <unistd.h>

using namespace std;

void compareSensorData(array<unsigned char, 30> sensorData, int fileNumber);

void playWithDataBackwardsAndPrint(const array<unsigned char, 30> &currentSensorData,
                                   const array<unsigned char, 30> &lastSensorData);

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
array <unsigned char, 30> playWithData(array<bool, 236> currentSensorData) {
    int bitCount = 0;
    int byteCount = 0;
    array <unsigned char, 30> sensorBytes{};        //auto *sensorBytes = new unsigned char[30];
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
        array<bool, 236> sensorData{};                         //means: auto sensorData = new bool[236];
        ifstream myFile(getFileName(fileNumber));
        if (myFile.is_open()) {
            while (getline(myFile, line, ';')) {
                auto sensorNumber = stoi(
                        line.substr(0, line.find(':')));       //returns number on Sensor in form of an int
                auto sensorValue = line.substr(line.find(':') + 1) == "true";   //returns "false" or "true"
                sensorData[sensorNumber - 1] = sensorValue;
            }
            myFile.close();
            auto sensors = playWithData(sensorData);
            compareSensorData(sensors, fileNumber);
        } else cout << "Unable to open file";
        fileNumber++;
    }
}

void compareSensorData(array<unsigned char, 30> currentSensorData, int fileNumber) {
    static array<unsigned char, 30> lastSensorData;
    if(fileNumber == 1){
        lastSensorData = currentSensorData;
    }
    if(fileNumber >= 2){
        playWithDataBackwardsAndPrint(currentSensorData, lastSensorData);
        lastSensorData = currentSensorData;
    }
    sleep(1);
}

void playWithDataBackwardsAndPrint(const array<unsigned char, 30> &currentSensorData,
                                   const array<unsigned char, 30> &lastSensorData) {
    int i;
    int j;
    int sensorIndex;
    for (i = 0; i < currentSensorData.size(); i++){
        for(j = 0; j<8; j++){
            sensorIndex = i*8 + j;
            auto currentValue = (currentSensorData[i] >> j) & 1;
            auto lastValue = (lastSensorData[i] >> j) & 1;
            if (currentValue != lastValue){
                cout << "WARNING!! NO NEED TO PANIC BUT SENSOR NUMBER " << sensorIndex << " HAS CHANGED ITS VALUE TO " << currentValue << "!!!!!!" << endl;
            }
        }
    }
}

int main () {
    readFile();
    return 0;
}