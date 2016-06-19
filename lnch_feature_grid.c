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

#include "lnch_tree.h"

#include "lnch_key.h"

/* Width of monitor */
static int mw = 0;

/* List of hotkeys for grid feature */
static unsigned int kc_z = 0u;

static unsigned int kc_w = 0u;

static unsigned int kc_q = 0u;

static unsigned int kc_e = 0u;

static unsigned int kc_c = 0u;

/* Commonly used structure */
static XWindowAttributes wa;

/* Commonly used structure */
static XWindowChanges wc;

/*

Function: lnch_feature_grid_grab_keys

Description:

    Register hot keys into given window.

*/
static
void
lnch_feature_grid_grab_keys(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    kc_z = lnch_key_grab(p_ctxt, i_window_id, "m-z");

    kc_w = lnch_key_grab(p_ctxt, i_window_id, "m-w");

    kc_q = lnch_key_grab(p_ctxt, i_window_id, "m-q");

    kc_e = lnch_key_grab(p_ctxt, i_window_id, "m-e");

    kc_c = lnch_key_grab(p_ctxt, i_window_id, "m-c");

} /* lnch_feature_grid_grab_keys() */

/*

Function: lnch_feature_grid_init_callback

Description:

    Register hot keys for existing window.

*/
static
void
lnch_feature_grid_init_callback(
    struct lnch_tree_callback_args const * const p_args)
{
    lnch_feature_grid_grab_keys(
        p_args->p_ctxt,
        p_args->i_window_id);

} /* lnch_feature_grid_init_callback() */

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

    /* Enumerate existing windows */
    lnch_tree_enum(p_ctxt, &lnch_feature_grid_init_callback, NULL);

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
    if (!pev->xmap.override_redirect)
    {
        /* Grab keys and buttons for new client */
        lnch_feature_grid_grab_keys(p_ctxt, pev->xmap.window);
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

    if ((kc_z == pev->xkey.keycode) ||
        (kc_q == pev->xkey.keycode) ||
        (kc_w == pev->xkey.keycode) ||
        (kc_e == pev->xkey.keycode) ||
        (kc_c == pev->xkey.keycode))
    {
        int mx;

        XRaiseWindow(p_display->dpy, pev->xkey.window);

        XGetWindowAttributes(p_display->dpy, pev->xkey.window, &wa);

        wc.x = wa.x;
        wc.y = wa.y;
        wc.width = wa.width;
        wc.height = wa.height;

        mx = ((wa.x + wa.width/2) >= mw) ? mw : 0;

        if (kc_z == pev->xkey.keycode)
        {
            wc.width = 486;
            wc.height = 331;
        }
        else if (kc_w == pev->xkey.keycode)
        {
            wc.x = (wc.x + mw) % p_display->sw;
        }
        else if (kc_q == pev->xkey.keycode)
        {
            wc.x = mx;
            wc.y = 0;
            wc.width = mw/2 - 2;
            wc.height = p_display->sh - 2;
        }
        else if (kc_e == pev->xkey.keycode)
        {
            wc.x = mx + mw/2 - 1;
            wc.y = 0;
            wc.width = mw/2 - 1;
            wc.height = p_display->sh - 2;
        }
        else if (kc_c == pev->xkey.keycode)
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

