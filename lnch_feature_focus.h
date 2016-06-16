/* See LICENSE for license details. */

/*

Module: lnch_feature_focus.h

Description:

    Group of hotkeys to control input focus.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_FOCUS_H)
#error include lnch_feature_focus.h once
#endif /* #if defined(INC_LNCH_FEATURE_FOCUS_H) */

#define INC_LNCH_FEATURE_FOCUS_H

/* Verify that feature is enabled. */
#if !defined(LNCH_FEATURE_FOCUS)
#error focus feature not enabled.
#endif /* #if !defined(LNCH_FEATURE_FOCUS) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

void
lnch_feature_focus_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * p_event);

/* end-of-file: lnch_feature_focus.h */
