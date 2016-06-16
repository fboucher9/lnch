/* See LICENSE for license details. */

/* OS-specific header files */
#include "lnch_os.h"

/* Main */
#include "lnch_main.h"

/*

Function: main()

Description:

    Dispatch OS-specific entry point to OS-independent lnch_main.

*/
int main(
    int argc,
    char * * argv)
{
    return lnch_main(argc, (char const * const *)(argv));

} /* main() */

/* end-of-file: lnch_os.c */
