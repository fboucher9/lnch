/* See LICENSE for license details. */

/*

Module: lnch_feature_child.h

Description:

    Launch of child process via hotkey.

*/

/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_CHILD_H)
#error include lnch_feature_child.h once
#endif /* #if defined(INC_LNCH_FEATURE_CHILD_H) */

#define INC_LNCH_FEATURE_CHILD_H

/* Verify configuration */
#if !defined(LNCH_FEATURE_CHILD)
#error child feature not enabled
#endif /* #if !defined(LNCH_FEATURE_CHILD) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

/* All-in-one feature entry point */
void lnch_feature_child_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent const * const pev);

/* end-of-file: lnch_feature_child.h */
