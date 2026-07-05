# NaiViewer
A program for simulating 2-state isotropic non-totalistic naiverules, like NaiveLife, for example.

Features:

- Full support for INT rules

- Mouse drawing

- Selections, copying, and pasting

- Random pattern generation

- Neighborhood-based coloring

How to use

First, clone this repository on your machine. Next, run the command

`cd (path to NaiViewer directory)`

and then

`cc naiviewer.c -o naiviewer $(pkg-config --cflags --libs raylib)`

Then, whenever you want to run NaiViewer, just run the command

`./naiviewer`

You will be prompted for a rule. Write the rule in standard B.../S... notation, or, if you want to use standard NaiveLife, just hit Enter.

List of keyboard shortcuts:

- Use the arrow keys to move the cursor short distances.

- Use WASD to move the cursor long distances.

- Use C to copy patterns, X to cut them, and V to paste them.

- Press Shift to start a selection and Shift again to end it after moving the cursor to the opposite corner of the selection.

- If you want to remove a selection, just use the 0 key.

- If you want to clear the board, press 0 (if there is a selection) and press Delete/Backspace.

- Press K to toggle neighborhood-based coloring, which is off by default.

- Press I to invert the current selection, or, if there is none, the whole world will be inverted.
