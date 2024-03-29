# Versioning Common Codebase Project / Versioning Coding Cooperation Project
# VCCProject-VCCModuleDLL


## Assumption
All platform (Window, Linux, MacOS).
Already install VSCode, debugger, g++, googletest.

## Usage
To config, follow command in Makefile.
Change dll name in dynamic_library_test.cpp.
Remove first layer README and LICENCE. But should not remove LICENCE under External folder. May use other copyleft resources.

#### Note
As c++ are upgrading since c++17 and avoid too many versions. VCCModule default version is c++29 (or the version that c++ upgrade completed). VCCModule will force update if g++ support new version.

#### Pending: Full Review
Review Exception
Review Class
Review Enum

#### Status:
-	Active: Keep changing. Not recommend to use.
-	Stable: Workable.
-	Inactive: Will not update in the future.
-	Pending: Coming soon.

### Core:
-	Helper (Stable)
-	Thread Safe Class (Stable)
-	Exception (Stable)
-	Log Service (Stable)
-   Command Service (Stable)
-   Process Service (Stable)
-	Action Manager (Stable)
-	Property Accessor (Pending)
### Common:
-   Git (Actives)
### Module:
-	TextEditor (Pending)
-	Document (Pending)
-	Speedsheet (Pending)
### UI:
-	LoginService (Pending)
-	LicenseService (Pending)
-	PaymentService (Pending)

### Update
When update, drop all External/vcc folders then download the latest one.

### Optional
-	Filter out *.o: File > Preferences > Setting => Files: Exclude => Add **/**.o
-	Remove unittest/External to skip running unit test of VCCModule.

## Release Log

### 2023-12-06 Change Project and MakeFile to CPP Complex Mode

### 2023-10-15 Project Name
-	Add long project name

### 2023-03-05 Process, Git
-	Process
-   Git init

### 2023-02-25 Command
-	Command

### 2023-02-24 Class
-	Thread Safe Class

### 2023-02-19 Exception
-	Exception

### 2023-02-16 First Release
-	Initializtion
-	LogService
-	ActionManager
