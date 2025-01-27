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
    
    IUnknown* xapo;
    NW_AUD_WIN_CHECK(XAudio2CreateReverb(&xapo), -1);
    XAUDIO2_EFFECT_DESCRIPTOR desc{};
    desc.InitialState   = true;
    desc.pEffect        = xapo;
    desc.OutputChannels = 2;
    XAUDIO2_EFFECT_CHAIN chain{};
    chain.EffectCount = 1;
    chain.pEffectDescriptors = &desc;
    
    
   IXAudio2SourceVoice* s = (IXAudio2SourceVoice*)src;
   NW_AUD_WIN_CHECK(s->SetEffectChain(&chain), -2);

   XAUDIO2FX_REVERB_PARAMETERS rparams{};
   rparams.ReflectionsDelay = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_DELAY;
   rparams.ReverbDelay = XAUDIO2FX_REVERB_DEFAULT_REVERB_DELAY;
   rparams.RearDelay = XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY;
   rparams.PositionLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION;
   rparams.PositionRight = XAUDIO2FX_REVERB_DEFAULT_POSITION;
   rparams.PositionMatrixLeft = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
   rparams.PositionMatrixRight = XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX;
   rparams.EarlyDiffusion = XAUDIO2FX_REVERB_DEFAULT_EARLY_DIFFUSION;
   rparams.LateDiffusion = XAUDIO2FX_REVERB_DEFAULT_LATE_DIFFUSION;
   rparams.LowEQGain = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN;
   rparams.LowEQCutoff = XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_CUTOFF;
   rparams.HighEQGain = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN;
   rparams.HighEQCutoff = XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_CUTOFF;
   rparams.RoomFilterFreq = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ;
   rparams.RoomFilterMain = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_MAIN;
   rparams.RoomFilterHF = XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_HF;
   rparams.ReflectionsGain = XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_GAIN;
   rparams.ReverbGain = XAUDIO2FX_REVERB_DEFAULT_REVERB_GAIN;
   rparams.DecayTime = XAUDIO2FX_REVERB_DEFAULT_DECAY_TIME;
   rparams.Density = XAUDIO2FX_REVERB_DEFAULT_DENSITY;
   rparams.RoomSize = XAUDIO2FX_REVERB_DEFAULT_ROOM_SIZE;
   rparams.WetDryMix = XAUDIO2FX_REVERB_DEFAULT_WET_DRY_MIX; 
   //rparams = {};
   NW_AUD_WIN_CHECK(s->SetEffectParameters(0, &rparams, sizeof(rparams)), -4);
   NW_AUD_WIN_CHECK(s->EnableEffect(0), -5);

   AudioLib::initSrc(src, init);
   AudioLib::playSrc(src);


   xapo->Release();

    while (1) {

    }
    
    return 0;
}
