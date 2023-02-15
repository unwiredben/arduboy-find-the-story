# Find the Story

a Arduboy FX game developed by Ben Combee

<img src="screenshot.png" width="512" height="256" alt="screenshot of the game title screen">

This is a game for the ArduboyFX and Arduboy Mini handheld computers.
It's a coloring book application, telling the story of the creation of the Arduboy
in a series of images that you need to uncover from a collection of shapes,
some marked with a dot to indicate that they should be colored in.

You move the cursor with the arrow keys, including moving off the edge of the
screen to scroll through the image.  The A button will try to color in the
shape under the cursor if it's part of the image.  The B button will toggle
between a zoomed-in view where you can color sections and a zoomed-out view
that shows the colored-in parts of the whole page.

When you complete a page, you'll automatically zoom out, and then you can hit
A to move on to a bit of narrative about the page, and then continue to the
next image.

While the Arduboy screen is 128x64, we define each page as 512x256, making it
four times larger than the main view.

The initial game will only support one page, but a later version will have
multiple pages, with the data for the pages saved into the Arduboy FX's flash
memory.

<a
href="https://felipemanga.github.io/ProjectABE/?url=https://raw.githubusercontent.com/unwiredben/arduboy-find-the-story/main/FindTheStory.hex&skin=arduboy">Play
it in your browser using ProjectABE!</a>

The main branch is setup for building in the PlatformIO system.

## LICENSE

Copyright (C) 2020-2023, Ben Combee \
Released under Apache 2.0 license

Arduboy2 library: \
Copyright (c) 2016-2020, Scott Allen \
All rights reserved.

The Arduboy2 library was forked from the Arduboy library: \
https://github.com/Arduboy/Arduboy \
Copyright (c) 2016, Kevin "Arduboy" Bates \
Copyright (c) 2016, Chris Martinez \
Copyright (c) 2016, Josh Goebel \
Copyright (c) 2016, Scott Allen \
All rights reserved. \
which is in turn partially based on the Adafruit_SSD1306 library \
https://github.com/adafruit/Adafruit_SSD1306 \
Copyright (c) 2012, Adafruit Industries \
All rights reserved.

This also uses code from these libraries:

* Arduboy2 library from https://github.com/MLXXXp/Arduboy2
* ArduboyTones library from https://github.com/MLXXXp/ArduboyTones