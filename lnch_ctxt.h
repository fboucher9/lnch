/* See LICENSE for license details. */

/*

Module: lnch_ctxt.h

Description:

    Context structures.

*/

/* Reverse include guard */
#if defined(INC_LNCH_CTXT_H)
#error include lnch_ctxt.h once
#endif /* #if defined(INC_LNCH_CTXT_H) */

#define INC_LNCH_CTXT_H

/* Predefine body module */
struct lnch_body;

/* Predefine display module */
struct lnch_display;

/* Predefine key module */
struct lnch_key;

/*

Structure: lnch_ctxt

Description:

    Pointers to other modules.

*/
struct lnch_ctxt
{
    /* Pointer to body module */
    struct lnch_body * p_body;

    /* Pointer to display module */
    struct lnch_display * p_display;

    /* Pointer to key module */
    struct lnch_key * p_key;

}; /* struct lnch_ctxt */

/* end-of-file: lnch_ctxt.h */
