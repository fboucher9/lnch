/* See LICENSE for license details. */

/*

Module: lnch_feature_button2.h

Description:

    Snap of window position using mouse button 2.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_BUTTON2_H)
#error include lnch_feature_button2.h once
#endif /* #if defined(INC_LNCH_FEATURE_BUTTON2_H) */

#define INC_LNCH_FEATURE_BUTTON2_H

/* Verify configuration */
#if !defined(LNCH_FEATURE_BUTTON2)
#error button2 feature not enabled.
#endif /* #if defined(LNCH_FEATURE_BUTTON2) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

/* All-in-one feature entry point */
void
lnch_feature_button2_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev);

/* end-of-file: lnch_feature_button2.h */
