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

/* Application name */
#define LNCH_OPTS_APP_NAME "lnch"

struct lnch_opts_descriptor
{
    char const * p_switch;

    char const * p_resource;

    char const * p_default;

}; /* struct lnch_opts_descriptor */

/*

Definitions for command-line options and X resources:

    LNCH_OPTS_x_SWITCH      Command-line switch
    LNCH_OPTS_x_RES         Resource name
    LNCH_OPTS_x_DEFAULT     Default value

*/

/* mod mask: */

/* Switch for mod mask */
#define LNCH_OPTS_MOD_MASK_SWITCH "-m"

/* Resource for mod mask */
#define LNCH_OPTS_MOD_MASK_RES "KeyMod"

/* Default modifier mask for all x- mappings */
#define LNCH_OPTS_MOD_MASK_DEFAULT "1-"

static
struct lnch_opts_descriptor const
g_mod_mask =
{
    LNCH_OPTS_MOD_MASK_SWITCH,
    LNCH_OPTS_MOD_MASK_RES,
    LNCH_OPTS_MOD_MASK_DEFAULT
};

/* border leave color: */

#if defined(LNCH_FEATURE_BORDER)

/* Switch for border leave color */
#define LNCH_OPTS_BORDER_LEAVE_COLOR_SWITCH "-bg"

/* Resource for border leave color */
#define LNCH_OPTS_BORDER_LEAVE_COLOR_RES "LeaveColor"

/* Default value for border leave color */
#define LNCH_OPTS_BORDER_LEAVE_COLOR_DEFAULT "#222222"

static
struct lnch_opts_descriptor const
g_border_leave_color =
{
    LNCH_OPTS_BORDER_LEAVE_COLOR_SWITCH,
    LNCH_OPTS_BORDER_LEAVE_COLOR_RES,
    LNCH_OPTS_BORDER_LEAVE_COLOR_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_BORDER) */

/* border enter color: */

#if defined(LNCH_FEATURE_BORDER)

/* Switch for border enter color */
#define LNCH_OPTS_BORDER_ENTER_COLOR_SWITCH "-fg"

/* Resource for border enter color */
#define LNCH_OPTS_BORDER_ENTER_COLOR_RES "EnterColor"

/* Default value for border enter color */
#define LNCH_OPTS_BORDER_ENTER_COLOR_DEFAULT "#444444"

static
struct lnch_opts_descriptor const
g_border_enter_color =
{
    LNCH_OPTS_BORDER_ENTER_COLOR_SWITCH,
    LNCH_OPTS_BORDER_ENTER_COLOR_RES,
    LNCH_OPTS_BORDER_ENTER_COLOR_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_BORDER) */

/* child key: */

#if defined(LNCH_FEATURE_CHILD)

/* Switch for child key */
#define LNCH_OPTS_CHILD_KEY_SWITCH "-kx"

/* Resource for child key */
#define LNCH_OPTS_CHILD_KEY_RES "KeyChild"

/* Default value for child key */
#define LNCH_OPTS_CHILD_KEY_DEFAULT "x-x"

static
struct lnch_opts_descriptor const
g_child_key =
{
    LNCH_OPTS_CHILD_KEY_SWITCH,
    LNCH_OPTS_CHILD_KEY_RES,
    LNCH_OPTS_CHILD_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_CHILD) */

/* child program: */

#if defined(LNCH_FEATURE_CHILD)

/* Switch for child program */
#define LNCH_OPTS_CHILD_PROGRAM_SWITCH "-e"

/* Resource for child program */
#define LNCH_OPTS_CHILD_PROGRAM_RES "Exec"

/* Default child program to launch */
#define LNCH_OPTS_CHILD_PROGRAM_DEFAULT "/usr/bin/bfst"

static
struct lnch_opts_descriptor const
g_child_program =
{
    LNCH_OPTS_CHILD_PROGRAM_SWITCH,
    LNCH_OPTS_CHILD_PROGRAM_RES,
    LNCH_OPTS_CHILD_PROGRAM_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_CHILD) */

/* focus left key: */

#if defined(LNCH_FEATURE_FOCUS)

/* Switch */
#define LNCH_OPTS_FOCUS_LEFT_KEY_SWITCH "-ka"

/* Resource */
#define LNCH_OPTS_FOCUS_LEFT_KEY_RES "KeyFocusLeft"

/* Default */
#define LNCH_OPTS_FOCUS_LEFT_KEY_DEFAULT "x-a"

static
struct lnch_opts_descriptor const
g_focus_left_key =
{
    LNCH_OPTS_FOCUS_LEFT_KEY_SWITCH,
    LNCH_OPTS_FOCUS_LEFT_KEY_RES,
    LNCH_OPTS_FOCUS_LEFT_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_FOCUS) */

