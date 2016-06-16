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

/* Color to use for all borders */
static XColor color;

/* Commonly used structure */
static XWindowChanges wc;

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
        /* Force border width to 1 pixel wide */
        wc.border_width = 1;

        XConfigureWindow(p_display->dpy, pev->xmap.window, CWBorderWidth, &wc);

        /* Force border color (default color is usually black) */
        XSetWindowBorder(p_display->dpy, pev->xmap.window, color.pixel);
    }
} /* lnch_feature_border_map_notify() */

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
} /* lnch_feature_border_dispatch() */

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

    XAllocNamedColor(
        p_display->dpy,
        DefaultColormap(p_display->dpy, p_display->scr),
        "#444444",
        &color,
        &color);

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

