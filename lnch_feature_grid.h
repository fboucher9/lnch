/* See LICENSE for license details. */

/*

Module: lnch_feature_grid.h

Description:

*/


/* Reverse include guard */
#if defined(INC_LNCH_FEATURE_GRID_H)
#error include lnch_feature_grid.h once
#endif /* #if defined(INC_LNCH_FEATURE_GRID_H) */

#define INC_LNCH_FEATURE_GRID_H

/* This file should only be included when feature is enabled. */
#if !defined(LNCH_FEATURE_GRID)
#error grid feature not enabled
#endif /* #if !defined(LNCH_FEATURE_GRID) */

/* Predefine context handle */
struct lnch_ctxt;

/* Interface: */

void
lnch_feature_grid_event(
    struct lnch_ctxt const * const p_ctxt,
    XEvent * pev);

/* end-of-file: lnch_feature_grid.h */
