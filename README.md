# Versioning Common Codebase Module (VCCModule)
### Versioning Common Codebase Project
It is member of Versioning Common Codebase Project.
All platform (Window, Linux, MacOS, Andriod, IOS).

Note: Still in initialize version, will have full review when official release
Note: Don't use XMLReader, it will be combined with Builder and rename to XMLBuilder later

## Introduction
When starting a new project, it is time consuming to create basic structure. In fact, all projects have similar structure and lots of similar functions. And rewrite codebase is time consuming. Versioning Common Codebase Project is raised to extract common factor to enhance development efficience.

## Pre-Requirement
1. git
2. g++
3. make
4. gtest

## Usage
Please use following project to create and update project.
VCCProjectGenerator (https://github.com/s1155003185/VCCProjectGenerator)
VCCProjectGeneratorVSCodeExtension (https://github.com/s1155003185/VCCProjectGeneratorVSCodeExtension)

## Note
As c++ are upgrading since c++17 and avoid too many versions. VCCModule default version is c++29 (or the version that c++ upgrade completed). VCCModule will force update if g++ support new version.

****
## Feature
### Status:
-	Active: Keep changing. Not recommend to use.
-	Stable: Workable.
-	Inactive: Will not update in the future.
-	Pending: Coming soon.

### Core:
-	Action Manager (Pending)
-	Exception (Stable)
-	Helper (Stable, Keep update)
-	Log Service (Stable)
-   Process Service (Stable)
-	Property Accessor (Pending)
-   Terminal Service (Stable)
-   XML (Pending)
### Common:
-   Git (Actives, basic function only)
### Module:
-	TextEditor (Pending)
-	Document (Pending)
-	Speedsheet (Pending)
### UI:
-	LoginService (Pending)
-	LicenseService (Pending)
-	PaymentService (Pending)

****
## Update
When update, drop all External/VCC folders then replace by the latest one.

## Optional
-	Filter out *.o: File > Preferences > Setting => Files: Exclude => Add **/**.o
-	Remove unittest/External to skip running unit test of VCCModule.

## Build C++ project
Follow the instruction listed in Makefile

when compile enter following command in terminal:
To build debug
```
make debug -j10
```

To build release
```
make release -j10
```

Debug program is built in bin/Debug
Release program is built in bin/Release

## Execute C++ project in VScode
F5

## Contact
X(Twitter) @VCCProject

## Release Log

### 2024-05-05 First Release: v0.0.1

### 2023-02-16 Initialize
-	Initializtion
-	LogService
-	ActionManager
