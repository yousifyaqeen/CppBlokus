# CppBlokus 
Projet d'initiation à l'ingénierie logicielle CMI Informatique L1

![alt text](https://raw.githubusercontent.com/yousifyaqeen/CppBlokus/master/logo.png)

### for more info see the [wiki](https://github.com/yousifyaqeen/CppBlokus/wiki)

## to compile on linux you will need :
* [clang](https://clang.llvm.org/) a c++ compiler
* [sfml](https://www.sfml-dev.org/index.php) installed
```
make
./blokus

```
or you can do it manually if you have another compiler
```
g++ -Wall -g -O2 -std=c++11 -Wno-deprecated-declarations -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
./blokus

```
## to run on windows 

 download build.7z from the release folder 

## to compile on windows you will need :
* this exact version of [MinGW Builds 6.1.0 (64-bit)]( https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/6.1.0/threads-posix/seh/x86_64-6.1.0-release-posix-seh-rt_v5-rev0.7z/download)

unzip the file then add MinGW/bin to paths 
if you have multiple compilers you will have to remove them from paths

* [sfml](https://www.sfml-dev.org/index.php) files are included
## to compile on windows :
* use [compileonwindows](https://raw.githubusercontent.com/yousifyaqeen/CppBlokus/master/compileonwindows.bat)

* to do it manually

```
mkdir build
g++ -Wall -g  -I%cd%\include -c "%cd%\blokus.cc" -o build\blokus.o 2> compiling_error.txt
findstr "^" "compiling_error.txt" || del "compiling_error.txt"
g++ -L%cd%\include\lib -o "build\blokus.exe" build\blokus.o   -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
copy  %cd%\include\bin\*.dll %cd%\build
mkdir %cd%\build\res
xcopy /E %cd%\res %cd%\build\res
cd %cd%\build
blokus.exe

```
