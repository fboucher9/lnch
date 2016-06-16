/* See LICENSE for license details. */

/*

Module: lnch_display.h

Description:

    X resources common to all modules.

*/

/* Reverse include guard */
#if defined(INC_LNCH_DISPLAY_H)
#error include lnch_display.h once
#endif /* #if defined(INC_LNCH_DISPLAY_H) */

#define INC_LNCH_DISPLAY_H

/*

Structure: lnch_display

Description:

    Storage for X resources.

*/
struct lnch_display
{
    /* Pointer to display */
    Display* dpy;

    /* Window id of root window */
    Window root;

    /* Root window event mask selection.  Each plugin may add flags to this variable */
    long root_event_mask;

    /* Index of default screen */
    int scr;

    /* Width of screen */
    int sw;

    /* Height of screen */
    int sh;

}; /* struct lnch_display */

/* Interface: */

/* Initialize module. This is C code, so we can't call it a constructor? */
char
lnch_display_init(
    struct lnch_ctxt const * const p_ctxt);

/* Cleanup module. This is C code, so we can't call it a destructor? */
void
lnch_display_cleanup(
    struct lnch_ctxt const * const p_ctxt);

/* end-of-file: lnch_display.h */
