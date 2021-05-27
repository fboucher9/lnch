/* See LICENSE for license details. */

/*

Module: lnch_feature_movesize.h

Description:

    Move and resize windows using mouse.

*/

/* OS headers */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_MOVESIZE)

/* Module */
#include "lnch_feature_movesize.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Tree */
#include "lnch_tree.h"

/* Options */
#include "lnch_opts.h"

/* Keys */
#include "lnch_key.h"

/* Define key modifier flags */
#include "lnch_mods.h"

/* Define MAX macro to help with window resizing calculations */
#define MAX(A, B) ((A) > (B) ? (A) : (B))

static void lnch_feature_movesize_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    unsigned int m;

    /* Grab keys and buttons for new client */
    for (m = 0; m < sizeof(mods)/sizeof(mods[0]); m++)
    {
        XGrabButton(p_display->dpy, Button1, p_opts->i_mod_mask|mods[m], i_window_id,
            False, ButtonPressMask, GrabModeAsync, GrabModeSync,
            None, None);

        XGrabButton(p_display->dpy, Button3, p_opts->i_mod_mask|mods[m], i_window_id,
            False, ButtonPressMask, GrabModeAsync, GrabModeSync,
            None, None);
    }
}

static void lnch_feature_movesize_init_cb(
    struct lnch_tree_callback_args const * const p_args)
{
    lnch_feature_movesize_grab(p_args->p_ctxt, p_args->i_window_id);
}

void
lnch_feature_movesize_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    static XEvent ev0;

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
            (((pev->xbutton.button == Button1) &&
                ((pev->xbutton.state & (p_opts->i_mod_mask|ControlMask)) == (p_opts->i_mod_mask))) ||
             ((pev->xbutton.button == Button3) &&
                ((pev->xbutton.state & (p_opts->i_mod_mask|ControlMask)) == (p_opts->i_mod_mask)))))
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
            if ((ev0.xbutton.button == Button1) || (ev0.xbutton.button == Button3))
            {
                /* Calculate new position and size of client window.
                If Button1 is pressed, then position is adjusted.
                If Button3 is pressed, then size is adjusted. */
                if (ev0.xbutton.button == Button1)
                {
                    wc.x = wa.x + pev->xmotion.x_root - ev0.xbutton.x_root;

                    wc.width = wa.width;

                    wc.y = wa.y + pev->xmotion.y_root - ev0.xbutton.y_root;

                    wc.height = wa.height;
                }
                else if (ev0.xbutton.button == Button3)
                {
                    if (ev0.xbutton.x_root < (wa.x + wa.width/3))
                    {
                        wc.width = MAX(wa.width - pev->xmotion.x_root + ev0.xbutton.x_root, 1);

                        wc.x = wa.x - wc.width + wa.width;
                    }
                    else if (ev0.xbutton.x_root > (wa.x + wa.width*2/3))
                    {
                        wc.x = wa.x;

                        wc.width = MAX(wa.width + pev->xmotion.x_root - ev0.xbutton.x_root, 1);
                    }
                    else
                    {
                        wc.x = wa.x;

                        wc.width = wa.width;
                    }

                    if (ev0.xbutton.y_root < (wa.y + wa.height/3))
                    {
                        wc.height = MAX(wa.height - pev->xmotion.y_root + ev0.xbutton.y_root, 1);

                        wc.y = wa.y - wc.height + wa.height;
                    }
                    else if (ev0.xbutton.y_root > (wa.y + wa.height*2/3))
                    {
                        wc.y = wa.y;

                        wc.height = MAX(wa.height + pev->xmotion.y_root - ev0.xbutton.y_root, 1);
                    }
                    else
                    {
                        wc.y = wa.y;

                        wc.height = wa.height;
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
            if ((ev0.xbutton.button == Button1) || (ev0.xbutton.button == Button3))
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
                lnch_feature_movesize_grab(p_ctxt, pev->xmap.window);
            }
        }
    }
    else
    {
        memset(&ev0, 0, sizeof(ev0));

        lnch_tree_enum(p_ctxt, &lnch_feature_movesize_init_cb, NULL);

        /* Request for events to be reported to our application */
        p_ctxt->p_display->root_event_mask |= SubstructureNotifyMask;

        XSelectInput(p_display->dpy, p_display->root, p_display->root_event_mask);
    }
}

#endif /* #if defined(LNCH_FEATURE_MOVESIZE) */

/* end-of-file: lnch_feature_movesize.c */
