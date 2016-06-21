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

/* Options */
#include "lnch_opts.h"

/* Default modifier mask when all else fails */
#define LNCH_KEY_DEFAULT_MOD_MASK Mod1Mask

/*

Function: lnch_key_convert_mod_char

Description:

    Convert the given string to a modifier key mask.

*/
unsigned int
lnch_key_convert_mod_char(
    char const * const p_key_mod)
{
    unsigned int i_mod_mask;

    if (p_key_mod)
    {
        /* Accept 1- for Mod1Mask */
        if ('1' == p_key_mod[0u])
        {
            i_mod_mask = Mod1Mask;
        }
        /* Accept 2- for Mod2Mask */
        else if ('2' == p_key_mod[0u])
        {
            i_mod_mask = Mod2Mask;
        }
        /* Accept 3- for Mod2Mask */
        else if ('3' == p_key_mod[0u])
        {
            i_mod_mask = Mod3Mask;
        }
        /* Accept 4- for Mod4Mask */
        else if ('4' == p_key_mod[0u])
        {
            i_mod_mask = Mod4Mask;
        }
        /* Accept 5- for Mod5Mask */
        else if ('5' == p_key_mod[0u])
        {
            i_mod_mask = Mod5Mask;
        }
        /* Accept s- or S- for ShiftMask */
        else if (('s' == p_key_mod[0u]) || ('S' == p_key_mod[0u]))
        {
            i_mod_mask = ShiftMask;
        }
        /* Accept c- or C- for ControlMask */
        else if (('c' == p_key_mod[0u]) || ('C' == p_key_mod[0u]))
        {
            i_mod_mask = ControlMask;
        }
        else
        {
            /* Use hard-coded default */
            i_mod_mask = LNCH_KEY_DEFAULT_MOD_MASK;
        }
    }
    else
    {
        /* Use hard-coded default */
        i_mod_mask = LNCH_KEY_DEFAULT_MOD_MASK;
    }

    return i_mod_mask;

} /* lnch_key_convert_mod_char() */

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

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    char const * p_key_it = p_key_string;

    p_desc->i_mod_mask = 0u;

    /* Parse all prefixes */
    while (p_key_it[0u] && ('-' == p_key_it[1]))
    {
        /* Accept x- or X- for default modifier mask */
        if (('x' == p_key_it[0u]) || ('X' == p_key_it[0u]))
        {
            /* Is the modifier mask setting present? */
            p_desc->i_mod_mask |= lnch_key_convert_mod_char(p_opts->p_key_mod);
        }
        else
        {
            p_desc->i_mod_mask |= lnch_key_convert_mod_char(p_key_it);
        }

        p_key_it += 2;
    }

    /* Convert the string to a key code */
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
