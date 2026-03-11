## ECS in C89
A simple Entity Component System implementation in C89. My implementation is a basic introductory ECS with a few of my own ideas and approaches, though not in a real 'production' project setting.
This simple demo is not a 1-to-1 of how i would do everything in a production project. For further production / real scenario details, read the source comments with the 'In real:' prefix.

## Building information
The project depends only on SDL3 for two (2) important reasons:
- To showcase abstracting a pre-existing API and object (struct) into a component
- Show something more interesting than some console output
It is required you have SDL3 and the relevant `pkg-config` to build the project.
If you are using MSVC for some reason, and want to build the project, create a solution and set up your SDL3 dependency in your PATH manually.

## Source overview
What is the Component API?
- It is the API a given component uses to implement its functionality, it does not include the `map.h` utility, just `component.h`.
  exposed in : `inc/ecs/component.h`
  implementation : `src/ecs.c`
What is the Entity API?
- It is the API that allows registration/unregistration of entities.
  exposed in : `inc/ecs/entity.h`
  implementation : `src/ecs.c`

Individual components can be found in the `components/` folders in `src/` and `inc/`.
Some rendering related code lives in the `renderer` folders in `src/` and `inc/`.
Finally, I decided for project simplicity to keep `map.h` in the `inc/ecs/` folder, and be implemented in `src/map.c`.

## Some things about my implementation
Everything is in the `.bss` segment as static globals, but the system contains a stub (`FreeECS`) and unregistration mechanism for freeing system and component related memory.
My map implementation maps an ID to a structure using two 1D arrays (one ID array, and one struct array), which are provided by the API User.
ID generation uses the SplitMix64 algorithm, because it has very good bit coverage. Usually bit coverage does not matter too much, but ECSs can be used for very intensive tasks with many entities.

---
Enjoy! - temple-fed | License : GPL3 (See LICENSE file)
