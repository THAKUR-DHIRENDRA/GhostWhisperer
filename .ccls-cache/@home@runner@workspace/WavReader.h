#pragma once
#include<iostream>
#include<vector>
#include<string>
 #include <cstdint>
using namespace std;

class WavReader
{
public:
uint16_t channel;    //offset value = 22 size 2
uint32_t sample_rate;//offset value = 24 size 4
uint16_t bits_per_sample; //offset value = 34 size 
int total_samples;
vector<double>sample;
vector<double> getSamples();
int getSampleRate();
int getBitDepth();
bool WReader(string filepath);
};