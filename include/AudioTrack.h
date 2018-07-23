#pragma once


#include <AL/al.h>
#include <AL/alc.h>


class AudioTrack
{
public:
  AudioTrack();
  ~AudioTrack();

  ALuint source = -1;
};
