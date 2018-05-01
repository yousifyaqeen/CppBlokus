rm -r build
mkdir build
g++ -Wall -g  -I%cd%\include -c "%cd%\blokus.cc" -o build\blokus.o 2> compiling_error.txt
findstr "^" "compiling_error.txt" || del "compiling_error.txt"
g++ -L%cd%\include\lib -o "build\blokus.exe" build\blokus.o   -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
copy  %cd%\include\bin\*.dll %cd%\build
mkdir %cd%\build\res
xcopy /E %cd%\res %cd%\build\res
cd %cd%\build
blokus.exe
