#include<iostream>
#include "WavReader.h"
#include<fstream>
using namespace std;
bool WavReader::WReader(string filepath)
{
  uint32_t audio_size;
  ifstream reader(filepath,ios::binary);


  if(!reader.is_open())
  {
    cout<<".wav file could not be opened: "<<endl;
    return false;
  }
  else
  {
    
    reader.seekg(22); //offset value for channel=22 size=2
    reader.read((char*)&channel,2);
    reader.seekg(24);//offset value for sample_rate value=24 size=4
    reader.read((char*)&sample_rate,4);
    reader.seekg(34);//bits_per_sample value=34 size=4 
    reader.read((char*)&bits_per_sample,2);

    char chunkid[5];
    chunkid[4]='\0';
    uint32_t chunksize;

    
    reader.seekg(36);   
    while(reader)
      {
        reader.read((char*)&chunkid,4);
        reader.read((char*)&chunksize,4);
        if(string(chunkid)=="data")
          break;
        reader.seekg(chunksize+(chunksize%2),ios::cur);        //chunk id(4) + chunk size feild(4) + actual chunk size
                    //(chunkSize % 2)  WAV chunks are padded to an even byte boundary, so if chunkSize is odd, add 1 more byte
      }

    
  }

  
  int bytes_per_sample=bits_per_sample/8;
  reader.seekg(-4,ios::cur);
  reader.read((char*)&audio_size,4);

  
  cout << "audio_size: " << audio_size << "\n";

  
  reader.seekg(44);
  total_samples = (audio_size/bytes_per_sample)/channel;
  cout << "total_samples: " << total_samples << "\n";
  cout << "channels: " << channel << "\n";
  cout << "bits: " << bits_per_sample << "\n";

  if(channel==2)
  {
    int32_t leftval=0,rightval=0;
    for(int i=0;i<total_samples;i++)
      {
        leftval=0,rightval=0;
        if(bits_per_sample==8)
        {
          if(!reader.read((char*)&leftval,1)) 
            break;
          if(!reader.read((char*)&rightval,1))
            break;
        }
        else 
        {
          if(!reader.read((char*)&leftval,bytes_per_sample))
            break;
          if(!reader.read((char*)&rightval,bytes_per_sample))
            break;
        }

        double avg=(leftval+rightval)/2;
        if(bits_per_sample==8)
          avg=(avg-128)/128.0;
        else if(bits_per_sample==16)
          avg=avg/32768.0;
        else
          avg=avg/2147483648.0;
        sample.push_back(avg);
      }
  }
  else
  {
    
   for(int i=0;i<total_samples;i++)
      {
        double val=0;
        int32_t current=0;
        if(bits_per_sample==8)
          {
            if(!reader.read((char*)&current,1))
              break;
          }
          else 
          {
            if(!reader.read((char*)&current,bytes_per_sample))
              break;
          }
        if(bits_per_sample==8)
          val=(current-128)/128.0;
        else if(bits_per_sample==16)
          val=current/32768.0;
        else
          val=current/2147483648.0;
        sample.push_back(val);
      }
  }

  cout<<"Pushed successfully into the sample vector:"<<endl;
  return true; 
}



vector<double> WavReader::getSamples()
{
  return sample;
}


int WavReader::getBitDepth()
{
  return bits_per_sample;
}

int WavReader::getSampleRate()
{
  return sample_rate;
}
