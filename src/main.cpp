#include <iostream>
#include "AudioLib.h"
#include <commapi.h>
#include <xaudio2.h>
#include <xaudio2fx.h>



int main() {
    const char* a = "Mystery.wav";
    const char* b = "Wilhelm.wav";

    AudioLib::createCtx();
    AudioLib::DataBuffer buff = AudioLib::genBuff();
    AudioLib::Source src;
    AudioLib::loadWav(a, buff);
    AudioLib::genSrc(&src,buff);
    AudioLib::SourceInitData init;
    init.buff = buff;
    init.loopTimes = NW_AUD_LOOP_DONT;
//    AudioLib::Source src2;
//    AudioLib::DataBuffer buff2 = AudioLib::genBuff();
//    AudioLib::loadWav(b, buff2);
//    AudioLib::genSrc(&src2, buff2);
//    init.loopTimes = NW_AUD_LOOP_DONT;
//    init.buff      = buff2;
//    AudioLib::initSrc(src2, init);
//AudioLib::playSrc(src2);

//    AudioLib::setSrcVol(src, 0.5);
//    AudioLib::setSrcVol(src2, 0.5);
//    AudioLib::setSrcPitch(src, 2.0);
//    AudioLib::setSrcPitch(src, 1.0);
    

   AudioLib::initSrc(src, init);
   AudioLib::setDefMasterVol(0.2);
    
   AudioLib::addReverb(src, AudioLib_I3DL2_PRESET_UNDERWATER);

   AudioLib::playSrc(src);
   AudioLib::disableReverb(src);
   long long i = 30000000000;
   while (1) {
        i--;
        if (i == 0)
            AudioLib::enableReverb(src);

    }
    AudioLib::destroyCtx();
    
    return 0;
}
