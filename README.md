# POMEGRANATE GAME ENGINE (WIP)
![Pomegranate](img/PomegranateEngineText.png)
## About
Pomegranate engine is an easily modable 3d game engine. It intends to be a nice simple engine, with a readable, minimal UI, and easily modifiable with custom plugins. The engine currently is in pre-alpha, and will probably be there for a long time. 

## Supported Platforms

Ubuntu

Windows (Cmake modifications will need to be made although it will run.)

macOS (Someday maybe)

## Compiling

To be honest I barely know how I compiled this. So good luck.  

Assimp, GLFW, and OpenGL are required.

### Linux

Install the required packages:

```sudo apt-get install libassimp-dev```

```sudo apt-get install libglfw3-dev```

Clone the repo

```git clone https://github.com/Large-Guy/Pomegranate-Game-Engine.git```

```cd Pomegranate-Game-Engine-main```

Cmake and make

```Cmake .```

```make```


If you are running this on something other than linux you will probably have to compile teascript yourself. https://github.com/RevengerWizard/teascript
## Documentation
Documentation for both Teascript and the engine are WIP.

[Docs](docs/engine.md)

[Teascript](docs/teascript.md)
