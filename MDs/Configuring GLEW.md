# Configuring GLEW

As OpenGL are just expecifications implemented by the Graphics Driver, to use the modern OpenGL is required to get the existing functions implementation pointers to use them. And this is what GLEW does. There's another option called [Glad](https://glad.dav1d.de).

Download the GLEW bin files from [Download](https://glew.sourceforge.net/index.html) and extract to ``Dependencies/GLEW``

To make it work on Windows open the OpenGL project configuration and set the following items.

### C/C++ -> Aditional Include Directories

``$(SolutionDir)Dependencies\GLEW\include``

### Linker -> General -> Additional Library Directories

``$(SolutionDir)Dependencies\GLEW\lib\Release\Win32``

### Linker -> Input -> Additional Dependencies

There are two files in the lib folder: ``glew32.lib`` and ``glew32s.lib``. One is to be used as DLL and the other as static library. So...

``glew32s.lib``

To define as static library is required to set a Preprocessor Definitions in project properties ``C/C++ -> Preprocessor -> Preprocessor Definitions`` as ``GLEW_STATIC``

# Initializing

``if (glewInit() != GLEW_OK)```

This need to be done after creating a window context.