/* focus right key: */

#if defined(LNCH_FEATURE_FOCUS)

/* Switch */
#define LNCH_OPTS_FOCUS_RIGHT_KEY_SWITCH "-kd"

/* Resource */
#define LNCH_OPTS_FOCUS_RIGHT_KEY_RES "KeyFocusRight"

/* Default key for focus right */
#define LNCH_OPTS_FOCUS_RIGHT_KEY_DEFAULT "x-d"

static
struct lnch_opts_descriptor const
g_focus_right_key =
{
    LNCH_OPTS_FOCUS_RIGHT_KEY_SWITCH,
    LNCH_OPTS_FOCUS_RIGHT_KEY_RES,
    LNCH_OPTS_FOCUS_RIGHT_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_FOCUS) */

/* focus next key: */

#if defined(LNCH_FEATURE_FOCUS)

/* Switch */
#define LNCH_OPTS_FOCUS_NEXT_KEY_SWITCH "-ks"

/* Resource */
#define LNCH_OPTS_FOCUS_NEXT_KEY_RES "KeyFocusNext"

/* Default key for focus next */
#define LNCH_OPTS_FOCUS_NEXT_KEY_DEFAULT "x-s"

static
struct lnch_opts_descriptor const
g_focus_next_key =
{
    LNCH_OPTS_FOCUS_NEXT_KEY_SWITCH,
    LNCH_OPTS_FOCUS_NEXT_KEY_RES,
    LNCH_OPTS_FOCUS_NEXT_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_FOCUS) */

/* grid left key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_LEFT_KEY_SWITCH "-kq"

/* Resource */
#define LNCH_OPTS_GRID_LEFT_KEY_RES "KeyGridLeft"

/* Default key for grid left */
#define LNCH_OPTS_GRID_LEFT_KEY_DEFAULT "x-q"

