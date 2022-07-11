# ConstellationEngine

![GitHub Repo stars](https://img.shields.io/github/stars/ConstellationGamesOrg/ConstellationEngine?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/ConstellationGamesOrg/ConstellationEngine?style=social)

![GitHub top language](https://img.shields.io/github/languages/top/ConstellationGamesOrg/ConstellationEngine)
![Lines of code](https://img.shields.io/tokei/lines/github/ConstellationGamesOrg/ConstellationEngine)
![GitHub repo size](https://img.shields.io/github/repo-size/ConstellationGamesOrg/ConstellationEngine)

![GitHub issues](https://img.shields.io/github/issues/ConstellationGamesOrg/ConstellationEngine)
![GitHub pull requests](https://img.shields.io/github/issues-pr/ConstellationGamesOrg/ConstellationEngine)
![GitHub](https://img.shields.io/github/license/ConstellationGamesOrg/ConstellationEngine)

![GitHub release (latest by date)](https://img.shields.io/github/v/release/ConstellationGamesOrg/ConstellationEngine)
![GitHub all releases](https://img.shields.io/github/downloads/ConstellationGamesOrg/ConstellationEngine/total)

## About ConstellationEngine
### An extraordinarily performant game engine
The **entire** game engine's features will be able to run on an AMD A6-3420M APU, an **_11 year old_** APU from AMD made for **_entry level laptops_**.

## Compiling
On all supported Operating Systems (OS'), the first step is to **download this repository**

### Linux
Open the folder in which Constellation Engine is on your system in your terminal and run the following commands depending on your distro

If you get a message containing "Y/n :" type in Y and hit enter.

#### Debian
On Debian, if this is your first compile of Constellation Engine run ``make debiandeps`` to install dependencies and ``make linux`` to compile :)

#### Arch (BTW)
On Arch, the installation process is different based off if you're using Wayland or X11. To find out which one you're on, run ``echo $WAYLAND_DISPLAY``. If it outputs nothing, you're on X11. If it outputs something like wayland-0 then you're on Wayland.

If you get a message saying something similar to "Unsupported package - Potentially Dangerous !" don't worry. It's only saying that CGLM is an unsupported package, but nothing bad will happen to your system.

##### Wayland
On Wayland, if this is your first compile of Constellation Engine run ``make archwaylanddeps`` to install dependencies and ``make linux`` to compile :)

##### X11
On X11, if this is your first compile of Constellation Engine run ``make archx11deps`` to install dependencies and ``make linux`` to compile :)

### macOS
Open the folder in which Constellation Engine is on your system in your terminal.

#### With brew
If you have brew installed, and this is your first compile of Constellation Engine, run ``brew install glfw cglm`` and ``make mac`` to compile. Enjoy :)

#### Without brew
If this is your first compile of Constellation Engine and you don't have brew installed, run ``make macdeps`` to install dependencies and ``make mac`` to compile. Enjoy :)

### Windows
#### Visual studio
On Windows with Visual Studio, first install Visual Studio 2022 (if you haven't already), then download this repository, download the thirdparty tools needed to build on windows from the ConstellationGamesOrg github profile and make sure your folder structure looks like so:
```
  Programming Folder
    |
    |-> Constellation Engine
    |   |
    |   |-> (The project files)
    |
    |-> Thirdparty
    |   |
    |   |-> (The thirdparty files)
```
Then go into Constellation Engine and open ConstellationEngine.sln in Visual Studio 2022. :)

### Command Prompt
On Windows without Visual Studio, first download g++ (if you haven't already), download this repository, download the thirdparty tools repository from the ConstellationGamesOrg github profile's "thirdparty" repository and make sure your folder structure looks like so:
```
  Programming Folder
    |
    |-> Constellation Engine
    |   |
    |   |-> (The project files)
    |
    |-> Thirdparty
    |   |
    |   |-> (The thirdparty files)
```
Now, open up the command prompt and type ``make windows``. This will automatically compile + run the engine. Note: If you're wondering where the executable is, it's called ConstellationEngine.exe and lies in the root of the Constellation-Engine folder.

## Bug Reporting
You can report bugs in the [issues tab](https://github.com/ConstellationGamesOrg/ConstellationEngine/issues) in the github repository.

## Contributing
If you want to contribute, you can create a pull request so we can consider your contribution.

Please add your name and/or Github username to [AUTHORS.md](AUTHORS.md) in your pull request.

## Changelog
Please see [CHANGELOG.md](CHANGELOG.md).
