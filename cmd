g++ -std=c++17 -Wall -Wextra -pedantic -g  main.cpp raytracer.cc shapes.cc material.cc vmath.cc lights.cc -lsfml-graphics-s -lfreetype -ljpeg -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32
g++ -std=c++17 main.cpp raytracer.cc shapes.cc vmath.cc lights.cc material.cc -lsfml-graphics-s -lfreetype -ljpeg -lsfml-window-s -lsfml-system-s -lopengl32