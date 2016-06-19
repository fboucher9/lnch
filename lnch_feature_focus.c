/* See LICENSE for license details. */

/*

Module: lnch_feature_focus.c

Description:

    Group of hotkeys to control input focus.

*/

/* Operating system headers */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_FOCUS)

/* Focus feature */
#include "lnch_feature_focus.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Key */
#include "lnch_key.h"

/* List of hotkeys for focus feature */
static unsigned int kc_a = 0u;

static unsigned int kc_s = 0u;

static unsigned int kc_d = 0u;

/* Commonly used structure */
static XWindowAttributes wa;

static
void
lnch_feature_focus_set(
    struct lnch_ctxt const * const p_ctxt,
    Window const sel)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if ((sel != None) && (sel != p_display->root))
    {
        XRaiseWindow(p_display->dpy, sel);

        XGetWindowAttributes(p_display->dpy, sel, &wa);

        XWarpPointer(
            p_display->dpy,
            None,
            sel,
            0,
            0,
            0,
            0,
            wa.width/2,
            wa.height/2);
    }
} /* lnch_feature_focus_set() */

static
Window
lnch_feature_focus_find(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    Window sel = None;

    Window top = None;

    Window d1, d2, *wins = NULL;

    unsigned int l;

    int const mx = (pev->xkey.x_root >= p_display->sw/2) ? p_display->sw/2 : 0;

    if (XQueryTree(p_display->dpy, p_display->root, &d1, &d2, &wins, &l))
    {
        unsigned int j;

        for (j = 0; j < l; j++)
        {
            if (XGetWindowAttributes(p_display->dpy, wins[j], &wa) &&
                (wa.map_state == IsViewable))
            {
                if (
                    (wa.x + wa.width/2 - mx >= 0) &&
                    (wa.x + wa.width/2 - mx < p_display->sw/2))
                {
                    top = wins[j];
                }
                if ((kc_a == pev->xkey.keycode) &&
                    (wa.x + wa.width/2 < p_display->sw/2))
                {
                    sel = wins[j];
                }
                else if ((kc_d == pev->xkey.keycode) &&
                    (wa.x + wa.width/2 >= p_display->sw/2))
                {
                    sel = wins[j];
                }
                else if (
                    (kc_s == pev->xkey.keycode) &&
                    (wa.x + wa.width/2 - mx >= 0) &&
                    (wa.x + wa.width/2 - mx < p_display->sw/2) &&
                    (wins[j] != pev->xkey.subwindow) &&
                    (None == sel))
                {
                    sel = wins[j];
                }
            }
        }

        /* Bring current window to top */
        if ((kc_s == pev->xkey.keycode) &&
            (top != pev->xkey.subwindow))
        {
            if ((None != pev->xkey.subwindow) &&
                (p_display->root != pev->xkey.subwindow))
            {
                sel = pev->xkey.subwindow;
            }
        }

        XFree(wins);
    }

    return sel;

} /* lnch_feature_focus_find() */

static
void
lnch_feature_focus_key_press(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (
        (kc_a == pev->xkey.keycode) ||
        (kc_s == pev->xkey.keycode) ||
        (kc_d == pev->xkey.keycode))
    {
        Window const sel = lnch_feature_focus_find(p_ctxt, pev);

        lnch_feature_focus_set(p_ctxt, sel);
    }
} /* lnch_feature_focus_key_press() */

static
void
lnch_feature_focus_dispatch(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (KeyPress == pev->type)
    {
        lnch_feature_focus_key_press(p_ctxt, pev);
    }
} /* lnch_feature_focus_dispatch() */

static
void
lnch_feature_focus_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    /* Grab keys for root window */
    kc_a = lnch_key_grab(p_ctxt, p_display->root, "m-a");

    kc_s = lnch_key_grab(p_ctxt, p_display->root, "m-s");

    kc_d = lnch_key_grab(p_ctxt, p_display->root, "m-d");

} /* lnch_feature_focus_init() */

void
lnch_feature_focus_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (pev)
    {
        lnch_feature_focus_dispatch(p_ctxt, pev);
    }
    else
    {
        lnch_feature_focus_init(p_ctxt);
    }
} /* lnch_feature_focus_event() */

#endif /* #if defined(LNCH_FEATURE_FOCUS) */

/* end-of-file: lnch_feature_focus.c */
