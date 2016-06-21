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

/* Key */
#include "lnch_key.h"

/* Default color for border */
#define LNCH_FEATURE_BORDER_COLOR_LEAVE "#222222"

#define LNCH_FEATURE_BORDER_COLOR_ENTER "#444444"

/* Default modifier mask */
#define LNCH_KEY_DEFAULT Mod1Mask

/* Default key for child feature */
#define LNCH_FEATURE_CHILD_KEY "x-x"

/* Default keys for focus feature */
#define LNCH_FEATURE_FOCUS_LEFT_KEY "x-a"
#define LNCH_FEATURE_FOCUS_RIGHT_KEY "x-d"
#define LNCH_FEATURE_FOCUS_NEXT_KEY "x-s"

/* Default keys for grid feature */
#define LNCH_FEATURE_GRID_LEFT_KEY "x-q"
#define LNCH_FEATURE_GRID_RIGHT_KEY "x-e"
#define LNCH_FEATURE_GRID_TOGGLE_KEY "x-w"
#define LNCH_FEATURE_GRID_RESET_KEY "x-z"
#define LNCH_FEATURE_GRID_SNAP_KEY "x-c"

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
        else if (0 == strcmp(argv[argi], "-ka"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_focus_left = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-ks"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_focus_next = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kd"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_focus_right = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kq"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_grid_left = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kw"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_grid_toggle = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-ke"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_grid_right = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kz"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_grid_reset = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-kc"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_grid_snap = argv[argi];
                argi ++;
            }
        }
        else if (0 == strcmp(argv[argi], "-m"))
        {
            argi ++;
            if (argi < argc)
            {
                p_opts->p_key_mod = argv[argi];
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

    if (!p_opts->p_key_mod)
    {
        p_opts->p_key_mod = XGetDefault(p_display->dpy, "lnch", "KeyMod");
    }

    if (p_opts->p_key_mod)
    {
        struct lnch_key_descriptor o_mod_desc;

        lnch_key_parse(p_ctxt, p_opts->p_key_mod, &o_mod_desc);

        p_opts->i_mod_mask = o_mod_desc.i_mod_mask;
    }
    else
    {
        p_opts->i_mod_mask = LNCH_KEY_DEFAULT;
    }

    if (!p_opts->p_key_child)
    {
        p_opts->p_key_child = XGetDefault(p_display->dpy, "lnch", "KeyChild");

        if (!p_opts->p_key_child)
        {
            p_opts->p_key_child = LNCH_FEATURE_CHILD_KEY;
        }
    }

    if (!p_opts->p_key_focus_left)
    {
        p_opts->p_key_focus_left = XGetDefault(p_display->dpy, "lnch", "KeyFocusLeft");

        if (!p_opts->p_key_focus_left)
        {
            p_opts->p_key_focus_left = LNCH_FEATURE_FOCUS_LEFT_KEY;
        }
    }

    if (!p_opts->p_key_focus_right)
    {
        p_opts->p_key_focus_right = XGetDefault(p_display->dpy, "lnch", "KeyFocusRight");

        if (!p_opts->p_key_focus_right)
        {
            p_opts->p_key_focus_right = LNCH_FEATURE_FOCUS_RIGHT_KEY;
        }
    }

    if (!p_opts->p_key_focus_next)
    {
        p_opts->p_key_focus_next = XGetDefault(p_display->dpy, "lnch", "KeyFocusNext");

        if (!p_opts->p_key_focus_next)
        {
            p_opts->p_key_focus_next = LNCH_FEATURE_FOCUS_NEXT_KEY;
        }
    }

    if (!p_opts->p_key_grid_left)
    {
        p_opts->p_key_grid_left = XGetDefault(p_display->dpy, "lnch", "KeyGridLeft");

        if (!p_opts->p_key_grid_left)
        {
            p_opts->p_key_grid_left = LNCH_FEATURE_GRID_LEFT_KEY;
        }
    }

    if (!p_opts->p_key_grid_right)
    {
        p_opts->p_key_grid_right = XGetDefault(p_display->dpy, "lnch", "KeyGridRight");

        if (!p_opts->p_key_grid_right)
        {
            p_opts->p_key_grid_right = LNCH_FEATURE_GRID_RIGHT_KEY;
        }
    }

    if (!p_opts->p_key_grid_toggle)
    {
        p_opts->p_key_grid_toggle = XGetDefault(p_display->dpy, "lnch", "KeyGridToggle");

        if (!p_opts->p_key_grid_toggle)
        {
            p_opts->p_key_grid_toggle = LNCH_FEATURE_GRID_TOGGLE_KEY;
        }
    }

    if (!p_opts->p_key_grid_reset)
    {
        p_opts->p_key_grid_reset = XGetDefault(p_display->dpy, "lnch", "KeyGridReset");

        if (!p_opts->p_key_grid_reset)
        {
            p_opts->p_key_grid_reset = LNCH_FEATURE_GRID_RESET_KEY;
        }
    }

    if (!p_opts->p_key_grid_snap)
    {
        p_opts->p_key_grid_snap = XGetDefault(p_display->dpy, "lnch", "KeyGridSnap");

        if (!p_opts->p_key_grid_snap)
        {
            p_opts->p_key_grid_snap = LNCH_FEATURE_GRID_SNAP_KEY;
        }
    }

    if (!p_opts->p_exec_child)
    {
        p_opts->p_exec_child = g_exec_child;
    }

} /* lnch_opts_init() */

/* end-of-file: lnch_opts.c */
