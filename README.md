Steganografia
Project Description

Steganografia is a C++ application for hiding and extracting information within image files. The project demonstrates steganography techniques—concealing data so that it is invisible to outsiders but can be retrieved by authorized users.
Features

    Hide text or binary data inside images (e.g., BMP, PNG)

    Extract hidden information from image files

    Support for BMP and PNG formats (see sample files: imprisoned.bmp, pineapple_stare.png)

    Simple command-line interface

    Error detection and handling during hiding and extraction

How Does It Work?

    Hiding Data
    The program modifies the least significant bits (LSB) of image pixels to encode the selected text or file. These changes are virtually invisible to the human eye, so the image looks almost identical to the original.

    Extracting Data
    The program reads the modified bits from the image and reconstructs the hidden message or file.

Project Structure

    main.cpp – main application entry point

    Engine.cpp / Engine.h – logic for data hiding and extraction

    BitTool.cpp / BitTool.h – bitwise operations

    Errors.cpp / Errors.h – error handling

    help.cpp / help.h – help and usage information

    Sample images: imprisoned.bmp, pineapple_stare.png

Requirements

    C++ compiler (e.g., g++)

    CMake for building the project

Usage Example (bash)


    # Build the project
    cmake .
    make

    # Hide a message in an image
    ./steganografia hide input.bmp output.bmp "Secret message"

    # Reveal a message from an image
    ./steganografia reveal output.bmp

Use Cases

    Securely transmitting confidential information

    Intellectual property protection

    Securing communications

Author

Jakub Rawski
