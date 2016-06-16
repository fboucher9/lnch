/* See LICENSE for license details. */

/*

Module: lnch_display.c

Description:

    X resources common to all modules.

*/

/* Include operating-system header files */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/*

Function: lnch_display_init

Description:

    Initialize module. This is C code, so we can't call it a constructor?

*/
char
lnch_display_init(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display * const p_display = p_ctxt->p_display;

    char b_result;

    /* Get pointer to X11 display using default display name.  The DISPLAY
    environment variable must be set before launching this window manager. */
    p_display->dpy = XOpenDisplay(NULL);

    if (p_display->dpy)
    {
        /* Get index of screen */
        p_display->scr = DefaultScreen(p_display->dpy);

        /* Get width of screen */
        p_display->sw = DisplayWidth(p_display->dpy, p_display->scr);

        /* Get height of screen */
        p_display->sh = DisplayHeight(p_display->dpy, p_display->scr);

        /* Get window id of root window */
        p_display->root = DefaultRootWindow(p_display->dpy);

        b_result = 1;
    }
    else
    {
        b_result = 0;
    }

    return b_result;

} /* lnch_display_init() */

/*

Function: lnch_display_cleanup

Description:

    Cleanup module. This is C code, so we can't call it a destructor?

*/
void
lnch_display_cleanup(
    struct lnch_ctxt const * const p_ctxt)
{
    struct lnch_display * const p_display = p_ctxt->p_display;

    if (p_display->dpy)
    {
        XCloseDisplay(p_display->dpy);

        p_display->dpy = NULL;
    }

    p_display->root = None;

    p_display->scr = -1;

    p_display->sw = 0;

    p_display->sh = 0;

} /* lnch_display_cleanup() */

