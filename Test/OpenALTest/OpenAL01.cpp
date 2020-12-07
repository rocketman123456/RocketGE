#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>

/* InitAL opens a device and sets up a context using default attributes, making
 * the program ready to call OpenAL functions. */
int InitAL(char ***argv, int *argc)
{
    const ALCchar *name;
    ALCdevice *device;
    ALCcontext *ctx;

    /* Open and initialize a device */
    device = NULL;
    if(argc && argv && *argc > 1 && strcmp((*argv)[0], "-device") == 0)
    {
        device = alcOpenDevice((*argv)[1]);
        if(!device)
            fprintf(stderr, "Failed to open \"%s\", trying default\n", (*argv)[1]);
        (*argv) += 2;
        (*argc) -= 2;
    }
    if(!device)
        device = alcOpenDevice(NULL);
    if(!device)
    {
        fprintf(stderr, "Could not open a device!\n");
        return 1;
    }

    ctx = alcCreateContext(device, NULL);
    if(ctx == NULL || alcMakeContextCurrent(ctx) == ALC_FALSE)
    {
        if(ctx != NULL)
            alcDestroyContext(ctx);
        alcCloseDevice(device);
        fprintf(stderr, "Could not set a context!\n");
        return 1;
    }

    name = NULL;
    if(alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
        name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
    if(!name || alcGetError(device) != AL_NO_ERROR)
        name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    printf("Opened \"%s\"\n", name);

    return 0;
}

/* CloseAL closes the device belonging to the current context, and destroys the
 * context. */
void CloseAL(void)
{
    ALCdevice *device;
    ALCcontext *ctx;

    ctx = alcGetCurrentContext();
    if(ctx == NULL)
        return;

    device = alcGetContextsDevice(ctx);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(device);
}

/* LoadBuffer loads the named audio file into an OpenAL buffer object, and
 * returns the new buffer ID.
 */
static ALuint LoadSound(const char *filename)
{
    ALenum err, format;
    ALuint buffer;
    SNDFILE *sndfile;
    SF_INFO sfinfo;
    short *membuf;
    sf_count_t num_frames;
    ALsizei num_bytes;

    /* Open the audio file and check that it's usable. */
    sndfile = sf_open(filename, SFM_READ, &sfinfo);
    if(!sndfile)
    {
        fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
        return 0;
    }
    if(sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX/sizeof(short))/sfinfo.channels)
    {
        fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
        sf_close(sndfile);
        return 0;
    }

    /* Get the sound format, and figure out the OpenAL format */
    format = AL_NONE;
    if(sfinfo.channels == 1)
        format = AL_FORMAT_MONO16;
    else if(sfinfo.channels == 2)
        format = AL_FORMAT_STEREO16;
    else if(sfinfo.channels == 3)
    {
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT2D_16;
    }
    else if(sfinfo.channels == 4)
    {
        if(sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
            format = AL_FORMAT_BFORMAT3D_16;
    }
    if(!format)
    {
        fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
        sf_close(sndfile);
        return 0;
    }

    /* Decode the whole audio file to a buffer. */
    auto size = (size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short);
    membuf = (short*)malloc(size);

    num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
    if(num_frames < 1)
    {
        free(membuf);
        sf_close(sndfile);
        fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
        return 0;
    }
    num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

    /* Buffer the audio data into a new buffer object, then free the data and
     * close the file.
     */
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

    free(membuf);
    sf_close(sndfile);

    /* Check if an error occured, and clean up if so. */
    err = alGetError();
    if(err != AL_NO_ERROR)
    {
        fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
        if(buffer && alIsBuffer(buffer))
            alDeleteBuffers(1, &buffer);
        return 0;
    }

    return buffer;
}

/* Cross-platform timeget and sleep functions. */
int altime_get(void);
void al_nssleep(unsigned long nsec);

int main(int argc, char **argv)
{
    std::cout << "OpenAL Hello!" << std::endl;

    ALuint source, buffer;
    ALfloat offset;
    ALenum state;

    /* Print out usage if no arguments were specified */
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s [-device <name>] <filename>\n", argv[0]);
        return 1;
    }

    argv++; argc--;
    if(InitAL(&argv, &argc) != 0)
        return 1;
    
    /* Load the sound into a buffer. */
    buffer = LoadSound(argv[0]);
    if(!buffer)
    {
        CloseAL();
        return 1;
    }

    /* Create the source to play the sound with. */
    source = 0;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);
    assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source");

    /* Play the sound until it finishes. */
    alSourcePlay(source);
    do {
        al_nssleep(10000000);
        alGetSourcei(source, AL_SOURCE_STATE, &state);

        /* Get the source offset. */
        alGetSourcef(source, AL_SEC_OFFSET, &offset);
        printf("\rOffset: %f  ", offset);
        fflush(stdout);
    } while(alGetError() == AL_NO_ERROR && state == AL_PLAYING);
    printf("\n");

    /* All done. Delete resources, and close down OpenAL. */
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    
    CloseAL();
    return 0;
}

#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int altime_get(void)
{
    static int start_time = 0u;
    int cur_time;

#if _POSIX_TIMERS > 0
    struct timespec ts;
    int ret = clock_gettime(CLOCK_REALTIME, &ts);
    if(ret != 0) return 0;
    cur_time = (int)(ts.tv_sec*1000 + ts.tv_nsec/1000000);
#else /* _POSIX_TIMERS > 0 */
    struct timeval tv;
    int ret = gettimeofday(&tv, NULL);
    if(ret != 0) return 0;
    cur_time = (int)(tv.tv_sec*1000 + tv.tv_usec/1000);
#endif

    if(!start_time)
        start_time = cur_time;
    return cur_time - start_time;
}

void al_nssleep(unsigned long nsec)
{
    struct timespec ts, rem;
    ts.tv_sec = (time_t)(nsec / 1000000000ul);
    ts.tv_nsec = (long)(nsec % 1000000000ul);
    while(nanosleep(&ts, &rem) == -1 && errno == EINTR)
        ts = rem;
}