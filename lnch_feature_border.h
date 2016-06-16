/* See LICENSE for license details. */

/*

Module: lnch_feature_border.h

Description:

    Force a border around each window.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_BORDER_H)
#error include lnch_feature_border.h once
#endif /* #if defined(INC_LNCH_FEATURE_BORDER_H) */

#define INC_LNCH_FEATURE_BORDER_H

/* Verify that feature is enabled. */
#if !defined(LNCH_FEATURE_BORDER)
#error border feature not enabled.
#endif /* #if !defined(LNCH_FEATURE_BORDER) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

void
lnch_feature_border_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * p_event);

/* end-of-file: lnch_feature_border.h */

