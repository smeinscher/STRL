<a name="readme-top"></a>



<!-- PROJECT LOGO -->
<br />
<div align="center">

<h3 align="center">STRL</h3>

  <p align="center">
    A simple game framework.
    <br />
    <br />
    <a href="https://github.com/smeinscher/STRL">View Demo</a>
  </p>
</div>

## About The Project

This is a simple game framework made for educational purposes. The goal is to eventually create my own games with this.

Motivation:
* I enjoy programming, not so much learning the UI or functionality of a traditional game engine.
* The extra time spent working on this will allow me to polish my programming skills while making games.
* While not the primary goal, I want to learn how to make projects publicly accessible, and easy to get working on different machines.

### External Tools and Libraries

Graphics APIs:
* [OpenGL](https://www.opengl.org/)
* [Vulkan? (to be implemented maybe?)](https://www.vulkan.org/)

Libraries:
* [GLFW](https://www.glfw.org/)
* [glad](https://github.com/Dav1dde/glad)
* [stb_image](https://github.com/nothings/stb)
* [glm](https://github.com/g-truc/glm)
* [Box2D](https://box2d.org/)
* [Dear ImGui (to be implemented)](https://github.com/ocornut/imgui)

Tools:
* [CLion](https://www.jetbrains.com/clion/)
* [CMake](https://cmake.org/)
* [vcpkg](https://vcpkg.io/en/)

Working Compilers:
* [MinGW](https://www.mingw-w64.org/)

<!-- GETTING STARTED -->
## Getting Started

Support currently only for Windows. In theory, it should work on Linux, but has not been tested.
Try it out and let me know how it goes!

### Prerequisites

CMake is required for building. vcpkg is also nice, but might be able to get away with not having it
(with some modifications to the CMakeLists.txt files). Developed in CLion, but there could be ways to get this working
on other IDEs/configurations. Future releases will take this into account. MinGW is used for compilation. Has not been
tested on other compilers.

1. Download and install CLion (https://www.jetbrains.com/clion/)
    * Alternatively, download and install MinGW (https://www.mingw-w64.org/) and CMake (https://cmake.org/download/) separately. 
    * Steps to get it working from here are unknown at this time.
2. Download and install vcpkg (guide here: https://github.com/microsoft/vcpkg)

### Building

_This assumes you are using CLion. Future releases will take other configurations into account._

1. Clone the repo
    ```sh
    git clone https://github.com/smeinscher/STRL.git
    ```
    </br>OR in CLion:</br></br>
    File->New->Project From Version Control and put above URL in
    </br></br>
2. ???
3. Profit

Will finish build instructions on future releases.

<!-- USAGE EXAMPLES -->
## Usage

_TBD_

## Current Roadmap

- [x] Create basic Pong game
- [x] Make STRL publicly available
    - [x] LICENSE stuff
    - [x] Fill in initial README.md
    - [x] Make repository public
- [ ] Create unit tests
  - [ ] Research/finish tutorials on testing with C++
  - [ ] Create initial tests
- [ ] Determine features to be added
  - [ ] Brainstorm/research
  - [ ] Finish filling out roadmap



<!-- CONTRIBUTING -->
## Contributing

Currently, I'd like to maintain this project myself. I am open to and appreciate suggestions though!

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

## Contact

Sterling Meinscher - sterling@meinscher.com

Project Link: [https://github.com/smeinscher/STRL](https://github.com/smeinscher/STRL)

## Acknowledgments

Here are some useful resources I've used:

* [learnopengl.com](https://learnopengl.com/)
* [kenney.nl (free game assets)](https://kenney.nl/)
* [Best-README-template](https://github.com/othneildrew/Best-README-Template)
