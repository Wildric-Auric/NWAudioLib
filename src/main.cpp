#include <iostream>
#include "AudioLib.h"



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
    AudioLib::initSrc(src, init);
    AudioLib::playSrc(src);

    AudioLib::Source src2;
    AudioLib::DataBuffer buff2 = AudioLib::genBuff();
    AudioLib::loadWav(b, buff2);
    AudioLib::genSrc(&src2, buff2);
    init.loopTimes = NW_AUD_LOOP_DONT;
    init.buff      = buff2;
    AudioLib::initSrc(src2, init);
    AudioLib::playSrc(src2);

    AudioLib::setSrcVol(src, 0.01);
    AudioLib::setSrcVol(src2, 0.01);
    AudioLib::setSrcPitch(src, 2.0);
    AudioLib::setSrcPitch(src, 1.0);

    while (1) {

    }
    
    return 0;
}