static
struct lnch_opts_descriptor const
g_grid_left_key =
{
    LNCH_OPTS_GRID_LEFT_KEY_SWITCH,
    LNCH_OPTS_GRID_LEFT_KEY_RES,
    LNCH_OPTS_GRID_LEFT_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid right key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_RIGHT_KEY_SWITCH "-ke"

/* Resource */
#define LNCH_OPTS_GRID_RIGHT_KEY_RES "KeyGridRight"

/* Default key for grid right */
#define LNCH_OPTS_GRID_RIGHT_KEY_DEFAULT "x-e"

static
struct lnch_opts_descriptor const
g_grid_right_key =
{
    LNCH_OPTS_GRID_RIGHT_KEY_SWITCH,
    LNCH_OPTS_GRID_RIGHT_KEY_RES,
    LNCH_OPTS_GRID_RIGHT_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid toggle key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_TOGGLE_KEY_SWITCH "-kw"

/* Resource */
#define LNCH_OPTS_GRID_TOGGLE_KEY_RES "KeyGridToggle"

/* Default key for grid toggle */
#define LNCH_OPTS_GRID_TOGGLE_KEY_DEFAULT "x-w"

static
struct lnch_opts_descriptor const
g_grid_toggle_key =
{
    LNCH_OPTS_GRID_TOGGLE_KEY_SWITCH,
    LNCH_OPTS_GRID_TOGGLE_KEY_RES,
    LNCH_OPTS_GRID_TOGGLE_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid reset key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_RESET_KEY_SWITCH "-kz"

/* Resource */
#define LNCH_OPTS_GRID_RESET_KEY_RES "KeyGridReset"

/* Default key for grid reset */
#define LNCH_OPTS_GRID_RESET_KEY_DEFAULT "x-z"

static
struct lnch_opts_descriptor const
g_grid_reset_key =
{
    LNCH_OPTS_GRID_RESET_KEY_SWITCH,
    LNCH_OPTS_GRID_RESET_KEY_RES,
    LNCH_OPTS_GRID_RESET_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid snap key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_SNAP_KEY_SWITCH "-kc"

/* Resource */
#define LNCH_OPTS_GRID_SNAP_KEY_RES "KeyGridSnap"

/* Default key for grid snap */
#define LNCH_OPTS_GRID_SNAP_KEY_DEFAULT "x-c"

static
struct lnch_opts_descriptor const
g_grid_snap_key =
{
    LNCH_OPTS_GRID_SNAP_KEY_SWITCH,
    LNCH_OPTS_GRID_SNAP_KEY_RES,
    LNCH_OPTS_GRID_SNAP_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid 1 key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_1_KEY_SWITCH "-k1"

/* Resource */
#define LNCH_OPTS_GRID_1_KEY_RES "KeyGrid1"

/* Default key for grid 1 */
#define LNCH_OPTS_GRID_1_KEY_DEFAULT "x-1"

static
struct lnch_opts_descriptor const
g_grid_1_key =
{
    LNCH_OPTS_GRID_1_KEY_SWITCH,
    LNCH_OPTS_GRID_1_KEY_RES,
    LNCH_OPTS_GRID_1_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid 2 key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_2_KEY_SWITCH "-k2"

/* Resource */
#define LNCH_OPTS_GRID_2_KEY_RES "KeyGrid2"

/* Default key for grid 2 */
#define LNCH_OPTS_GRID_2_KEY_DEFAULT "x-2"

static
struct lnch_opts_descriptor const
g_grid_2_key =
{
    LNCH_OPTS_GRID_2_KEY_SWITCH,
    LNCH_OPTS_GRID_2_KEY_RES,
    LNCH_OPTS_GRID_2_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid 3 key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_3_KEY_SWITCH "-k3"

/* Resource */
#define LNCH_OPTS_GRID_3_KEY_RES "KeyGrid3"

/* Default key for grid 3 */
#define LNCH_OPTS_GRID_3_KEY_DEFAULT "x-3"

static
struct lnch_opts_descriptor const
g_grid_3_key =
{
    LNCH_OPTS_GRID_3_KEY_SWITCH,
    LNCH_OPTS_GRID_3_KEY_RES,
    LNCH_OPTS_GRID_3_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

/* grid 4 key: */

#if defined(LNCH_FEATURE_GRID)

/* Switch */
#define LNCH_OPTS_GRID_4_KEY_SWITCH "-k4"

/* Resource */
#define LNCH_OPTS_GRID_4_KEY_RES "KeyGrid4"

/* Default key for grid 4 */
#define LNCH_OPTS_GRID_4_KEY_DEFAULT "x-4"

static
struct lnch_opts_descriptor const
g_grid_4_key =
{
    LNCH_OPTS_GRID_4_KEY_SWITCH,
    LNCH_OPTS_GRID_4_KEY_RES,
    LNCH_OPTS_GRID_4_KEY_DEFAULT
};

#endif /* #if defined(LNCH_FEATURE_GRID) */

static
char const *
lnch_opts_find_string(
    struct lnch_ctxt const * const p_ctxt,
    int const argc,
    char const * const * const argv,
    char const * const p_switch)
{
    char const * p_value = NULL;

    int argi = 1u;

    (void)p_ctxt;

    while (!p_value && (argi < argc))
    {
        if (0 == strcmp(argv[argi++], p_switch))
        {
            if (argi < argc)
            {
                p_value = argv[argi];
                argi ++;
            }
        }
    }

    return p_value;
}

static
char const *
lnch_opts_find_res(
    struct lnch_ctxt const * const p_ctxt,
    int const argc,
    char const * const * const argv,
    struct lnch_opts_descriptor const * const p_desc)
{
    char const * p_value = NULL;

    p_value = lnch_opts_find_string(p_ctxt, argc, argv, p_desc->p_switch);

    if (!p_value)
    {
        struct lnch_display const * const p_display = p_ctxt->p_display;

        p_value = XGetDefault(p_display->dpy, LNCH_OPTS_APP_NAME, p_desc->p_resource);

        if (!p_value)
        {
            p_value = p_desc->p_default;
        }
    }

    return p_value;

} /* lnch_opts_find_res() */

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

    p_opts->p_key_mod =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_mod_mask);

#if defined(LNCH_FEATURE_BORDER)
    p_opts->p_color_leave =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_border_leave_color);
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_BORDER)
    p_opts->p_color_enter =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_border_enter_color);
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_CHILD)
    p_opts->p_key_child =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_child_key);
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_CHILD)
    p_opts->p_exec_child =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_child_program);
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_FOCUS)
    p_opts->p_key_focus_left =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_focus_left_key);
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_FOCUS)
    p_opts->p_key_focus_next =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_focus_next_key);
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_FOCUS)
    p_opts->p_key_focus_right =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_focus_right_key);
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_left =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_left_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_toggle =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_toggle_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_right =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_right_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_reset =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_reset_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_snap =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_snap_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_1 =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_1_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_2 =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_2_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_3 =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_3_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    p_opts->p_key_grid_4 =
        lnch_opts_find_res(p_ctxt, argc, argv,
            &g_grid_4_key);
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_TIMESTAMP)
    p_opts->p_log_file =
        lnch_opts_find_string(p_ctxt, argc, argv,
            "-g");
#endif /* #if defined(LNCH_FEATURE_TIMESTAMP) */

    {
        struct lnch_key_descriptor o_mod_desc;

        lnch_key_parse(p_ctxt, p_opts->p_key_mod, &o_mod_desc);

        p_opts->i_mod_mask = o_mod_desc.i_mod_mask;
    }

} /* lnch_opts_init() */

/* end-of-file: lnch_opts.c */
