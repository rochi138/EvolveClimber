# EvolveClimber
Based off of Cary Huang's Evolution Simulator. Code and demo available on [Open Processing](https://openprocessing.org/sketch/377698). YouTube series available as [Evolution Simulator](https://www.youtube.com/watch?v=GOFws_hhZs8).

This is an evolution simulator using genetic algorithms to produce a climbing creature made of nodes and muscles. Built using Dear ImGUI and available as a web app at [https://rochi138.github.io/EvolveClimber/imgui.html](https://rochi138.github.io/EvolveClimber/imgui.html).

## To Run
### Setup
Requires emsdk and imgui to build and Live Server VS Code plug-in to run. Git clone outside this repo (recommended).
```
git clone https://github.com/emscripten-core/emsdk.git
source ../emsdk/emsdk_env.sh
emsdk install 2.0.0
emsdk activate 2.0.0
```
### Build
```
make
```
### Run
```
source ../emsdk/emsdk_env.sh
```
^ run once per terminal session
1. Open repo folder in VS Code
2. Right-click imgui.html
3. Open with Live Server
