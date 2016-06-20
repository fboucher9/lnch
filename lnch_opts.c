/* See LICENSE for license details. */

/*

Module: lnch_opts.h

Description:

    Command line options.

*/

/* OS headers */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Module */
#include "lnch_opts.h"

/* Context */
#include "lnch_ctxt.h"

/* Display */
#include "lnch_display.h"

/* Default color for border */
#define LNCH_FEATURE_BORDER_COLOR_LEAVE "#222222"

#define LNCH_FEATURE_BORDER_COLOR_ENTER "#444444"

/* Default key for child feature */
#define LNCH_FEATURE_CHILD_KEY "M-x"

/* Default child program to launch */
#define LNCH_FEATURE_CHILD_PROGRAM "/usr/bin/bfst"

/* Default child program argument table */
static char const * const g_exec_child[] =
{
    LNCH_FEATURE_CHILD_PROGRAM,
    NULL
};

/*

Function: lnch_opts_init

Description:

    Initialize the lnch_opts module.

*/
void lnch_opts_init(
    struct lnch_ctxt const * const p_ctxt,
    int const argc,
    char const * const * const argv)
{
    struct lnch_opts * const p_opts = p_ctxt->p_opts;

    struct lnch_display const * const p_display = p_ctxt->p_display;

    int argi = 0u;

    while (argi < argc)
    {
        if (0 == strcmp(argv[argi], "-bg"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_color_leave = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-fg"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_color_enter = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kx"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_child = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-e"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_exec_child = argv + argi;
                argi = argc;
            }
        }
        else
        {
            argi ++;
        }
    }

    if (!p_opts->p_color_leave)
    {
        p_opts->p_color_leave = XGetDefault(p_display->dpy, "lnch", "LeaveColor");

        if (!p_opts->p_color_leave)
        {
            p_opts->p_color_leave = LNCH_FEATURE_BORDER_COLOR_LEAVE;
        }
    }

    if (!p_opts->p_color_enter)
    {
        p_opts->p_color_enter = XGetDefault(p_display->dpy, "lnch", "EnterColor");

        if (!p_opts->p_color_enter)
        {
            p_opts->p_color_enter = LNCH_FEATURE_BORDER_COLOR_ENTER;
        }
    }

    if (!p_opts->p_key_child)
    {
        p_opts->p_key_child = XGetDefault(p_display->dpy, "lnch", "KeyChild");

        if (!p_opts->p_key_child)
        {
            p_opts->p_key_child = LNCH_FEATURE_CHILD_KEY;
        }
    }

    if (!p_opts->p_exec_child)
    {
        p_opts->p_exec_child = g_exec_child;
    }

} /* lnch_opts_init() */

/* end-of-file: lnch_opts.c */
