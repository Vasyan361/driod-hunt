#pragma once

#include <Arduino.h>
#include <driver/i2s.h>
#include "../../Config.h"
#include "../../Signal.h"

class Sound
{
    public:
        void init();
        void play();
    private:
        struct WavHeader_Struct {
            //   RIFF Section    
            char RIFFSectionID[4];      // Letters "RIFF"
            uint32_t Size;              // Size of entire file less 8
            char RiffFormat[4];         // Letters "WAVE"
            
            //   Format Section    
            char FormatSectionID[4];    // letters "fmt"
            uint32_t FormatSize;        // Size of format section less 8
            uint16_t FormatID;          // 1=uncompressed PCM
            uint16_t NumChannels;       // 1=mono,2=stereo
            uint32_t SampleRate;        // 44100, 16000, 8000 etc.
            uint32_t ByteRate;          // =SampleRate * Channels * (BitsPerSample/8)
            uint16_t BlockAlign;        // =Channels * (BitsPerSample/8)
            uint16_t BitsPerSample;     // 8,16,24 or 32
            
            // Data Section
            char DataSectionID[4];      // The letters "data"
            uint32_t DataSize;          // Size of the data that follows
        } WavHeader;
        unsigned const char* data;
        uint32_t dataIdx = 0;
        void i2cInstall();
        void i2cSetpin();
};
