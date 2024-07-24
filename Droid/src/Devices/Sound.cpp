#include "Sound.h"

void Sound::init()
{
    Serial.begin(115200);
    memcpy(&WavHeader,&droidSignal,44);                     // Copy the header part of the wav data into our structure
    i2cInstall();        // ESP32 will allocated resources to run I2S
    i2cSetpin();                        // Tell it the pins you will be using
    i2s_set_sample_rates(I2S_NUM_0, WavHeader.SampleRate);      //set sample rate 
    data = droidSignal;                                          // set to start of data  
    data += 44;
}

void Sound::play()
{
    while(dataIdx < WavHeader.DataSize) {
        size_t BytesWritten;                            // Returned by the I2S write routine, we are not interested in it

        // As the WAV data for this example is in form of two 16 bit signed values we can send each four bytes direct to I2S
        i2s_write(I2S_NUM_0, data + dataIdx, 4, &BytesWritten, portMAX_DELAY); 
        dataIdx+=4;                                   // increase the data index to next two 16 bit values (4 bytes)
    }

    dataIdx=0;
}

void Sound::i2cInstall()
{
    const i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,                            // Note, this will be changed later
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // high interrupt priority
        .dma_buf_count = 8,                             // 8 buffers
        .dma_buf_len = 1024,                            // 1K per buffer, so 8K of buffer space
        .use_apll=0,
        .tx_desc_auto_clear= true, 
        .fixed_mclk=-1    
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL); 
}

void Sound::i2cSetpin()
{
    const i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,                                 // The bit clock connectiom, goes to pin 27 of ESP32
        .ws_io_num = I2S_WS,                                  // Word select, also known as word select or left right clock
        .data_out_num = I2S_SD,                               // Data out from the ESP32, connect to DIN on 38357A
        .data_in_num = I2S_PIN_NO_CHANGE                  // we are not interested in I2S data into the ESP32
    };

    i2s_set_pin(I2S_NUM_0, &pin_config);
}