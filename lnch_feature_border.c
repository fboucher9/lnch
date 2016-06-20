/* See LICENSE for license details. */

/*

Module: lnch_feature_border.c

Description:

    Force a border around each window.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_BORDER)

/* border feature */
#include "lnch_feature_border.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Tree */
#include "lnch_tree.h"

/* Options */
#include "lnch_opts.h"

/* Color to use for all borders */
static XColor color_leave;

/* Color to use for foreground window */
static XColor color_enter;

/* Commonly used structure */
static XWindowChanges wc;

static XWindowAttributes wa;

static
void
lnch_feature_border_set(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    /* Force border width to 1 pixel wide */
    wc.border_width = 1;

    XConfigureWindow(p_display->dpy, i_window_id, CWBorderWidth, &wc);

    /* Detect which window is under cursor */
    {
        Window i_root_window = None;

        Window i_child_window = None;

        int i_root_x = 0;

        int i_root_y = 0;

        int i_window_x = 0;

        int i_window_y = 0;

        unsigned int i_mask = 0u;

        if (XQueryPointer(
                p_display->dpy,
                p_display->root,
                &(i_root_window),
                &(i_child_window),
                &(i_root_x),
                &(i_root_y),
                &(i_window_x),
                &(i_window_y),
                &(i_mask)))
        {
            /* Force border color (default color is usually black) */
            XSetWindowBorder(
                p_display->dpy,
                i_window_id,
                i_child_window == i_window_id ? color_enter.pixel : color_leave.pixel);

        }
    }
} /* lnch_feature_border_set() */

/*

Function: lnch_feature_border_map_notify

Description:

    border feature initialization and event handling.

*/
void
lnch_feature_border_map_notify(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (!pev->xmap.override_redirect)
    {
        if (XGetWindowAttributes(p_display->dpy, pev->xmap.window, &wa))
        {
            XSelectInput(p_display->dpy, pev->xmap.window, wa.your_event_mask | EnterWindowMask | LeaveWindowMask);
        }

        lnch_feature_border_set(p_ctxt, pev->xmap.window);
    }
} /* lnch_feature_border_map_notify() */

/*

Function: lnch_feature_border_crossing

Description:

    Handle the EnterNotify and LeaveNotify events.

*/
void
lnch_feature_border_crossing(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if (pev->xcrossing.window != p_display->root)
    {
        lnch_feature_border_set(
            p_ctxt,
            pev->xcrossing.window);
    }
} /* lnch_feature_border_crossing() */

/*

Function: lnch_feature_border_dispatch

Description:

    border feature initialization and event handling.

*/
void
lnch_feature_border_dispatch(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (MapNotify == pev->type)
    {
        lnch_feature_border_map_notify(p_ctxt, pev);
    }
    else if (EnterNotify == pev->type)
    {
        lnch_feature_border_crossing(p_ctxt, pev);
    }
    else if (LeaveNotify == pev->type)
    {
        lnch_feature_border_crossing(p_ctxt, pev);
    }
} /* lnch_feature_border_dispatch() */

/*

Function: lnch_feature_border_init_callback

Description:

    Apply border feature to existing window.

*/
static
void
lnch_feature_border_init_callback(
    struct lnch_tree_callback_args const * const p_args)
{
    struct lnch_display const * const p_display = p_args->p_ctxt->p_display;

    if (XGetWindowAttributes(p_display->dpy, p_args->i_window_id, &wa))
    {
        XSelectInput(
            p_display->dpy,
            p_args->i_window_id,
            wa.your_event_mask | EnterWindowMask | LeaveWindowMask);
    }

    lnch_feature_border_set(
        p_args->p_ctxt,
        p_args->i_window_id);

} /* lnch_feature_border_init_callback() */

/*

Function: lnch_feature_border_init

Description:

    border feature initialization and event handling.

*/
void
lnch_feature_border_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    char const * p_color_name_leave = p_opts->p_color_leave;

    char const * p_color_name_enter = p_opts->p_color_enter;

    XAllocNamedColor(
        p_display->dpy,
        DefaultColormap(p_display->dpy, p_display->scr),
        p_color_name_leave,
        &color_leave,
        &color_leave);

    XAllocNamedColor(
        p_display->dpy,
        DefaultColormap(p_display->dpy, p_display->scr),
        p_color_name_enter,
        &color_enter,
        &color_enter);

    /* enumerate existing windows */
    lnch_tree_enum(p_ctxt, &lnch_feature_border_init_callback, NULL);

} /* lnch_feature_border_init() */

/*

Function: lnch_feature_border_event

Description:

    border feature initialization and event handling.

*/
void
lnch_feature_border_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (pev)
    {
        lnch_feature_border_dispatch(p_ctxt, pev);
    }
    else
    {
        lnch_feature_border_init(p_ctxt);
    }
} /* lnch_feature_border_event() */

#endif /* #if defined(LNCH_FEATURE_BORDER) */

