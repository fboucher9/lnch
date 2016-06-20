/* See LICENSE for license details. */

/*

Module: lnch_feature_movesize.h

Description:

    Move and resize windows using mouse.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_MOVESIZE_H)
#error include lnch_feature_movesize.h once
#endif /* #if defined(INC_LNCH_FEATURE_MOVESIZE_H) */

#define INC_LNCH_FEATURE_MOVESIZE_H

/* Verify that feature is enabled. */
#if !defined(LNCH_FEATURE_MOVESIZE)
#error movesize feature not enabled.
#endif /* #if !defined(LNCH_FEATURE_MOVESIZE) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

/* All-in-one feature entry point */
void
lnch_feature_movesize_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev);

/* end-of-file: lnch_feature_movesize.h */
