/* See LICENSE for license details. */

/*

Module: lnch_opts.h

Description:

    Command line options.

*/

/* Reverse include guard */
#if defined(INC_LNCH_OPTS_H)
#error include lnch_opts.h once
#endif /* #if defined(INC_LNCH_OPTS_H) */

#define INC_LNCH_OPTS_H

/* Predefine context handle. */
struct lnch_ctxt;

/*

Structure: lnch_opts

Description:

    Collection of command-line options for all features.

*/
struct lnch_opts
{
    unsigned int i_mod_mask;

    unsigned int a_padding[1u];

    char const * p_key_mod;

#if defined(LNCH_FEATURE_BORDER)
    char const * p_color_enter;
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_BORDER)
    char const * p_color_leave;
#endif /* #if defined(LNCH_FEATURE_BORDER) */

#if defined(LNCH_FEATURE_CHILD)
    char const * p_key_child;
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_CHILD)
    char const * p_exec_child;
#endif /* #if defined(LNCH_FEATURE_CHILD) */

#if defined(LNCH_FEATURE_FOCUS)
    char const * p_key_focus_left;
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_FOCUS)
    char const * p_key_focus_next;
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_FOCUS)
    char const * p_key_focus_right;
#endif /* #if defined(LNCH_FEATURE_FOCUS) */

#if defined(LNCH_FEATURE_GRID)
    char const * p_key_grid_left;
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    char const * p_key_grid_right;
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    char const * p_key_grid_snap;
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    char const * p_key_grid_reset;
#endif /* #if defined(LNCH_FEATURE_GRID) */

#if defined(LNCH_FEATURE_GRID)
    char const * p_key_grid_toggle;
#endif /* #if defined(LNCH_FEATURE_GRID) */

}; /* struct lnch_opts */

/* Interface: */

/* Initialize module. */
void lnch_opts_init(
    struct lnch_ctxt const * const p_ctxt,
    int const argc,
    char const * const * const argv);

/* end-of-file: lnch_opts.h */
