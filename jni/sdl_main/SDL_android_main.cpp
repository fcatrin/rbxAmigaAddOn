
#include "SDL_config.h"

#ifdef __ANDROID__

/* Include the SDL main definition header */
#include "SDL_main.h"
#include <android/log.h>

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>

// Called before SDL_main() to initialize JNI bindings in SDL library
extern "C" void SDL_Android_Init(JNIEnv* env, jclass cls);

// Library init
extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    return JNI_VERSION_1_4;
}

// Start up the SDL app
extern "C" void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj)
{
    /* This interface could expand with ABI negotiation, calbacks, etc. */
    SDL_Android_Init(env, cls);


    /* Run the application code! */
    int status;
    char *argv[2];
    argv[0] = strdup("SDL_app");
    argv[1] = NULL;
    __android_log_print(ANDROID_LOG_INFO, "libSDL", "Calling SDL_main(\"%s\")", argv[0]);
    status = SDL_main(1, argv);

    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
    //exit(status);
}

#endif /* __ANDROID__ */

/* vi: set ts=4 sw=4 expandtab: */

