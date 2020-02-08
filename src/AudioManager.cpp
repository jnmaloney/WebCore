// #include "AudioManager.h"
// #include <iostream>
// #include <fstream>
// #include <math.h>
// #ifdef USE_AUDIO_MANAGER_VORBIS
// #include <vorbis/codec.h>
// #endif//0
//
// struct RIFF_Header {
//     char chunkID[4];
//     long chunkSize;//size not including chunkSize or chunkID
//     char format[4];
// };
//
//
// /*
//  * Struct to hold fmt subchunk data for WAVE files.
//  */
// struct WAVE_Format {
//     char subChunkID[4];
//     long subChunkSize;
//     short audioFormat;
//     short numChannels;
//     long sampleRate;
//     long byteRate;
//     short blockAlign;
//     short bitsPerSample;
// };
//
// /*
// * Struct to hold the data of the wave file
// */
// struct WAVE_Data {
//     char subChunkID[4]; //should contain the word data
//     long subChunk2Size; //Stores the size of the data block
// };
//
//
// AudioManager::AudioManager()
// {
//
// }
//
//
// AudioManager::~AudioManager()
// {
//   // Exit
//   Context=alcGetCurrentContext();
//   Device=alcGetContextsDevice(Context);
//   alcMakeContextCurrent(NULL);
//   alcDestroyContext(Context);
//   alcCloseDevice(Device);
//
//   std::cout << "Finishing" << std::endl;
// }
//
//
// int AudioManager::init()
// {
//   // Initialization
//   Device = alcOpenDevice(NULL); // select the "preferred device"
//   if (Device) {
//         Context=alcCreateContext(Device,NULL);
//         alcMakeContextCurrent(Context);
//   }
//   // Check for EAX 2.0 support
//   g_bEAX = alIsExtensionPresent("EAX2.0");
//   // Generate Buffers
//   alGetError(); // clear error code
//   alGenBuffers(NUM_BUFFERS, g_Buffers);
//   if ((error = alGetError()) != AL_NO_ERROR)
//   {
//         DisplayALError("alGenBuffers :", error);
//         return 0;
//   }
//
//   return 0;
// }
//
//
// void AudioManager::load(const char* filename)
// {
//   // Create the track handle
//   m_tracks.push_back(AudioTrack());
//   AudioTrack& track = m_tracks[m_tracks.size() - 1];
//
//   // // This loads into a buffer
//   // LoadWAVFile(filename,
//   //             &format, &m_audioBuffer, &size, &freq, &loop);
//   // This loads into a buffer
//   ALuint buf = 0;
//   LoadWAVFile(filename,
//               &format, &buf, &size, &freq, &loop);
//
//   // Bind source to buffer
//   //std::cout << "Binding buf " << buf << " to source " << source[0] << std::endl;
//   //alSourcei(source[0], AL_BUFFER, buf);
//   m_audioBuffer = buf;
//
//   // // Bind source to buffer
//   // std::cout << "Binding buf " << m_audioBuffer << " to source " << source[0] << std::endl;
//   alSourcei(track.source, AL_BUFFER, m_audioBuffer);
// }
//
//
// void AudioManager::load_ogg(const char* filename)
// {
//   // Create the track handle
//   m_tracks.push_back(AudioTrack());
//   AudioTrack& track = m_tracks[m_tracks.size() - 1];
//
//   // Not using many arguments
//   ALuint buf = 0;
//   LoadOGGFile(filename,
//               &format, &buf, &size, &freq, &loop);
//
//   // Set m_audioBuffer
//
//   alSourcei(track.source, AL_BUFFER, m_audioBuffer);
// }
//
//
// void AudioManager::play(int track, bool loop)
// {
//   if (m_currentTrack != -1) stop(m_currentTrack);
//
//   m_currentTrack = track;
//
//   // Play
//   alSourcef(m_tracks[track].source, AL_GAIN, mGain);
//   alSourcePlay(m_tracks[track].source);
//
//   if (loop) alSourcei(m_tracks[track].source, AL_LOOPING, AL_TRUE);
//   else alSourcei(m_tracks[track].source, AL_LOOPING, AL_FALSE);
// }
//
//
// void AudioManager::stop(int track)
// {
//   m_currentTrack = track;
//
//   // Play
//   alSourceStop(m_tracks[track].source);
// }
//
//
// void AudioManager::list_audio_devices(const ALCchar *devices)
// {
//   const ALCchar *device = devices, *next = devices + 1;
//   size_t len = 0;
//
//   fprintf(stdout, "Devices list:\n");
//   fprintf(stdout, "----------\n");
//   while (device && *device != '\0' && next && *next != '\0') {
//           fprintf(stdout, "%s\n", device);
//           len = strlen(device);
//           device += (len + 1);
//           next += (len + 2);
//   }
//   fprintf(stdout, "----------\n");
// }
//
//
// void AudioManager::DisplayALError(const char*, ALuint er)
// {
//   fprintf(stdout, "An error occured\n");
// }
//
//
// bool AudioManager::unloadWAV(ALenum format, void *_data, ALsizei size,
//                  ALsizei frequency)
// {
//   return true;
// }
//
//
// bool AudioManager::LoadWAVFile(const char * filename, ALenum * format, ALuint* buffer, ALsizei * size,
//                  ALsizei * frequency, ALboolean* loop)
// {
//   //Local Declarations
//   FILE* soundFile = NULL;
//   WAVE_Format wave_format;
//   RIFF_Header riff_header;
//   WAVE_Data wave_data;
//   unsigned char* data;
//
//   *size = wave_data.subChunk2Size;
//   *frequency = wave_format.sampleRate;
//   if (wave_format.numChannels == 1)
//   {
//       if (wave_format.bitsPerSample == 8 )
//           *format = AL_FORMAT_MONO8;
//       else if (wave_format.bitsPerSample == 16)
//           *format = AL_FORMAT_MONO16;
//   }
//   else if (wave_format.numChannels == 2)
//   {
//       if (wave_format.bitsPerSample == 8 )
//           *format = AL_FORMAT_STEREO8;
//       else if (wave_format.bitsPerSample == 16)
//           *format = AL_FORMAT_STEREO16;
//   }
//
//   try
//   {
//       soundFile = fopen(filename, "rb");
//       if (!soundFile)
//           throw (filename);
//
//       // Read in the first chunk into the struct
//       fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);
//
//       //check for RIFF and WAVE tag in memeory
//       if ((riff_header.chunkID[0] != 'R' ||
//            riff_header.chunkID[1] != 'I' ||
//            riff_header.chunkID[2] != 'F' ||
//            riff_header.chunkID[3] != 'F') ||
//           (riff_header.format[0] != 'W' ||
//            riff_header.format[1] != 'A' ||
//            riff_header.format[2] != 'V' ||
//            riff_header.format[3] != 'E'))
//           throw ("Invalid RIFF or WAVE Header");
//
//       //Read in the 2nd chunk for the wave info
//       fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
//       //check for fmt tag in memory
//       if (wave_format.subChunkID[0] != 'f' ||
//           wave_format.subChunkID[1] != 'm' ||
//           wave_format.subChunkID[2] != 't' ||
//           wave_format.subChunkID[3] != ' ')
//           throw ("Invalid Wave Format");
//
//       //check for extra parameters;
//       if (wave_format.subChunkSize > 16)
//           fseek(soundFile, sizeof(short), SEEK_CUR);
//
//       //Read in the the last byte of data before the sound file
//       fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
//
//       //check for data tag in memory
//       if (wave_data.subChunkID[0] != 'd' ||
//           wave_data.subChunkID[1] != 'a' ||
//           wave_data.subChunkID[2] != 't' ||
//           wave_data.subChunkID[3] != 'a')
//           throw ("Invalid data header");
//
//       //Allocate memory for data
//       data = new unsigned char[wave_data.subChunk2Size];
//
//       // Read in the sound data into the soundData variable
//       if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
//           throw ("error loading WAVE data into struct!");
//
//       //Now we set the variables that we passed in with the
//       //data from the structs
//       *size = wave_data.subChunk2Size;
//       *frequency = wave_format.sampleRate;
//       std::cout << *size << std::endl;
//       std::cout << *frequency << std::endl;
//       //The format is worked out by looking at the number of
//       //channels and the bits per sample.
//       if (wave_format.numChannels == 1) {
//           if (wave_format.bitsPerSample == 8 )
//               *format = AL_FORMAT_MONO8;
//           else if (wave_format.bitsPerSample == 16)
//               *format = AL_FORMAT_MONO16;
//       } else if (wave_format.numChannels == 2) {
//           if (wave_format.bitsPerSample == 8 )
//               *format = AL_FORMAT_STEREO8;
//           else if (wave_format.bitsPerSample == 16)
//               *format = AL_FORMAT_STEREO16;
//       }
//       //create our openAL buffer and check for success
//       alGenBuffers(2, buffer);
//       if(alGetError() != AL_NO_ERROR) {
//           std::cerr << alGetError() << std::endl;
//       }
//       //now we put our data into the openAL buffer and
//       //check for success
//       alBufferData(*buffer, *format, (void*)data,
//                    *size, *frequency);
//       if(alGetError() != AL_NO_ERROR) {
//           std::cerr << alGetError() << std::endl;
//       }
//       //clean up and return true if successful
//       std::cout << "Load wav successful - buf: " << *buffer << std::endl;
//       fclose(soundFile);
//       delete data;
//       return true;
//   }
//   catch(const char* error)
//   {
//       //our catch statement for if we throw a string
//       std::cerr << error << " : trying to load "
//       << filename << std::endl;
//       //clean up memory if wave loading fails
//       if (soundFile != NULL)
//           fclose(soundFile);
//       //return false to indicate the failure to load wave
//       delete data;
//       return false;
//   }
// }
//
//
// void AudioManager::tick()
// {
//
//   alGetSourcei(m_tracks[m_currentTrack].source, AL_SAMPLE_OFFSET, &sample_offset);
//
//
//   //alSourcePlay(source[0]);
//   ALint source_state = 0;
//   alGetSourcei(m_tracks[m_currentTrack].source, AL_SOURCE_STATE, &source_state);
//   // check for errors
//   if (source_state == AL_PLAYING) {
//           //alGetSourcei(source[0], AL_SOURCE_STATE, &source_state);
//           // check for errors
//   }
// }
//
//
// bool AudioManager::LoadOGGFile(const char * filename, ALenum * _format, ALuint* _buffer, ALsizei * _size,
//                  ALsizei * _frequency, ALboolean* _loop)
// {
//   std::vector<ogg_int16_t> m_convertedBuffer;
//
//   ogg_int16_t convbuffer[4096]; /* take 8k out of the data segment, not the stack */
//   int convsize=4096;
//
//   ogg_sync_state   oy; /* sync and verify incoming physical bitstream */
//   ogg_stream_state os; /* take physical pages, weld into a logical
//                           stream of packets */
//   ogg_page         og; /* one Ogg bitstream page. Vorbis packets are inside */
//   ogg_packet       op; /* one raw packet of data for decode */
//
//   vorbis_info      vi; /* struct that stores all the static vorbis bitstream
//                           settings */
//   vorbis_comment   vc; /* struct that stores all the bitstream user comments */
//   vorbis_dsp_state vd; /* central working state for the packet->PCM decoder */
//   vorbis_block     vb; /* local working space for packet->PCM decode */
//
//   char *buffer;
//   int  bytes;
//
//   // A file stream ?
//   FILE* infile;
//   infile = fopen(filename, "rb"); //.open(filename, std::ios::binary);
//
//   /********** Decode setup ************/
//
//   ogg_sync_init(&oy); /* Now we can read pages */
//
//   while(1){ /* we repeat if the bitstream is chained */
//     int eos=0;
//     int i;
//
//     /* grab some data at the head of the stream. We want the first page
//        (which is guaranteed to be small and only contain the Vorbis
//        stream initial header) We need the first page to get the stream
//        serialno. */
//
//     /* submit a 4k block to libvorbis' Ogg layer */
//     buffer=ogg_sync_buffer(&oy,4096);
//     //bytes=fread(buffer,1,4096,stdin);
//     bytes=fread(buffer,1,4096,infile);
//
//     ogg_sync_wrote(&oy,bytes);
//
//     /* Get the first page. */
//     if(ogg_sync_pageout(&oy,&og)!=1){
//       /* have we simply run out of data?  If so, we're done. */
//       if(bytes<4096)break;
//
//       /* error case.  Must not be Vorbis data */
//       fprintf(stderr,"Input does not appear to be an Ogg bitstream.\n");
//       return false;//exit(1);
//     }
//
//     /* Get the serial number and set up the rest of decode. */
//     /* serialno first; use it to set up a logical stream */
//     ogg_stream_init(&os,ogg_page_serialno(&og));
//
//     /* extract the initial header from the first page and verify that the
//        Ogg bitstream is in fact Vorbis data */
//
//     /* I handle the initial header first instead of just having the code
//        read all three Vorbis headers at once because reading the initial
//        header is an easy way to identify a Vorbis bitstream and it's
//        useful to see that functionality seperated out. */
//
//     vorbis_info_init(&vi);
//     vorbis_comment_init(&vc);
//     if(ogg_stream_pagein(&os,&og)<0){
//       /* error; stream version mismatch perhaps */
//       fprintf(stderr,"Error reading first page of Ogg bitstream data.\n");
//       return false;//exit(1);
//     }
//
//     if(ogg_stream_packetout(&os,&op)!=1){
//       /* no page? must not be vorbis */
//       fprintf(stderr,"Error reading initial header packet.\n");
//       return false;//exit(1);
//     }
//
//     if(vorbis_synthesis_headerin(&vi,&vc,&op)<0){
//       /* error case; not a vorbis header */
//       fprintf(stderr,"This Ogg bitstream does not contain Vorbis "
//               "audio data.\n");
//       return false;//exit(1);
//     }
//
//     /* At this point, we're sure we're Vorbis. We've set up the logical
//        (Ogg) bitstream decoder. Get the comment and codebook headers and
//        set up the Vorbis decoder */
//
//     /* The next two packets in order are the comment and codebook headers.
//        They're likely large and may span multiple pages. Thus we read
//        and submit data until we get our two packets, watching that no
//        pages are missing. If a page is missing, error out; losing a
//        header page is the only place where missing data is fatal. */
//
//     i=0;
//     while(i<2){
//       while(i<2){
//         int result=ogg_sync_pageout(&oy,&og);
//         if(result==0)break; /* Need more data */
//         /* Don't complain about missing or corrupt data yet. We'll
//            catch it at the packet output phase */
//         if(result==1){
//           ogg_stream_pagein(&os,&og); /* we can ignore any errors here
//                                          as they'll also become apparent
//                                          at packetout */
//           while(i<2){
//             result=ogg_stream_packetout(&os,&op);
//             if(result==0)break;
//             if(result<0){
//               /* Uh oh; data at some point was corrupted or missing!
//                  We can't tolerate that in a header.  Die. */
//               fprintf(stderr,"Corrupt secondary header.  Exiting.\n");
//               return false; //exit(1);
//             }
//             result=vorbis_synthesis_headerin(&vi,&vc,&op);
//             if(result<0){
//               fprintf(stderr,"Corrupt secondary header.  Exiting.\n");
//               return false; //exit(1);
//             }
//             i++;
//           }
//         }
//       }
//       /* no harm in not checking before adding more */
//       buffer=ogg_sync_buffer(&oy,4096);
//       bytes=fread(buffer,1,4096,infile);
//       if(bytes==0 && i<2){
//         fprintf(stderr,"End of file before finding all Vorbis headers!\n");
//         return false; //exit(1);
//       }
//       ogg_sync_wrote(&oy,bytes);
//     }
//
//     /* Throw the comments plus a few lines about the bitstream we're
//        decoding */
//     {
//       char **ptr=vc.user_comments;
//       while(*ptr){
//         fprintf(stderr,"%s\n",*ptr);
//         ++ptr;
//       }
//       fprintf(stderr,"\nBitstream is %d channel, %ldHz\n",vi.channels,vi.rate);
//       fprintf(stderr,"Encoded by: %s\n\n",vc.vendor);
//     }
//
//     convsize=4096/vi.channels;
//
//
//     /* OK, got and parsed all three headers. Initialize the Vorbis
//        packet->PCM decoder. */
//     if(vorbis_synthesis_init(&vd,&vi)==0){ /* central decode state */
//       vorbis_block_init(&vd,&vb);          /* local state for most of the decode
//                                               so multiple block decodes can
//                                               proceed in parallel. We could init
//                                               multiple vorbis_block structures
//                                               for vd here */
//
//       /* The rest is just a straight decode loop until end of stream */
//       while(!eos){
//         while(!eos){
//           int result=ogg_sync_pageout(&oy,&og);
//           if(result==0)break; /* need more data */
//           if(result<0){ /* missing or corrupt data at this page position */
//             fprintf(stderr,"Corrupt or missing data in bitstream; "
//                     "continuing...\n");
//           }else{
//             ogg_stream_pagein(&os,&og); /* can safely ignore errors at
//                                            this point */
//             while(1){
//               result=ogg_stream_packetout(&os,&op);
//
//               if(result==0)break; /* need more data */
//               if(result<0){ /* missing or corrupt data at this page position */
//                 /* no reason to complain; already complained above */
//               }else{
//                 /* we have a packet.  Decode it */
//                 float **pcm;
//                 int samples;
//
//                 if(vorbis_synthesis(&vb,&op)==0) /* test for success! */
//                   vorbis_synthesis_blockin(&vd,&vb);
//                 /*
//
//                 **pcm is a multichannel float vector.  In stereo, for
//                 example, pcm[0] is left, and pcm[1] is right.  samples is
//                 the size of each channel.  Convert the float values
//                 (-1.<=range<=1.) to whatever PCM format and write it out */
//
//                 while((samples=vorbis_synthesis_pcmout(&vd,&pcm))>0){
//                   int j;
//                   int clipflag=0;
//                   int bout=(samples<convsize?samples:convsize);
//
//                   /* convert floats to 16 bit signed ints (host order) and
//                      interleave */
//                   for(i=0;i<vi.channels;i++){
//                     ogg_int16_t *ptr=convbuffer+i;
//                     float  *mono=pcm[i];
//                     for(j=0;j<bout;j++){
//                       int val=floor(mono[j]*32767.f+.5f);
//
//                       /* might as well guard against clipping */
//                       if(val>32767){
//                         val=32767;
//                         clipflag=1;
//                       }
//                       if(val<-32768){
//                         val=-32768;
//                         clipflag=1;
//                       }
//                       *ptr=val;
//                       ptr+=vi.channels;
//                     }
//                   }
//
//                   if(clipflag)
//                     fprintf(stderr,"Clipping in frame %ld\n",(long)(vd.sequence));
//
//                   //fwrite(convbuffer,2*vi.channels,bout,stdout);
//                   // Copy the buffer ?
//                   // std::cout << 2*vi.channels << std::endl;
//                   // std::cout << sizeof(ogg_int16_t) << std::endl;
//                   for (int i = 0; i < vi.channels * bout; ++i)
//                   {
//                     m_convertedBuffer.push_back(convbuffer[i]);
//                   }
//                   //std::cout << convbuffer << std::endl;
//                   //std::cout << convbuffer << ", " << 2 * vi.channels * bout << std::endl;
//
//                   vorbis_synthesis_read(&vd,bout); /* tell libvorbis how
//                                                       many samples we
//                                                       actually consumed */
//                 }
//               }
//             }
//             if(ogg_page_eos(&og))eos=1;
//           }
//         }
//         if(!eos){
//           buffer=ogg_sync_buffer(&oy,4096);
//           bytes=fread(buffer,1,4096,infile);
//           ogg_sync_wrote(&oy,bytes);
//           if(bytes==0)eos=1;
//         }
//       }
//
//       /* ogg_page and ogg_packet structs always point to storage in
//          libvorbis.  They're never freed or manipulated directly */
//
//       vorbis_block_clear(&vb);
//       vorbis_dsp_clear(&vd);
//     }else{
//       fprintf(stderr,"Error: Corrupt header during playback initialization.\n");
//     }
//
//     // Scrape vorbis info
//     freq = vi.rate;
//     if (vi.channels == 1) {
//         if (0)
//             format = AL_FORMAT_MONO8;
//         else if (1)
//             format = AL_FORMAT_MONO16;
//     } else if (vi.channels == 2) {
//         if (0)
//             format = AL_FORMAT_STEREO8;
//         else if (1)
//             format = AL_FORMAT_STEREO16;
//     }
//
//     /* clean up this logical bitstream; before exit we see if we're
//        followed by another [chained] */
//
//     ogg_stream_clear(&os);
//     vorbis_comment_clear(&vc);
//     vorbis_info_clear(&vi);  /* must be called last */
//   }
//
//   /* OK, clean up the framer */
//   ogg_sync_clear(&oy);
//   // std::cout << "end of load ogg function" << std::endl;
//   // std::cout << m_convertedBuffer.size() << " bytes in stream" << std::endl;
//   data = (void*)&m_convertedBuffer[0];
//   size = m_convertedBuffer.size();
//   //freq = vi.rate;
//   //format = AL_FORMAT_STEREO16;
//
//   //create our openAL buffer and check for success
//   ALuint bufs[] = {0, 0};
//   ALuint b = 0;
//
//   alGenBuffers(2, &b);
//   if(alGetError() != AL_NO_ERROR) {
//       std::cerr << "Error gen buffers" << std::endl;
//       std::cerr << alGetError() << std::endl;
//   }
//   //now we put our data into the openAL buffer and
//   //check for success
//   alBufferData(b, format, (void*)data, size*2, freq); // sizeof(x) = 2
//   // std::cout << "data " << data << std::endl;
//   // std::cout << "size " << size << std::endl;
//   // std::cout << "format " << format << std::endl;
//   // std::cout << "freq " << freq << std::endl;
//   // std::cout << "vi.channels " << vi.channels << std::endl;
//   ALenum e = alGetError();
//   if(e != AL_NO_ERROR) {
//       std::cerr << "Error buffer data" << std::endl;
//       if (e == AL_OUT_OF_MEMORY) std::cerr << "AL_OUT_OF_MEMORY" << std::endl;
//       if (e == AL_INVALID_VALUE) std::cerr << "AL_INVALID_VALUE" << std::endl;
//       if (e == AL_INVALID_ENUM) std::cerr << "AL_INVALID_ENUM" << std::endl;
//   }
//
//   m_audioBuffer = b;//bufs[0];
//   //std::cout << "buffer #" << m_audioBuffer << std::endl;
//
//   // Can delete data here?
//   //m_convertedBuffer.resize(0);
//   if (save) m_convertedBuffer_save = m_convertedBuffer;
//
//   return true;
// }
