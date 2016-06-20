/* See LICENSE for license details. */

/*

Module: lnch_body.c

Description:

    Management of all modules.

*/

/* Include operating-system header files */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Body */
#include "lnch_body.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Tree */
#include "lnch_tree.h"

/* Key */
#include "lnch_key.h"

/* Options */
#include "lnch_opts.h"

#if defined(LNCH_FEATURE_XERROR)
#include "lnch_feature_xerror.h"
#endif /* #if defined(LNCH_FEATURE_XERROR) */

#if defined(LNCH_FEATURE_GRID)
#include "lnch_feature_grid.h"
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_FOCUS)
#include "lnch_feature_focus.h"
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_BORDER)
#include "lnch_feature_border.h"
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_REDIRECT)
#include "lnch_feature_redirect.h"
#endif /* #if defined(LNCH_FEATURE_REDIRECT) */

#if defined(LNCH_FEATURE_CHILD)
#include "lnch_feature_child.h"
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_MOVESIZE)
#include "lnch_feature_movesize.h"
#endif /* #if defined(LNCH_FEATURE_MOVESIZE) */

/*

Structure: lnch_body

Description:

    Container for modules.

*/
struct lnch_body
{
    /* Context */
    struct lnch_ctxt o_ctxt;

    /* X resources */
    struct lnch_display o_display;

    /* options */
    struct lnch_opts o_opts;

}; /* struct lnch_body */

/* Define key modifier flags */
#include "lnch_mods.h"

#if defined(LNCH_FEATURE_BUTTON2)

#define LNCH_FEATURE_BUTTON2_MODMASK Mod1Mask

static void lnch_feature_button2_grab(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    unsigned int j;

    for (j = 0; j < sizeof(mods)/sizeof(mods[0]); j++)
    {
        XGrabButton(p_display->dpy, Button2, LNCH_FEATURE_BUTTON2_MODMASK|mods[j], i_window_id,
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

static void button2_event(
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

    if (pev)
    {
        /* Detect that one of the mouse buttons have been pressed for a
        client window.  The root window is ignored */
        if ((ButtonPress == pev->type) &&
            (pev->xbutton.window != None) &&
            (pev->xbutton.button == Button2))
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
            /* Calculate new position and size of client window.
            If Button1 is pressed, then position is adjusted.
            If Button3 is pressed, then size is adjusted. */
            if (ev0.xbutton.button == Button2)
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
            if (ev0.xbutton.button == Button2)
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

/*

Function: lnch_body_event

Description:

    Process of a single event.  First time this is called the event pointer is
    NULL so each plugin will do its own initialization. Second time, the event
    pointer is not NULL so each plugin may process an actual event.

*/
static
void
lnch_body_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
#if defined(LNCH_FEATURE_MOVESIZE)
    lnch_feature_movesize_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_MOVESIZE) */

#if defined(LNCH_FEATURE_BUTTON2)
    button2_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_BUTTON2) */

#if defined(LNCH_FEATURE_BORDER)
    lnch_feature_border_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_CHILD)
    lnch_feature_child_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_GRID)
    lnch_feature_grid_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_FOCUS)
    lnch_feature_focus_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_REDIRECT)
    lnch_feature_redirect_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_REDIRECT) */

#if defined(LNCH_FEATURE_XERROR)
    lnch_feature_xerror_event(p_ctxt, pev);
#endif /* #if defined(LNCH_FEATURE_XERROR) */

} /* lnch_body_event() */

/*

Function: lnch_body_init

Description:

    Initialize lnch_body module.

*/
struct lnch_ctxt *
lnch_body_init(
    int const argc,
    char const * const * const argv)
{
    struct lnch_ctxt * p_ctxt;

    struct lnch_body * p_body;

    p_body = (struct lnch_body *)(malloc(sizeof(*p_body)));

    if (p_body)
    {
        memset(p_body, 0, sizeof(*p_body));

        p_body->o_ctxt.p_body = p_body;

        p_body->o_ctxt.p_display = &p_body->o_display;

        p_body->o_ctxt.p_opts = &p_body->o_opts;

        if (lnch_display_init(&p_body->o_ctxt))
        {
            /* parse command-line options */
            lnch_opts_init(&p_body->o_ctxt, argc, argv);

            p_ctxt = &p_body->o_ctxt;
        }
        else
        {
            free(p_body);

            p_body = 0;

            p_ctxt = 0;
        }
    }
    else
    {
        p_ctxt = 0;
    }

    return p_ctxt;

} /* lnch_body_init() */

void
lnch_body_cleanup(
    struct lnch_ctxt * const p_ctxt)
{
    struct lnch_body * p_body;

    p_body = p_ctxt->p_body;

    lnch_display_cleanup(p_ctxt);

    p_ctxt->p_body = NULL;

    p_ctxt->p_display = NULL;

    free(p_body);

} /* lnch_body_cleanup() */

/*

Function: lnch_body_run

Description:

    Main event loop.

*/
void
lnch_body_run(
    struct lnch_ctxt * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    XEvent ev1;

    XEvent * pev = NULL;

    do
    {
        /* Process of a single event */
        lnch_body_event(p_ctxt, pev);

        /* Initialization is finished, point to an event object and get
        an event from the event queue. */
        pev = &ev1;
    }
    while (!XNextEvent(p_display->dpy, pev));

} /* lnch_body_run() */

/* end-of-file: lnch_body.c */
