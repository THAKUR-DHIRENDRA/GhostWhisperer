#include "WavReader.h"
#include <iostream>
using namespace std;

// Creates a WavReader object
// Calls WReader() with a .wav file path
// Prints getSampleRate()
// Prints getBitDepth()
// Prints getSamples().size()

int main() {
  WavReader W1;
  W1.WReader("song.wav");
  cout << W1.getSampleRate() << "\n";
  cout << W1.getBitDepth() << "\n";
  cout << W1.getSamples().size() << "\n";
}