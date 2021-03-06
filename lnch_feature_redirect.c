/* See LICENSE for license details. */

/*

Module: lnch_feature_redirect.c

Description:

    Redirection of X substructure events to fix input focus and also
    to modify attributes of new windows.

Comments:

    -   Certain X clients do not behave correctly unless a window manager
        is running and is redirecting the substructure events.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_REDIRECT)

/* redirect feature */
#include "lnch_feature_redirect.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Tree */
#include "lnch_tree.h"

static int mw = 0;

/* Commonly used structure */
static XWindowAttributes wa;

/* Commonly used structure */
static XWindowChanges wc;

/*

Function: lnch_feature_redirect_enter_notify

Description:

    Handle EnterNotify event.

*/
static
void
lnch_feature_redirect_enter_notify(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (((pev->xcrossing.mode == NotifyNormal) &&
            (pev->xcrossing.detail != NotifyInferior)) ||
        (pev->xcrossing.window != p_display->root))
    {
        XSetInputFocus(p_display->dpy, pev->xcrossing.window, RevertToPointerRoot, CurrentTime);
    }
} /* lnch_feature_redirect_enter_notify() */

/*

Function: lnch_feature_redirect_center_window

Description:

    Center window around current mouse pointer position.

Comments:

    -   To avoid flashing, this must be done before window is mapped.

    -   By calling this from MapRequest event, it centers the window on both
        a new window creation or on a reparent.

*/
static
void
lnch_feature_redirect_center_window(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    int x;

    int y;

    int mx;

    /* Get position of pointer relative to root window */
    {
        int di;

        unsigned int du;

        Window d1;

        XQueryPointer(
            p_display->dpy,
            p_display->root,
            &d1,
            &d1,
            &x,
            &y,
            &di,
            &di,
            &du);
    }

    /* Get window width and height */
    XGetWindowAttributes(p_display->dpy, i_window_id, &wa);

    /* Calculate left coordinate of monitor under cursor */
    mx = (x < mw) ? 0 : mw;

    /* Calculate horizontal position of window centered on mouse */
    x -= wa.width/2;

    /* Calculate vertical position of window centered on mouse */
    y -= wa.height/2;

    /* Clip horizontal position to right edge of monitor */
    if ((x + wa.width + 2) > mx + mw) x = mx + mw - wa.width - 2;

    /* Clip vertical position to bottom edge of monitor */
    if ((y + wa.height + 2) > (int)(p_display->sh)) y = p_display->sh - wa.height - 2;

    /* Clip horizontal position to left edge of monitor */
    if (x < mx) x = mx;

    /* Clip vertical position to top edge of monitor */
    if (y < 0) y = 0;

    /* Apply new position of window */
    XMoveWindow(p_display->dpy, i_window_id, x, y);

} /* lnch_feature_redirect_center_window() */

/*

Function: lnch_feature_redirect_map_request

Description:

    Handle MapRequest event.

*/
static
void
lnch_feature_redirect_map_request(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (XGetWindowAttributes(p_display->dpy, pev->xmaprequest.window, &wa) && !wa.override_redirect)
    {
        XSelectInput(p_display->dpy, pev->xmaprequest.window, wa.your_event_mask | EnterWindowMask);

        lnch_feature_redirect_center_window(p_ctxt, pev->xmaprequest.window);

        XMapWindow(p_display->dpy, pev->xmaprequest.window);
    }
} /* lnch_feature_redirect_map_request() */

/*

Function: lnch_feature_redirect_configure_request

Description:

    Handle ConfigureRequest event.

*/
static
void
lnch_feature_redirect_configure_request(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    wc.x = pev->xconfigurerequest.x;
    wc.y = pev->xconfigurerequest.y;
    wc.width = pev->xconfigurerequest.width;
    wc.height = pev->xconfigurerequest.height;
    wc.border_width = pev->xconfigurerequest.border_width;
    wc.sibling = pev->xconfigurerequest.above;
    wc.stack_mode = pev->xconfigurerequest.detail;

    XConfigureWindow(
        p_display->dpy,
        pev->xconfigurerequest.window,
        pev->xconfigurerequest.value_mask,
        &wc);
} /* lnch_feature_redirect_configure_request() */

/*

Function: lnch_feature_redirect_dispatch

Description:

    Dispatch event by type.

*/
static
void
lnch_feature_redirect_dispatch(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    if (ConfigureRequest == pev->type)
    {
        lnch_feature_redirect_configure_request(p_ctxt, pev);
    }
    else if (MapRequest == pev->type)
    {
        lnch_feature_redirect_map_request(p_ctxt, pev);
    }
    else if (EnterNotify == pev->type)
    {
        lnch_feature_redirect_enter_notify(p_ctxt, pev);
    }
} /* lnch_feature_redirect_dispatch() */

/*

Function: lnch_feature_redirect_init_callback

Description:

    Window enumeration callback.  Register for enter and leave notifications
    so that we may change input focus on all windows.

*/
static
void
lnch_feature_redirect_init_callback(
    struct lnch_tree_callback_args const * const p_args)
{
    struct lnch_ctxt const * const p_ctxt = p_args->p_ctxt;

    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (XGetWindowAttributes(p_display->dpy, p_args->i_window_id, &wa) && !wa.override_redirect)
    {
        XSelectInput(p_display->dpy, p_args->i_window_id, wa.your_event_mask | EnterWindowMask);
    }
} /* lnch_feature_redirect_init_callback() */

/*

Function: lnch_feature_redirect_init

Description:

    Initialize module.

*/
static
void
lnch_feature_redirect_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    /* Calculate width of a single monitor */
    mw = (p_display->sw >= 2048) ? p_display->sw/2 : p_display->sw;

    /* Initialize all existing windows */
    lnch_tree_enum(p_ctxt, &lnch_feature_redirect_init_callback, NULL);

    /* Request for events to be reported to our application */
    p_ctxt->p_display->root_event_mask |= SubstructureRedirectMask;

    /* Update the root window event mask */
    XSelectInput(
        p_display->dpy,
        p_display->root,
        p_display->root_event_mask);

} /* lnch_feature_redirect_init() */

/*

Function: lnch_feature_redirect_event

Description:

    All-in-one redirect feature entry-point.

*/
void
lnch_feature_redirect_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent* pev)
{
    if (pev)
    {
        lnch_feature_redirect_dispatch(p_ctxt, pev);
    }
    else
    {
        lnch_feature_redirect_init(p_ctxt);
    }
} /* lnch_feature_redirect_event() */

#endif /* #if defined(LNCH_FEATURE_REDIRECT) */

/* end-of-file: lnch_feature_redirect.c */
