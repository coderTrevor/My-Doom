# My-Doom
This is simply doomgeneric ported to My OS. See https://github.com/ozkl/doomgeneric for more info about doomgeneric. It's an excellent place to start for us hobbyist OS developers!

This port has **everything** that isn't completely necessary for the game to run ripped out of it. fprintf()? Nope. fwrite()? What for? stdio? How about no. ... You get the idea.

Nearly every bug that MyOS has (like fopen returning NULL) was hastily worked around instead of being fixed to get this port running ASAP.

MyOS doesn't like it when the game looks for every possible .wad file, so this port only looks for "doom.wad." You can rename the shareware version from doom1.wad to doom.wad and it will work.

As of the first commit, keyboard input hasn't been implemented, the game just runs and shows demos.

There's a bug somewhere that causes the game to crash when updating the arms display; I've kept the display from getting updated for now.