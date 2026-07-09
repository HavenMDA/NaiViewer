# NaiViewer
A program for simulating isotropic non-totalistic CA, like Life and NaiveLife.

Features:

- Full support for INT, BSFKL, and Generations rules (like Brain's Brain, B2/S/G3)

- Mouse drawing

- Selections, copying, and pasting

- Random pattern generation

- Neighborhood-based coloring

How to use

First, clone this repository on your machine. Next, run the command

`cd (path to NaiViewer directory)`

and then

`cc naiviewer.c -o naiviewer $(pkg-config --cflags --libs raylib)`

(Note that this command may differ depending on your operating system but this is the command for MacOS).

Then, whenever you want to run NaiViewer, just run the command

`./naiviewer`

You will be prompted for a rule. Write the rule in standard B.../S... notation, or, if you want to use standard Life, just hit Enter. If you want to run NaiveLife, write NB3/S23, and if you want to generate a random, interesting (no B0, B1, or B2, with B3ai) rule, write "R" and hit Enter.

List of keyboard shortcuts:

- Use the arrow keys to move the cursor short distances.

- Use WASD to move the cursor long distances.

- Use C to copy patterns, X to cut them, and V to paste them.

- Press Shift to start a selection and Shift again to end it after moving the cursor to the opposite corner of the selection.

- If you want to remove a selection, just use the 0 key.

- If you want to clear the board, press 0 (if there is a selection) and press Delete/Backspace.

- Press K to toggle neighborhood-based coloring, which is off by default. This is not compatible with Generations.

- Press I to invert the current selection, or, if there is none, the whole world will be inverted.
