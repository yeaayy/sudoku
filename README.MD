# Sudoku solver
3x3 Sudoku solver with customizable rule and board shape.
## Standard code
### Compiling
To compile it to `build` directory, using `ninja` as build tool:
```sh
mkdir build
cmake -GNinja -B build
ninja -C build
```
### Running
Running the sample:
```sh
./build/sudoku < sample/1.sudoku
```
## Customizing the rule
To customizing the rule simply edit `src/main.cpp`. But if you want to keep it separate just copy `main.cpp` to new file, for exmple `src/custom.cpp`, then rerun the `cmake` with additional variable:
```
cmake -GNinja -B build -DMAIN=src/custom.cpp
```
then rebuild as usual:
```sh
ninja -C build
```
### Code sample with custom rule
For sample look on other branch other than main branch