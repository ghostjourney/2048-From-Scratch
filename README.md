# 2048 From Scratch

#### Graphics From Scratch

## Description

2048 From Scratch is a test bed for write one or more libraries for creating graphical applications and games

## Current Project Structure

The project is split between platform specific code, shared library code, and game code

The platform specific code is located in directories containing the associated platform (E.g. linux specific code is in the linux directory)

## Build Instructions

The project is currently configured to auto detect the operation system and use the appropriate target for the operating system.

### Build MacOS

You must use xcode to build the MacOS target since it currently uses a .xib which is not compiled using unix makefiles

```sh
cmake -G Xcode -B xcode
```

The above command will generate an xcode project located in xcode. Open the project with xcode and compile it.

## Developer Notes

The symlink for compile_commands.json is for a cmake generated file located in the generated build directory. Use the following command
to create it.

```sh
cmake -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```
