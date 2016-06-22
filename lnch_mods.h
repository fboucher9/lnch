/* See LICENSE for license details. */

/*

Module: lnch_mods.h

Description:

    Define a list of key and button modifiers.  Each key or button is grabbed
    multiple times, with different modifiers.  This is done to ensure that Caps
    Lock and Num Lock do not affect hotkeys.  The Num Lock mask has been
    hardcoded to avoid scanning the keyboard mapping table.

*/

/* Reverse include guard */
#if defined(INC_LNCH_MODS_H)
#error include lnch_mods.h once
#endif /* #if defined(INC_LNCH_MODS_H) */

#define INC_LNCH_MODS_H

static unsigned int const
    mods[] =
{
    /* CapLock is off and NumLock is off */
    0,

    /* CapLock is ON and NumLock is off */
    LockMask,

    /* CapLock is off and NumLock is ON */
    Mod2Mask,

    /* CapLock in ON and NumLock is ON */
    Mod2Mask | LockMask

};

/* end-of-file: lnch_mods.h */
