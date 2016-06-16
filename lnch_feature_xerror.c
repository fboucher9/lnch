/* See LICENSE for license details. */

/*

Module: lnch_feature_xerror.c

Description:

*/

/* Operating system */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

#if defined(LNCH_FEATURE_XERROR)

/* xerror feature */
#include "lnch_feature_xerror.h"

/*

Function: lnch_feature_xerror_callback

Description:

    X error callback.

*/
static
int
lnch_feature_xerror_callback(
    Display * p_display,
    XErrorEvent * pev)
{
    /* Unused parameter */
    (void)(p_display);

    /* Unused parameter */
    (void)(pev);

    return 0;

} /* lnch_feature_xerror_callback() */

/*

Function: lnch_feature_xerror_event

Description:

    Initialize the X error handler.

*/
void
lnch_feature_xerror_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev)
{
    /* Unused parameter */
    (void)(p_ctxt);

    if (!pev)
    {
        XSetErrorHandler(lnch_feature_xerror_callback);
    }

} /* lnch_feature_xerror_event() */

#endif /* #if defined(LNCH_FEATURE_XERROR) */

/* end-of-file: lnch_feature_xerror.c */
