# cmake
Basic cmake project for a c++ application

----------------
Lets understand make first!
----------------
* make is a build automation tool.
* It reads instructions from a file called Makefile, which defines how to compile and link the program.
* You tell it how to build each part (e.g., compile main.c into main.o, then link main.o into an executable).
* eg. Makefile

```make
app: main.o utils.o
	gcc main.o utils.o -o app

main.o: main.c
	gcc -c main.c

utils.o: utils.c
	gcc -c utils.c
```
----------------
Explaination of Makefile
----------------
✅ Line 1: ```app: main.o utils.o```
This is a target rule.
app is the target — usually an executable or final output.
main.o and utils.o are the dependencies — files required to build app.
Meaning: "To build app, you first need main.o and utils.o."

✅ Line 2: ```gcc main.o utils.o -o app```
This is the command to build the target.
Runs only if main.o or utils.o is newer than app (i.e., modified).
This uses gcc to link the object files into an executable named app.

✅ Line 3: ```main.o: main.c```
Another target rule.
main.o depends on main.c.
Meaning: "To build main.o, you need main.c."

✅ Line 4: ```gcc -c main.c```
Compiles main.c into main.o (object file).
-c flag tells gcc to compile only (no linking).

same for utils.c

----------------
How to execute make
----------------
* ```make``` command finds default flename Makefile and runs to generate target
* for custom filename: ```make -f BuildRules.mk```

----------------
Now, Why CMake is better? 
----------------
* You don’t need to manually manage dependencies and file lists — CMake does it for you.
* Cross-platform support
* Automatic dependency handling- make requires you to manually list dependencies. CMake can use ```target_include_directories```, ```target_link_libraries```, and more — no need to repeat file paths everywhere.
* CMake supports out-of-source builds — keeps your source and build files separate.
* Easy to manage subdirectories, libraries, and modules.

----------------
Simple cmake code
----------------
``` CMakeLists.txt
cmake_minimum_required(VERSION 3.10)  # Minimum CMake version

project(MyApp)  # Project name

# Add executable from source files
add_executable(app main.c utils.c)
```

* Commands to build
```
mkdir build
cd build
cmake ..
make
```
----------------
✅ What Each Line Does
----------------
```cmake_minimum_required(VERSION 3.10)```: Ensures a minimum version of CMake is used.
```project(MyApp)```: Names your project.
```add_executable(app main.c utils.c)```: Tells CMake to compile these files into an executable called app.
* Optional
```
include_directories(include)       # Add include path
add_compile_options(-Wall -O2)     # Enable warnings and optimization
```

* ```cmake ..``` -
    Generates build files (like Makefile) from CMakeLists.txt
*  ```make``` -
    Uses that Makefile to compile and link your code

Note- cmake .. does not always generate Makefile. The default is Makefile but you can specify with ```-G``` flag
```cmake -G "Ninja" ..``` or
```cmake -G "Visual Studio 17 2022" ..```

----------------
For a simple project with head files, cpp source files and build executable; see the code section after this point!

----------------
Execution Commands
----------------
* ```cd build```
* ```cmake ..```
* ```make```
In terminal 1
* ```./server```
In terminal 2
* ```./client```