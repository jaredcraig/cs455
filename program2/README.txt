CS 455 - Fall 2015
Program #2

 Texturing

Dr. Egbert
Due Thursday September 17
(150 Points)

The purpose of this project is to help you learn the basics of texture mapping and how to perform texture mapping in OpenGL

For this program, you will use the crayon and crayon box models that you created in program 1.  You will first need to generate texture coordinates for the vertices of those two objects.  There are several ways you can do this.  Probably the easiest way is to have Maya generate them for you.  Once the texture coordinates have been generated, you need to export your objects, with the texture coordinates, to .obj files.

The second part of this assignment is to parse the .obj files, pull out the pertinent data, and then send that data to OpenGL for rendering.  You will at least need vertex information, normal information, and texture coordinate information.  There may be other data stored in the .obj file that is also useful to you.

The next part of this assignment is to use the scanner in the graphics lab to scan in an image of a crayon box and one crayon label.  (The crayon box and crayon labels will be provided for you in the lab).  Once you have scanned the images and stored them, you will need to read them into OpenGL to be used as the textures on the objects.  

The last piece of the assignment is to map the textures onto the objects then render the texture mapped objects in OpenGL.  The texture mapping should be done so that the crayon and crayon box appear as they would in real life.

To pass-off the program, you will need to email to myself and the TA the following:

1. The source code for your assignment
2. Pictures (screen captures or the like) of your textured crayon and crayon box


