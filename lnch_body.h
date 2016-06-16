/* See LICENSE for license details. */

/*

Module: lnch_body.h

Description:

    Container for modules.

*/

/* Reverse include guard */
#if defined(INC_LNCH_BODY_H)
#error include lnch_body.h once
#endif /* #if defined(INC_LNCH_BODY_H) */

#define INC_LNCH_BODY_H

/* Predefine context */
struct lnch_ctxt;

/* Interface: */

/* Initialize module. */
struct lnch_ctxt *
lnch_body_init(
    int const argc,
    char const * const * const argv);

/* Cleanup module. */
void
lnch_body_cleanup(
    struct lnch_ctxt * const p_ctxt);

/* Main event loop. */
void
lnch_body_run(
    struct lnch_ctxt * const p_ctxt);

/* end-of-file: lnch_body.h */
