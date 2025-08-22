# Syntax Tree Generator

## Build and run macOS/Linux

````shell
./scripts/make.sh
````

## Build and run Windows

````shell
./scripts/make.bat
````

## Run

*In CMakeLists.txt change STATIC_LINK on line 66 to true for linking raylib statically*

````shell
./SyntaxTreeGen
````

## Keybinds

````
A     - Add node at mouse pos
C     - Connect the selected node with the previously selected node
X     - Delete selected node
ENTER - Start typing in selected node
ESC   - Exit program (remove bind)
````

## Mouse

````
Ctrl+leftMouse or rightMouse to drag the camera
````

---

### Export example:

![](img/The_quick_brown_fox_0.png)

### Application example:

![](img/example_1.png)
