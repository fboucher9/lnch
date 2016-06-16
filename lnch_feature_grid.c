/* See LICENSE for license details. */

/*

Module: lnch_feature_grid.c

Description:

*/

#include "lnch_os.h"

#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_GRID)

#include "lnch_ctxt.h"

#include "lnch_display.h"

#include "lnch_feature_grid.h"

#include "lnch_mods.h"

/* Width of monitor */
static int mw = 0;

/* List of hotkeys for grid feature */
static char const * const
    grid_ks_list[] =
    {
        "z",
        "w",
        "q",
        "e",
        "c"
    };

/* Array of key codes.  Index with a ascii character ex: 'x' */
static unsigned int kc_[256];

/* Commonly used structure */
static XWindowAttributes wa;

/* Commonly used structure */
static XWindowChanges wc;

/*

Function: lnch_feature_grid_init()

Description:

    Initialize grid feature.

*/
static
void
lnch_feature_grid_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    /* Calculate width of a single monitor */
    mw = (p_display->sw >= 2048) ? p_display->sw/2 : p_display->sw;

    /* Translate the list of strings into key codes */
    {
        unsigned int j;

        for (j = 0; j < sizeof(grid_ks_list)/sizeof(grid_ks_list[0]); j++)
        {
            kc_[(unsigned char)grid_ks_list[j][0]] = XKeysymToKeycode(p_display->dpy, XStringToKeysym(grid_ks_list[j]));
        }
    }

    /* Request for events to be reported to our application */
    p_ctxt->p_display->root_event_mask |= SubstructureNotifyMask;

    XSelectInput(p_display->dpy, p_display->root, p_display->root_event_mask);

} /* lnch_feature_grid_init() */

/*

Function: lnch_feature_grid_map_notify

Description:

    Handle MapNotify event.

*/
static
void
lnch_feature_grid_map_notify(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (!pev->xmap.override_redirect)
    {
        /* Grab keys and buttons for new client */
        unsigned int j;

        for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
        {
            unsigned int l;

            for (l = 0;
                l < sizeof(grid_ks_list)/sizeof(grid_ks_list[0]);
                l ++)
            {
                XGrabKey(p_display->dpy, kc_[(unsigned char)grid_ks_list[l][0]], Mod1Mask|mods[j],
                    pev->xmap.window, True, GrabModeAsync, GrabModeAsync);
            }
        }
    }
}

/*

Function: lnch_feature_grid_key_press

Description:

    Handle KeyPress event.

*/
static
void
lnch_feature_grid_key_press(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if ((kc_['z'] == pev->xkey.keycode) ||
        (kc_['q'] == pev->xkey.keycode) ||
        (kc_['w'] == pev->xkey.keycode) ||
        (kc_['e'] == pev->xkey.keycode) ||
        (kc_['c'] == pev->xkey.keycode))
    {
        int mx;

        XRaiseWindow(p_display->dpy, pev->xkey.window);

        XGetWindowAttributes(p_display->dpy, pev->xkey.window, &wa);

        wc.x = wa.x;
        wc.y = wa.y;
        wc.width = wa.width;
        wc.height = wa.height;

        mx = ((wa.x + wa.width/2) >= mw) ? mw : 0;

        if (kc_['z'] == pev->xkey.keycode)
        {
            wc.width = 486;
            wc.height = 331;
        }
        else if (kc_['w'] == pev->xkey.keycode)
        {
            wc.x = (wc.x + mw) % p_display->sw;
        }
        else if (kc_['q'] == pev->xkey.keycode)
        {
            wc.x = mx;
            wc.y = 0;
            wc.width = mw/2 - 2;
            wc.height = p_display->sh - 2;
        }
        else if (kc_['e'] == pev->xkey.keycode)
        {
            wc.x = mx + mw/2 - 1;
            wc.y = 0;
            wc.width = mw/2 - 1;
            wc.height = p_display->sh - 2;
        }
        else if (kc_['c'] == pev->xkey.keycode)
        {
            if (pev->xkey.y < wa.height/3)
            {
                if (pev->xkey.x < wa.width/3)
                {
                    wc.x = mx + 0;
                    wc.y = 0;
                    wc.width = mw/2 - 2;
                    wc.height = p_display->sh/2 - 2;
                }
                else if (pev->xkey.x > wa.width*2/3)
                {
                    wc.x = mx + mw/2 - 1;
                    wc.y = 0;
                    wc.width = mw/2 - 1;
                    wc.height = p_display->sh/2 - 2;
                }
                else
                {
                    wc.x = mx + 0;
                    wc.y = 0;
                    wc.width = mw - 2;
                    wc.height = p_display->sh/2 - 2;
                }
            }
            else if (pev->xkey.y > wa.height*2/3)
            {
                if (pev->xkey.x < wa.width/3)
                {
                    wc.x = mx + 0;
                    wc.y = p_display->sh/2 - 1;
                    wc.width = mw/2 - 2;
                    wc.height = p_display->sh/2 - 1;
                }
                else if (pev->xkey.x > wa.width*2/3)
                {
                    wc.x = mx + mw/2 - 1;
                    wc.y = p_display->sh/2 - 1;
                    wc.width = mw/2 - 1;
                    wc.height = p_display->sh/2 - 1;
                }
                else
                {
                    wc.x = mx + 0;
                    wc.y = p_display->sh/2 - 1;
                    wc.width = mw - 2;
                    wc.height = p_display->sh/2 - 1;
                }
            }
            else
            {
                if (pev->xkey.x < wa.width/3)
                {
                    wc.x = mx + 0;
                    wc.y = 0;
                    wc.width = mw/2 - 2;
                    wc.height = p_display->sh - 2;
                }
                else if (pev->xkey.x> wa.width*2/3)
                {
                    wc.x = mx + mw/2 - 1;
                    wc.y = 0;
                    wc.width = mw/2 - 1;
                    wc.height = p_display->sh - 2;
                }
                else
                {
                    wc.x = mx + 0;
                    wc.y = 0;
                    wc.width = mw - 2;
                    wc.height = p_display->sh - 2;
                }
            }
        }

        XConfigureWindow(p_display->dpy, pev->xkey.window, CWX|CWY|CWWidth, &wc);

        XConfigureWindow(p_display->dpy, pev->xkey.window, CWX|CWY|CWHeight, &wc);

        XWarpPointer(p_display->dpy, None, pev->xkey.window, 0, 0, 0, 0,
            wc.width/2, wc.height/2);
    }

} /* lnch_feature_grid_key_press() */

/*

Function: lnch_feature_grid_dispatch

Description:

    Dispatch of event.

*/
static
void
lnch_feature_grid_dispatch(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    if (MapNotify == pev->type)
    {
        lnch_feature_grid_map_notify(p_ctxt, pev);
    }
    else if (KeyPress == pev->type)
    {
        lnch_feature_grid_key_press(p_ctxt, pev);
    }

} /* lnch_feature_grid_dispatch() */

/*

Function: lnch_feature_grid_event

Description:

    Handle events for grid feature.

*/
void
lnch_feature_grid_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    if (pev)
    {
        lnch_feature_grid_dispatch(p_ctxt, pev);
    }
    else
    {
        lnch_feature_grid_init(p_ctxt);
    }

} /* lnch_feature_grid_event() */

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* end-of-file: lnch_feature_grid.c */

