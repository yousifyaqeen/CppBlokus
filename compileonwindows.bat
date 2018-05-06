rm -r build
mkdir build
g++ -Wall -g -Wno-deprecated-declarations -I%cd%\include -c "%cd%\blokus.cc" -o build\blokus.o 
g++ -L%cd%\include\lib -o "build\blokus.exe" build\blokus.o   -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
copy  %cd%\include\bin\*.dll %cd%\build
mkdir %cd%\build\res
xcopy /E %cd%\res %cd%\build\res
cd %cd%\build
rm blokus.o
blokus.exe
