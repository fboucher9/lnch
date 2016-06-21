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
    char const * p_color_enter;

    char const * p_color_leave;

    char const * p_key_mod;

    char const * p_key_child;

    char const * p_key_focus_left;

    char const * p_key_focus_next;

    char const * p_key_focus_right;

    char const * p_key_grid_left;

    char const * p_key_grid_right;

    char const * p_key_grid_snap;

    char const * p_key_grid_reset;

    char const * p_key_grid_toggle;

    char const * const * p_exec_child;

}; /* struct lnch_opts */

/* Interface: */

/* Initialize module. */
void lnch_opts_init(
    struct lnch_ctxt const * const p_ctxt,
    int const argc,
    char const * const * const argv);

/* end-of-file: lnch_opts.h */
