# CppBlokus
Projet d'initiation à l'ingénierie logicielle CMI Informatique L1

## to compile on linux you need will need :
* clang c++ compiler
* SFML installed
```
make
./blokus
```

## to compile on windows you need will need :
* [MinGW Builds 6.1.0 (64-bit)]( https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/6.1.0/threads-posix/seh/x86_64-6.1.0-release-posix-seh-rt_v5-rev0.7z/download)

* [sfml](https://www.sfml-dev.org/index.php) files are included

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
or use the .bat file
