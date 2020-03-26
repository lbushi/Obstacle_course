# Obstacle_course

Obstacle_course(bad name i know) is a simple 3D game created using the OpenGL Graphics API written in C++ with the exception of some external code written in C. 

The game is simple; you are given control of a cube in the beginning of a straight road populated with obstacles and you have to overcome these obstacles either by moving left or right which you can do respectively by pressing A/D buttons or jumping up with the W button. If you hit an obstacle and you have collected no orbs(more on these later) then the game ends. 

Orbs are like power ups which can be collected and each orb gives you an extra life. For example, when you have 3 orbs then you are allowed to hit obstacles 3 times and then the 4-th one will end the game. 

Obstacles are visually represented as rectangles with varying widths and heights and orbs are represented as bipyramids with flashing colours.

The game can be paused with the P button.

In order to get the code running on your setup, you must first set up GLAD to get the function pointers that will ultimately instruct the GPU to draw stuff on the screen and you will need to set up GLFW library to create a window. Then simply put the header files that appear in my code in the include  directories of the project and also make sure to include glfw3.lib(found in the zip folder when you download GLFW) and include opengl32.lib(should be already in your computer). Finally, download the glm math library and set the corresponding include directories and .lib files to finish everything.  If you cant set it up, you might want to check out LearnOpenGL.com website which has probably the best tutorials on OpenGL out there and you can also find how to set up the project properly with GLAD, GLFW and glm.
