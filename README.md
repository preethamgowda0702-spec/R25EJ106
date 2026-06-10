# 2D-Graphics-Editor

A lightweight, terminal-based 2D graphics application written in C. This project implements a dynamic coordinate canvas using character arrays, allowing users to draw, erase, and manipulate custom geometric structures directly through an interactive command menu.

## 🚀 Key Features
* **Dynamic 2D Grid Storage:** Maintains a structured `30x80` grid representing matrix coordinates.
* **Geometric Tool Suite:** Real-time geometric rendering functions for:
    * Solid Rectangles (`*`)
    * Custom Lines (`#`)
    * Mathematical Circles (`O`) using distance-radius formulations
    * Right-angled Triangles (`^`)
* **Live Workspace Modification:** Explicit delete/erase modes that overwrite canvas regions back to background dot layers (`.`).
* **Active State Updates:** Automatic terminal screen-flushing loops for real-time visualization of shape plotting inputs.

## 🛠️ How to Compile & Run

To run the editor locally on your machine, clone the repository and execute the following commands in your terminal:

```bash
# Compile the source code (links the math library explicitly)
gcc main.c -o editor.exe -lm

# Run the executable program
./editor.exe
