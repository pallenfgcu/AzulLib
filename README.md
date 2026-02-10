# AzulLib
*Core Library for Azul’s World (C++ / SFML)*

**Repository:** https://github.com/pallenfgcu/AzulLib.git

AzulLib is the core C++ library that implements the Azul’s World environment. It provides the underlying world model, rendering, and API used by student-facing projects built on top of it.

> ⚠️ **Students:** You generally should **not clone this repository directly.**  
> Students should clone the **Azul starter project** instead:  
> https://github.com/pallenfgcu/Azul.git  
> AzulLib is included automatically as a dependency when building the Azul project.

---

## What is AzulLib?

AzulLib contains the implementation of:

- The grid-based world model
- World geometry (walls, boundaries, obstacles)
- Azul (FGCU’s mascot) as a programmable agent
- Rendering and animation of the world
- Interaction with objects such as graduation caps

AzulLib exposes a small, intentionally constrained API (e.g., movement, turning, sensing, and object interaction) designed to support introductory programming instruction.

---

## How AzulLib is Used

AzulLib is not meant to be built or used by students directly. Instead:

- The **Azul** executable project uses CMake’s `FetchContent` to download AzulLib at a specific version tag.
- When students configure the Azul project, AzulLib is built automatically as part of the build process.
- Students interact only with the public API of `fgcu::Azul` in their `main.cpp` file.

This design ensures:

- Consistent environments across student machines
- Reproducible builds for instructors and TAs
- A clean separation between instructional scaffolding (Azul project) and core functionality (AzulLib)

---

## Dependency: SFML

AzulLib is built on top of **SFML (Simple and Fast Multimedia Library)**.

**SFML provides:**

- Cross-platform window and graphics rendering
- 2D drawing primitives
- Event handling and input
- Timing and basic multimedia support

AzulLib uses SFML to:

- Render the grid-based world
- Display Azul and world objects
- Provide real-time visual feedback as student programs execute

SFML is fetched and built automatically as part of the Azul project’s CMake configuration; no manual installation is required by students.

More information about SFML:  
https://www.sfml-dev.org/

---

## Audience

This repository is primarily intended for:

- Instructors integrating Azul’s World into coursework
- Teaching assistants supporting Azul-based assignments
- Developers extending or maintaining the Azul environment
- Other educators exploring visual programming environments for CS1/CS2

---

## Versioning and Releases

AzulLib uses semantic versioning (e.g., `v1.0.1`) to ensure reproducibility across semesters.

Instructor-facing projects (such as the Azul starter project) pin AzulLib to a specific release tag. This ensures that:

- Student builds are consistent
- Behavior does not change unexpectedly mid-semester
- Course materials remain aligned with the software version

Please refer to the repository **tags/releases** for available versions.

---

## Repository Structure (High-Level)

```
AzulLib/
├── include/           # Public headers
├── src/               # Library implementation
├── doc/               # Generated API documentation
├── CMakeLists.txt    # Build configuration
└── README.md
```

---

## Extending AzulLib

Instructors or developers interested in extending AzulLib (e.g., new world elements, new sensing capabilities, new scenario features) are encouraged to:

- Fork the repository
- Create feature branches
- Submit pull requests with documentation of pedagogical intent

Maintaining a stable public API for students is a core design goal of the project.

---

## License

Please refer to the LICENSE file for terms of use and distribution.
