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
`mouse_right  [count = 1]  [delay = default_delay]`
`mouse_middle [count = 1]  [delay = default_delay]`

`mouse_move   [x] [y]  [delay = default_delay]`
`mouse_scroll [amount] [delay = default_delay]`