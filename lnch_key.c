/* See LICENSE for license details. */

/*

Module: lnch_key.c

Description:

    Register of hotkey for all features.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Module */
#include "lnch_key.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Modifiers */
#include "lnch_mods.h"

/*

Function: lnch_key_grab

Description:

    Register hot key for given window.

*/
void
lnch_key_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id,
    char const * const p_key_string)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_key * const p_key = p_ctxt->p_key;

    unsigned char const i_key_index = (unsigned char)(p_key_string[0]);

    unsigned int j;

    p_key->kc_[i_key_index] = XKeysymToKeycode(p_display->dpy, XStringToKeysym(p_key_string));

    for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
    {
        XGrabKey(
            p_display->dpy,
            p_key->kc_[i_key_index],
            Mod1Mask|mods[j],
            i_window_id,
            True,
            GrabModeAsync,
            GrabModeAsync);
    }

} /* lnch_key_grab() */

/* end-of-file: lnch_key.c */
