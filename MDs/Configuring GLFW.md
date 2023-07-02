#Configuring GLFW

Download the GLFW bin files from [Download](https://www.glfw.org/download.html) and extract only the ``include`` and ``lib-vc2022`` folders to ``Dependencies/GLFW``

To make it work on Windows open the OpenGL project configuration and set the following items.

### C/C++ -> Aditional Include Directories

``$(SolutionDir)Dependencies\GLFW\include``


### Linker -> General -> Additional Library Directories

``$(SolutionDir)Dependencies\GLFW\lib-vc2022``

### Linker -> Input -> Additional Dependencies

The ``glfw3.lib`` and ``opengl32.lib`` came from lib folder exported to ``Dependencies``. The rest are required libs for Windows.

``opengl32.lib;glfw3.lib;User32.lib;Gdi32.lib;Shell32.lib;``