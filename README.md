Simple game of life simulator made in C++ with "infinitely" expandable grid
The expansiveness of the grid hasn't been thoroughly tested so I'm sure it'll break down at some point.

I wrote this project as a fun way to get back into writing C++.

how to use:
-
Compile with make, then run by typing ./life [path to map file] in the console.   
Map files look for "1" symbols to find live cells. You can pad the "dead" space with whatever you feel like.

Alternatively run with "make run", which will always run "test_map". or "make run MAP="map_name"" to specify a different one

TODO:
-
- First finish another project before coming back to this. :)
- stop using a single class for the entire project (I wanted to interact with C++ features as much as possible, and this was my silly way of doing so).
- make a GUI, and actually do somthing with user inputs.
- memory optimizations, current implementation has a lot of bandaids and shortcuts in it
