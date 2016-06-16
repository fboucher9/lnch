# lnch - X window manager and launcher for bfst terminal

    The source is based on tinywm and dwm.

Installation:

    make

    sudo cp lnch /bin

    lnch & disown

Features:

    -   Mouse is used to move or resize a client window

    -   Hotkey to launch a new terminal

    -   Add a border around client window

    -   Hotkey to position a client window

    -   Hotkey to switch focus between clients

    -   Filtering of X errors

    -   Handle window manager events to fix Firefox

Hotkeys:

    [ q ] [ w ] [ e ]
      |     |     |
      |     |     +---------- Position window in right quadrants
      |     +---------------- Position window in next monitor
      +---------------------- Position window in left quadrants

    [ a ] [ s ] [ d ]
      |     |     |
      |     |     +---------- Focus window in right monitor
      |     +---------------- Focus next window in current monitor
      +---------------------- Focus window in left monitor

    [ z ] [ x ] [ c ]
      |     |     |
      |     |     +---------- Position window to pointer quadrant
      |     +---------------- Spawn new terminal
      +---------------------- Resize current window to 80x25

Not implemented yet:

    -   properties

    -   hints

    -   fullscreen atom

    -   Cursor shapes

    -   Kill of client

    -   Clean exit

    -   Colors for focus

    -   scan of existing clients

