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

Function: lnch_key_parse

Description:

    Parse the string to find the modifier mask and key code.

*/
void
lnch_key_parse(
    struct lnch_ctxt const * const p_ctxt,
    char const * const p_key_string,
    struct lnch_key_descriptor * const p_desc)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    char const * p_key_it = p_key_string;

    p_desc->i_mod_mask = 0u;

    while (p_key_it[0] && ('-' == p_key_it[1]))
    {
        if (('m' == p_key_it[0]) || ('M' == p_key_it[0])
            || ('a' == p_key_it[0]) || ('A' == p_key_it[0]))
        {
            p_desc->i_mod_mask |= Mod1Mask;
        }
        else if (('s' == p_key_it[0]) || ('S' == p_key_it[0]))
        {
            p_desc->i_mod_mask |= ShiftMask;
        }
        else if (('c' == p_key_it[0]) || ('C' == p_key_it[0]))
        {
            p_desc->i_mod_mask |= ControlMask;
        }
        else if (('w' == p_key_it[0]) || ('W' == p_key_it[0]))
        {
            p_desc->i_mod_mask |= Mod4Mask;
        }

        p_key_it += 2;
    }

    p_desc->i_key_code = XKeysymToKeycode(p_display->dpy, XStringToKeysym(p_key_it));

} /* lnch_key_parse() */

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

    struct lnch_key_descriptor o_desc;

    lnch_key_parse(p_ctxt, p_key_string, &o_desc);

    for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
    {
        XGrabKey(
            p_display->dpy,
            o_desc.i_key_code,
            o_desc.i_mod_mask|mods[j],
            i_window_id,
            True,
            GrabModeAsync,
            GrabModeAsync);
    }

    return o_desc.i_key_code;

} /* lnch_key_grab() */

/* end-of-file: lnch_key.c */
