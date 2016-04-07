Linux mouse emulator
====================

Download
--------
Binaries can be downloaded from `bin` folder.

Prerequisites
-------------
`uinput` kernel module

`xwininfo` program

Usage
-----
Single command can be run with:
`./autoclicker -c [command]`

List of commands can be run from file:
`./autoclicker -f [filename]`

Commands
--------
### setup commands:
`set_delay [device] [default_delay]`


### mouse commands:
`mouse_left   [count = 1]  [delay = default_delay]`
performs left click

`mouse_right  [count = 1]  [delay = default_delay]`
performs right click

`mouse_middle [count = 1]  [delay = default_delay]`
performs middle click


`mouse_move   [x] [y]  [delay = default_delay]`
moves the cursor by given offset

`mouse_reset [delay = default_delay]`
sets the mouse position to (0, 0)

`mouse_scroll [amount] [delay = default_delay]`
scrolls the mouse wheel by given amount