# Dev manual (os:windows)

## testing
to test from visual studio
-> run script "TESTING_copy_dlls.bat"
    - this will copy engine dlls and other dependencies 
        to the location of the testing exe
    
    - if the dlls are not copied than the test will fail/not execute by default

## programming/dev
to add new source files
-> run script "DEV_cmake_build.bat"
    - the "build" dir has to be updated everytime a new .cpp file (to be compiled) is added.
        this is done automatically by "DEV_cmake_build.bat"

    - you DONT have to run the script when adding header files (.h / .hpp) ONLY source files

