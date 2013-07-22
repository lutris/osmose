           _______                  _______
          |       |.-----.--------.|       |.-----.-----.
          |   -   ||__ --|        ||   -   ||__ --|  -__|
          |_______||_____|__|__|__||_______||_____|_____|
           _______                  __         __
          |    ___|.--------.--.--.|  |.---.-.|  |_.-----.----.
          |    ___||        |  |  ||  ||  _  ||   _|  _  |   _|
          |_______||__|__|__|_____||__||___._||____|_____|__|
       Version 0.9.96 - public release, written by Bruno Vedder.


Osmose means:
-------------

Object      Oriented
       S.m.s.         Emulator.

In brief it's an Sega Master System / Game Gear emulator encapsulated into C++
classes :-)


What's new:
-----------

Osmose now owns a clean graphical user interface based on QT. QT was the first
GUI lib powerfull enough to refresh display at 60hz. So no more SDL is used now.

-Switch sound system to use ALSA
-GUI development using QT.
-Rendering / Key mapping adapted to QTopenGL.
-Configuration system rewritten.


Dependancies to run:
--------------------
-QT 4.6
-Alsa


Dependancies to recompile:
--------------------------

-QT 4.6 qqchose Qt-dev
-Alsa libasound-dev

To build osmose, do from the source directory:
----------------
qmake
make


Vertical synchronisation:
-------------------------

Osmose uses double buffering to avoid tearing image on the screen, but this does
not guaranty that the rendering will be synchronized with the screen rendering.

Keep in mind that Osmose uses openGL for rendering and filtering.

Synchronisation is a matter of choice : High frames per second or Synchronisation.
On my Ubuntu, the closed source driver provide an option in the tab performance:
"Sync to VBlank". When selected the rendering is stable, without flickering. The
CPU usage is a bit higher. Without this option, the Osmose rendering is sometime
teared but uses lower CPU. I suppose that this option is available on all the 
drivers. Make your choice !


Sound:
------

Osmose uses ALSA for the sound system. It has been reported that concurrent
application using the sound channel can inhibit osmose sound rendering. So,
avoid watching videos while playing with osmose !


Features:
--------

-SMS: Good compatibility. At this stage, the emulator can run* 96% of commercial
 games and public demos, except games that relies on codemaster mapper, which
 work  but does not have proper video mode emulated.
-Game Gear: Good compatibility. At this stage, the emulator can run 98.0%* of
 game gear ROMS.
-SN76489 Sound is supported.
-support. for .zip .sms  and .gg format.
-Video filters: bilinear or nearest neighbour (default)
-Pad(keyboard or joystick mapped) emulation.
-PAL/NTSC Timing.
-Japanese/Export console.
-In game Screenshots, GFX rip, sound shot.
-Configurable keyboard configuration.
-Joystick support, congigurable button assignement.
-Drag and drop your ROMS into the emulator window to run games.

*Due to the huge number of game gear/sms (around 1300) roms, games have not been
deeply tested.

____________________________________________________________________________________


  |                                 |                                       _|       
  __ \    __| _  /      _` |   __|  __|   _ \   __|  _ \   __ \    _ \     |     __| 
  |   |  (      /      (   | \__ \  |     __/  |    (   |  |   |   __/     __|  |    
 _.__/  \___| ___| _) \__,_| ____/ \__| \___| _|   \___/   .__/  \___| _) _|   _|    
                                                          _|                         
____________________________________________________________________________________

            This file has been downloaded from : http://bcz.asterope.fr/
____________________________________________________________________________________

    Need more information or contact with author  : See contact page on the site
    or send an email to bruno@asterope.fr


