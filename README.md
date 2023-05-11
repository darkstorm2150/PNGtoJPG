# PNGtoJPG

PNG to JPG Converter aka PNGtoJPG.exe
=====================

This program is a command-line utility designed to convert PNG images to JPG format. It takes advantage of multithreading to process multiple images concurrently, providing faster performance on systems with multiple CPU cores.

Usage
-----

To use the program, open a Command Prompt or terminal window and navigate to the directory containing the executable.

Run the program by typing: <executable_name> <path_to_folder_containing_images>


Replace `<executable_name>` with the name of your compiled executable (e.g., `pngtojpg.exe` or `C++ Project.exe`) and `<path_to_folder_containing_images>` with the full path to the folder containing the PNG images you want to convert.

Example: pngtojpg.exe C:\Users\JohnDoe\Pictures\MyPNGs


This command would convert all PNG images in the `MyPNGs` folder to JPG format, with the output JPG images saved in the same folder as the input PNG images.

Notes
-----

- The program processes up to 8 images concurrently by default.
- The program only converts images with a `.png` file extension.
- The output JPG images will have the same file name as the input PNG images, but with a `.jpg` extension.
- The input PNG images are not modified or deleted during the conversion process.


