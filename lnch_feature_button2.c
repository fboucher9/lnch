/* See LICENSE for license details. */

/*

Module: lnch_feature_button2.c

Description:

    Snap of window position using mouse button 2.

*/

/* Operating system headers */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_BUTTON2)

/* Button2 feature */
#include "lnch_feature_button2.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Options */
#include "lnch_opts.h"

/* Keys */
#include "lnch_key.h"

/* Tree */
#include "lnch_tree.h"

/* Modifier masks */
#include "lnch_mods.h"

static void lnch_feature_button2_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    unsigned int j;

    for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
    {
        XGrabButton(p_display->dpy, Button1, p_opts->i_mod_mask|ControlMask|mods[j], i_window_id,
            False, ButtonPressMask, GrabModeAsync, GrabModeSync,
            None, None);
    }
}

static void lnch_feature_button2_cb(
    struct lnch_tree_callback_args const * const p_args)
{
    lnch_feature_button2_grab(
        p_args->p_ctxt,
        p_args->i_window_id);
}

void
lnch_feature_button2_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    static XEvent ev0;

    static int mw = 0;

    /* Commonly used structure */
    static XWindowAttributes wa;

    /* Commonly used structure */
    static XWindowChanges wc;

    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    if (pev)
    {
        /* Detect that one of the mouse buttons have been pressed for a
        client window.  The root window is ignored */
        if ((ButtonPress == pev->type) &&
            (pev->xbutton.window != None) &&
            (pev->xbutton.button == Button1) &&
            ((pev->xbutton.state & (p_opts->i_mod_mask|ControlMask)) == (p_opts->i_mod_mask|ControlMask)))
        {
            /* Bring current window to foreground */
            XRaiseWindow(p_display->dpy, pev->xbutton.window);

            /* Get position and size of current window */
            XGetWindowAttributes(p_display->dpy, pev->xbutton.window, &wa);

            /* Request for button release and pointer motion events */
            XGrabPointer(p_display->dpy, pev->xbutton.window, True,
                ButtonReleaseMask|PointerMotionMask, GrabModeAsync,
                GrabModeAsync, None, None, CurrentTime);

            /* Remember the button press event, it is used by motion */
            ev0 = *pev;
        }
        /* Detect that the mouse pointer has been moved.  This only occurs
        while one of the buttons is pressed. */
        else if (MotionNotify == pev->type)
        {
            if ((ev0.xbutton.button == Button1) &&
                ((ev0.xbutton.state & (p_opts->i_mod_mask|ControlMask)) == (p_opts->i_mod_mask|ControlMask)))
            {
                int mx;

                wc.x = wa.x;
                wc.y = wa.y;
                wc.width = wa.width;
                wc.height = wa.height;

                mx = (pev->xmotion.x_root >= p_display->sw/2) ? p_display->sw/2 : 0;

                if (pev->xmotion.y_root < p_display->sh/3)
                {
                    if ((pev->xmotion.y_root == 0) && (pev->xmotion.x_root == 0))
                    {
                        wc.x = 0;
                        wc.y = 0;
                        wc.width = 486;
                        wc.height = 331;
                    }
                    else if ((pev->xmotion.x_root - mx) < mw/3)
                    {
                        wc.x = mx + 0;
                        wc.y = 0;
                        wc.width = mw/2 - 2;
                        wc.height = p_display->sh/2 - 2;
                    }
                    else if ((pev->xmotion.x_root - mx) > mw*2/3)
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
                else if (pev->xmotion.y_root > p_display->sh*2/3)
                {
                    if ((pev->xmotion.x_root - mx) < mw/3)
                    {
                        wc.x = mx + 0;
                        wc.y = p_display->sh/2 - 1;
                        wc.width = mw/2 - 2;
                        wc.height = p_display->sh/2 - 1;
                    }
                    else if ((pev->xmotion.x_root - mx) > mw*2/3)
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
                    if ((pev->xmotion.x_root - mx) < mw/3)
                    {
                        wc.x = mx + 0;
                        wc.y = 0;
                        wc.width = mw/2 - 2;
                        wc.height = p_display->sh - 2;
                    }
                    else if ((pev->xmotion.x_root - mx) > mw*2/3)
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

                /* Apply new position and size in two steps.  This is required
                to fix a bug with certain applications such as VLC. */

                XConfigureWindow(p_display->dpy, ev0.xbutton.window, CWX|CWY|CWWidth, &wc);

                XConfigureWindow(p_display->dpy, ev0.xbutton.window, CWX|CWY|CWHeight, &wc);
            }
        }
        /* Detect that one of the mouse buttons has been released. */
        else if (ButtonRelease == pev->type)
        {
            if ((ev0.xbutton.button == Button1) &&
                ((ev0.xbutton.state & (p_opts->i_mod_mask|ControlMask)) == (p_opts->i_mod_mask|ControlMask)))
            {
                XUngrabPointer(p_display->dpy, CurrentTime);

                ev0.xbutton.button = 0;
            }
        }
        /* Detect that a new client has been created */
        else if (MapNotify == pev->type)
        {
            if (!pev->xmap.override_redirect)
            {
                /* Grab keys and buttons for new client */
                lnch_feature_button2_grab(p_ctxt, pev->xmap.window);
            }
        }
    }
    else
    {
        /* Calculate width of a single monitor */
        mw = (p_display->sw >= 2048) ? p_display->sw/2 : p_display->sw;

        lnch_tree_enum(p_ctxt, &lnch_feature_button2_cb, NULL);

        /* Request for events to be reported to our application */
        p_ctxt->p_display->root_event_mask |= SubstructureNotifyMask;

        XSelectInput(p_display->dpy, p_display->root, p_display->root_event_mask);
    }
}

#endif /* #if defined(LNCH_FEATURE_BUTTON2) */

/* end-of-file: lnch_feature_button2.c */
