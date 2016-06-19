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
unsigned int
lnch_key_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id,
    char const * const p_key_string)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    unsigned int j;

    unsigned int i_key_code;

    unsigned int i_mod_mask = 0u;

    char const * p_key_it = p_key_string;

    while (p_key_it[0] && ('-' == p_key_it[1]))
    {
        if (('m' == p_key_it[0]) || ('M' == p_key_it[0])
            || ('a' == p_key_it[0]) || ('A' == p_key_it[0]))
        {
            i_mod_mask |= Mod1Mask;
        }
        else if (('s' == p_key_it[0]) || ('S' == p_key_it[0]))
        {
            i_mod_mask |= ShiftMask;
        }
        else if (('c' == p_key_it[0]) || ('C' == p_key_it[0]))
        {
            i_mod_mask |= ControlMask;
        }

        p_key_it += 2;
    }

    i_key_code = XKeysymToKeycode(p_display->dpy, XStringToKeysym(p_key_it));

    for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
    {
        XGrabKey(
            p_display->dpy,
            i_key_code,
            i_mod_mask|mods[j],
            i_window_id,
            True,
            GrabModeAsync,
            GrabModeAsync);
    }

    return i_key_code;

} /* lnch_key_grab() */

/* end-of-file: lnch_key.c */
