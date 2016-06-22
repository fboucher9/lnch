/* See LICENSE for license details. */

/*

Module: lnch_feature_focus.c

Description:

    Group of hotkeys to control input focus.  When hotkey is pressed, the
    list of windows is scanned to find the window that will receive input
    focus.  The mouse pointer is moved to the center of the selected window
    and the selected window is raised to the top of the Z order.

    There are three focus keys defined:

        1. focus left

            Focus window that is on left side of screen.

        2. focus right

            Focus window that is on right side of screen.

        3. focus next

            Focus next window in Z-order from same side of screen.

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

/* Options */
#include "lnch_opts.h"

/* Tree */
#include "lnch_tree.h"

/* List of hotkeys for focus feature */

/* Hotkey for focus left */
static struct lnch_key_descriptor kc_a;

/* Hotkey for focus next */
static struct lnch_key_descriptor kc_s;

/* Hotkey for focus right */
static struct lnch_key_descriptor kc_d;

/*

Function: lnch_feature_focus_center_pointer

Description:

    Center the mouse pointer in the given window.

Parameters:

    p_ctxt
        Pointer to lnch_ctxt structure.

    i_window_id
        Window in which mouse pointer is centered.

Returns: None.

Comments:

    -   When the mouse pointer is moved, it should generate some LeaveNotify and
        EnterNotify events.  Those events will handle changing the border colors
        if focus has changed.

*/
static
void
lnch_feature_focus_center_pointer(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    XWindowAttributes wa;

    XGetWindowAttributes(p_display->dpy, i_window_id, &wa);

    XWarpPointer(
        p_display->dpy,
        None,
        i_window_id,
        0,
        0,
        0,
        0,
        wa.width/2,
        wa.height/2);

} /* lnch_feature_focus_center_pointer() */

/*

Function: lnch_feature_focus_set

Description:

    Apply the focus change to the select window.

Parameters:

    p_ctxt
        Pointer to lnch_ctxt structure.

    i_window_id
        Apply focus to this window.

Returns: None.

Comments:

    -   By raising the window, it becomes fully visible and also it
        rotates the Z order so that this window becomes the last
        in the list of next windows.

*/
static
void
lnch_feature_focus_set(
    struct lnch_ctxt const * const p_ctxt,
    Window const i_window_id)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    if ((i_window_id != None) && (i_window_id != p_display->root))
    {
        XRaiseWindow(p_display->dpy, i_window_id);

        lnch_feature_focus_center_pointer(p_ctxt, i_window_id);
    }

} /* lnch_feature_focus_set() */

/*

Structure: lnch_feature_focus_find_data

Description:

    State for window enumeration callback.

*/
struct lnch_feature_focus_find_data
{
    XEvent const * pev;

    Window top;

    Window sel;

}; /* struct lnch_feature_focus_find_data */

/*

Function: lnch_feature_focus_find_callback

Description:

    Window enumeration callback.  Process a single window.

*/
static
void
lnch_feature_focus_find_callback(
    struct lnch_tree_callback_args const * const p_args)
{
    struct lnch_ctxt const * const p_ctxt = p_args->p_ctxt;

    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_feature_focus_find_data * const p_data = p_args->p_callback_data;

    int const mx = (p_data->pev->xkey.x_root >= p_display->sw/2) ? p_display->sw/2 : 0;

    if (
        (p_args->o_window_attr.x + p_args->o_window_attr.width/2 - mx >= 0) &&
        (p_args->o_window_attr.x + p_args->o_window_attr.width/2 - mx < p_display->sw/2))
    {
        p_data->top = p_args->i_window_id;
    }

    if (lnch_key_compare(&kc_a, p_data->pev))
    {
        if (p_args->o_window_attr.x + p_args->o_window_attr.width/2 < p_display->sw/2)
        {
            p_data->sel = p_args->i_window_id;
        }
    }
    else if (lnch_key_compare(&kc_d, p_data->pev))
    {
        if (p_args->o_window_attr.x + p_args->o_window_attr.width/2 >= p_display->sw/2)
        {
            p_data->sel = p_args->i_window_id;
        }
    }
    else if (lnch_key_compare(&kc_s, p_data->pev))
    {
        if ((p_args->o_window_attr.x + p_args->o_window_attr.width/2 - mx >= 0) &&
            (p_args->o_window_attr.x + p_args->o_window_attr.width/2 - mx < p_display->sw/2) &&
            (p_args->i_window_id != p_data->pev->xkey.subwindow) &&
            (None == p_data->sel))
        {
            p_data->sel = p_args->i_window_id;
        }
    }

} /* lnch_feature_focus_find_callback() */

/*

Function: lnch_feature_focus_find

Description:

    Scan the list of windows to find the one that must be selected.

Parameters:

    p_ctxt
        Pointer to lnch_ctxt structure.

    pev
        Pointer to XEvent structure.

Returns: handle of window to select

Comments:

    -   The XQueryTree functions returns the windows in Z order, with
        the first window on the bottom.

*/
static
Window
lnch_feature_focus_find(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    struct lnch_display const * const p_display = p_ctxt->p_display;

    struct lnch_feature_focus_find_data o_data;

    o_data.pev = pev;

    o_data.sel = None;

    o_data.top = None;

    lnch_tree_enum(p_ctxt, &lnch_feature_focus_find_callback, &o_data);

    /* Bring current window to top */
    if (lnch_key_compare(&kc_s, pev) &&
        (o_data.top != pev->xkey.subwindow))
    {
        if ((None != pev->xkey.subwindow) &&
            (p_display->root != pev->xkey.subwindow))
        {
            o_data.sel = pev->xkey.subwindow;
        }
    }

    return o_data.sel;

} /* lnch_feature_focus_find() */

static
void
lnch_feature_focus_key_press(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    if (
        lnch_key_compare(&kc_a, pev) ||
        lnch_key_compare(&kc_s, pev) ||
        lnch_key_compare(&kc_d, pev))
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

    struct lnch_opts const * const p_opts = p_ctxt->p_opts;

    /* Convert keys */
    lnch_key_parse(p_ctxt, p_opts->p_key_focus_left, &kc_a);

    lnch_key_parse(p_ctxt, p_opts->p_key_focus_next, &kc_s);

    lnch_key_parse(p_ctxt, p_opts->p_key_focus_right, &kc_d);

    /* Grab keys for root window */
    lnch_key_grab(p_ctxt, p_display->root, &kc_a);

    lnch_key_grab(p_ctxt, p_display->root, &kc_s);

    lnch_key_grab(p_ctxt, p_display->root, &kc_d);

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
