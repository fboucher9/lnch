/* See LICENSE for license details. */

/*

Module: lnch_main.c

Description:

    Main entry point of lnch application.

*/

/* Include operating-system header files */
#include "lnch_os.h"

/* Configuration options */
#include "lnch_cfg.h"

/* Body */
#include "lnch_body.h"

/* Main */
#include "lnch_main.h"

/*

Function: lnch_main

Description:

    Parse command line options and dispatch to lnch_body object.

*/
int lnch_main(
    int const argc,
    char const * const * const argv)
{
    struct lnch_ctxt * const p_ctxt = lnch_body_init(argc, argv);

    if (p_ctxt)
    {
        lnch_body_run(p_ctxt);

        lnch_body_cleanup(p_ctxt);
    }

    return 0;

} /* lnch_main() */

/* end-of-file: lnch_main.c */
