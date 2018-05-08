## Hello Rectangle and Cube for macOS

`hello-rect` and `hello-cube` are each standalone.

### Project structure

It looks like this (`tree hello-rect` with explanation):

    hello-rect
    ├── bin
    │   ├── macos-bundle
    │   │   └── hello-rect.app
    │   │       └── Contents
    │   │           ├── Frameworks
    │   │           │   └── <dylibs that .app requires>
    │   │           ├── MacOS
    │   │           │   ├── hello-rect     <-- the actual executable, with modified refs to dylibs
    │   │           │   └── launcher.sh    <-- wrapped entry point in Info.plist to ensure working dir
    │   │           ├── Resources          <-- GLFW will change cwd here
    │   │           │   └── <shaders>
    │   │           └── Info.plist
    │   └── unix-exec   
    │       ├── hello-rect    <-- freshly from g++-8, reads shader file from cwd
    │       └── <shaders>
    ├── build    
    │   └── <midway object files>
    ├── resc
    │   ├── shader
    │   │   ├── rect.frag
    │   │   └── rect.vert
    │   ├── Info.plist
    │   └── launcher.sh
    ├── src       
    │   ├── include
    │   │   ├── draw.hpp
    │   │   └── public.hpp
    │   ├── draw.cpp
    │   ├── init-shader.cpp
    │   └── window.cpp    // main() here
    └── Makefile


### Build 

To satisfy explicit requirements: (there might be other brewed tools in play but I'm not quite sure)

    $ brew install gcc glew glfw

Just `make` in each projects' root dir. For details, read `Makefile`.

The standalone mac `.app` version can be found in `bin/macos-bundle`, should be okay to open anywhere; the unix executable only works when current working dir contains all shader files.
    
