#include "AudioTrack.h"


AudioTrack::AudioTrack()
{
  // Generate Sources
  alGenSources(1, &source);
  // if ((error = alGetError()) != AL_NO_ERROR)
  // {
  //       DisplayALError("alGenSources 1 : ", error);
  // }
}


AudioTrack::~AudioTrack()
{

}
