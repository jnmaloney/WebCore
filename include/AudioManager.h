#pragma once
#define USE_AUDIO_MANAGER_VORBIS

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include "AudioTrack.h"
#include <vector>
#ifdef USE_AUDIO_MANAGER_VORBIS
#include <vorbis/codec.h>
#endif//0


class AudioManager
{
public:
  AudioManager();
  ~AudioManager();

  int init();
  //void loadWav(const char* filename)

  void load(const char* filename); // WAV
  void load_ogg(const char* filename);
  void load_ogg_data(const char* data, unsigned int size);

  void play(int track, bool loop = false);
  void stop(int track);

  void list_audio_devices(const ALCchar *devices);

  void tick();

  bool LoadWAVFile(const char * filename, ALenum * format, ALuint* buffer, ALsizei * size,
                   ALsizei * frequency, ALboolean* loop);
  bool unloadWAV(ALenum format, void *_data, ALsizei size,
                  ALsizei frequency);
  void DisplayALError(const char*, ALuint er);

   std::vector<ogg_int16_t> m_convertedBuffer_save;
   ALint sample_offset;
   bool save = false;

   double mGain = 0.75;

protected:

  bool LoadOGGFile(const char * filename, ALenum * format, ALuint* buffer, ALsizei * size,
                   ALsizei * frequency, ALboolean* loop);
  bool LoadOGGFile(const char * data, unsigned int datasize, ALenum * format, ALuint* buffer, ALsizei * size,
                   ALsizei * frequency, ALboolean* loop);

  ALCcontext *Context;
  ALCdevice *Device;
  ALuint error;

  ALuint NUM_BUFFERS = 1;
  bool g_bEAX = false;
  ALuint g_Buffers[1] = {0};
  //ALuint source[1] = {0};
  std::vector<AudioTrack> m_tracks;
  int m_currentTrack = -1;

  ALsizei size, freq;
  ALenum format;
  ALvoid *data;
  ALboolean loop = AL_FALSE;

  ALuint m_audioBuffer = 0;
};
