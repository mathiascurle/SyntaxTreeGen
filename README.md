# Syntax Tree Generator

## Build and run macOS/linux

````shell
./scripts/make.sh
````

## Build and run Windows

Can also link raylib statically by changing STATIC_LINK to true on line 66 in the CMakeLists.txt file.

````shell
./scripts/make.bat
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
