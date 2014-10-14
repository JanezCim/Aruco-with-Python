Aruco-with-Python
=================

I made this so Aruco library can be used with Python

The whole process has been tesed on Ubuntu.

Quick example setup:

	1.Tutorial on how to setup python:
		https://www.preney.ca/paul/archives/107

		Follow the whole procedure thuraly, otherwise it will not work!


	2.Delete the "build" file, because it's compiled for my computer and build a new one with "mkdir build".

	3.then:
		cd build
		cmake ..
		make

	4.Finally paste the Py.py file into new "build" file and run the example.


	NOTE: "aruco_simple.cpp" is there just as copy from original "aruco-1.2.5" file to help with the functions from 		Aruco library.


######################################################################################################
If you tend to change the project files you have to edit the CMakeLists.txt file so it fits the specifications of your Project. (Path of Python file, name of project folder,...) More details about this can be seen on the Tutorial link above.



TODO:
-Right now python is just starting and ending the program. It will have to extract the location data and use it in future projects.