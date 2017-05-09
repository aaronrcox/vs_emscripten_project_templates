# Emscripten Project Templates
#### For visual studio 2015 and 2017
I've created some project templates that allows me to skip the project properties setup phase.
There are 3 template projects, each can build to Windows(x86 | x64) and emscripten for debug and release build. 

 - Console Application Template
 - SDL1.2 Template
 - SDL2 Template

Each of these projects are part of a single solution. If everything is setup correctly on your machine, they should be able to compile and run for all platforms without issue.

# Prerequisite
 - Install emscripten for windows
 - Add emscripten toolchain to your msbuild folder: https://github.com/crosire/vs-toolsets 
 - If using visual studio 2017: make sure [C++ 2015.3 v140 toolset(x86,x64)] option was checked when installing.


#### Running under windows:
Only one setting needs to be changed when running the project for windows (x86 or x64), the working directory:
Open project properties and set your working directory to:
```
$(SolutionDir)bin\
```


#### Running in the Browser:
You will need to run a local web server to serve the generated html files.
I use nodejs with pushstate-server installed globally.
There are thousands of tools available to do a simular thing, if you have something else available, great!. 

Make sure to run the server from your project output directory, then open localhost in your browser pointing to the generated html file.

The project output directory is:
```
$(SolutionDir)temp\$(Platform)\$(ProjectName)\$(Configuration)\
```
