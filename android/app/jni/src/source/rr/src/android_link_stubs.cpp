#include "compat.h"
#include "sdl_inc.h"
#include "in_android.h"
#include "libasync_config.h"

struct midifuncs;

extern "C" {

droidsysinfo_t droidinfo = { 48000, 512, 1280, 720 };

int SDL_SendKeyboardKey(Uint8 state, SDL_Scancode scancode)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = state == SDL_PRESSED ? SDL_KEYDOWN : SDL_KEYUP;
    event.key.state = state;
    event.key.repeat = 0;
    event.key.keysym.scancode = scancode;
    event.key.keysym.sym = SDL_GetKeyFromScancode(scancode);
    return SDL_PushEvent(&event);
}

int SDL_SendKeyboardText(const char *text)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_TEXTINPUT;
    Bstrncpy(event.text.text, text ? text : "", sizeof(event.text.text));
    return SDL_PushEvent(&event);
}

int SDL_SendMouseMotion(SDL_Window *window, Uint32 mouseID, int relative, int x, int y)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_MOUSEMOTION;
    event.motion.windowID = window ? SDL_GetWindowID(window) : 0;
    event.motion.which = mouseID;
    event.motion.x = x;
    event.motion.y = y;
    event.motion.xrel = relative ? x : 0;
    event.motion.yrel = relative ? y : 0;
    return SDL_PushEvent(&event);
}

int SDL_SendMouseButton(SDL_Window *window, Uint32 mouseID, Uint8 state, Uint8 button)
{
    SDL_Event event;
    SDL_zero(event);
    event.type = state == SDL_PRESSED ? SDL_MOUSEBUTTONDOWN : SDL_MOUSEBUTTONUP;
    event.button.windowID = window ? SDL_GetWindowID(window) : 0;
    event.button.which = mouseID;
    event.button.state = state;
    event.button.button = button;
    return SDL_PushEvent(&event);
}

void AndroidToggleButtonEditor(void) {}
void AndroidDrawControls(void) {}

} // extern "C"

void AndroidShowKeyboard(int) {}

int32_t ALSA_ClientID = 0;
int32_t ALSA_PortID = 0;

int ALSADrv_GetError(void) { return 0; }
const char *ALSADrv_ErrorString(int) { return "ALSA disabled on Android"; }
int ALSADrv_MIDI_Init(midifuncs *) { return 0; }
void ALSADrv_MIDI_Shutdown(void) {}
int ALSADrv_MIDI_StartPlayback(void) { return 0; }
void ALSADrv_MIDI_HaltPlayback(void) {}
void ALSADrv_MIDI_SetTempo(int, int) {}
void ALSADrv_MIDI_Lock(void) {}
void ALSADrv_MIDI_Unlock(void) {}
void ALSADrv_MIDI_Service(void) {}
