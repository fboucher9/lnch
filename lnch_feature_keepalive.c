/* See LICENSE for license details. */

/*

Module: lnch_feature_keepalive.c

Description:

    Keepalive the X connection by sending a dummy request.

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_KEEPALIVE)

/* Keepalive feature */
#include "lnch_feature_keepalive.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

static unsigned long int g_time_ref = 0;

/*

*/
static
unsigned long int
lnch_feature_keepalive_now(void)
{
    unsigned long int i_clock_value = 0;

    struct timeval o_clock_fields;

    gettimeofday(&o_clock_fields, 0);

    i_clock_value = (unsigned long int)(o_clock_fields.tv_sec * 1000)
        + (unsigned long int)(o_clock_fields.tv_usec / 1000);

    return i_clock_value;

} /* lnch_feature_keepalive_now() */

/*

Function: lnch_feature_keepalive_event

Description:

    Send a dummy command to server to keep connection alive.

*/
void
lnch_feature_keepalive_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev)
{
    if (pev)
    {
        if (pev->type == LASTEvent + 1)
        {
            unsigned long int i_elapsed = 0;
            unsigned long int i_clock_value = 0;

            i_clock_value = lnch_feature_keepalive_now();

            i_elapsed = i_clock_value - g_time_ref;

            if (i_elapsed >= 3000)
            {
                struct lnch_display const * const p_display = p_ctxt->p_display;

                /* Timeout, nothing is happening */
                /* Try to keep X11 connection awake */
                /* Check if a certain amount of time has elapsed */

                XWindowAttributes wa;

                XGetWindowAttributes(p_display->dpy, DefaultRootWindow(p_display->dpy), &wa);

                g_time_ref = i_clock_value;
            }
        }
        else
        {
        }
    }
    else
    {
        g_time_ref = lnch_feature_keepalive_now();
    }

} /* lnch_feature_keepalive_event() */

#endif /* #if defined(LNCH_FEATURE_KEEPALIVE) */

/* end-of-file: lnch_feature_keepalive.c */
