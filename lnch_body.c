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

#if defined(LNCH_FEATURE_BUTTON2)
#include "lnch_feature_button2.h"
#endif /* #if defined(LNCH_FEATURE_BUTTON2) */

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
    lnch_feature_button2_event(p_ctxt, pev);
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
