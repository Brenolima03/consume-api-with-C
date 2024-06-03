# About
This is a C program that serves as a client for interacting with a RESTful API. It utilizes the libcurl library for making HTTP requests.

## Prerequisites
Before using this program, ensure that you have the following prerequisites installed on your system:

- **gcc**: The GNU Compiler Collection, required for compiling the C code.
- **libcurl**: A library for transferring data with URLs, used for making HTTP requests. You need both the library and its development files.

Go to the official website and download the suitable version for you: https://curl.se/download.html.
Search for libcurl-x64.dll in the curl/ directories or download them if they're not there and copy or move them to the root directory of the project.

## Installation
1. Clone this repository to your local machine:
git clone git@github.com:Brenolima03/consume-api-with-C.git

2. Navigate to the project directory:
cd consume-api-with-C

3. Compile the C program using gcc. Replace `"curl/include"` and `"curl/lib"` with the paths to your libcurl installation:
gcc -o main main.c -I"curl/include" -L"curl/lib" -lcurl

## Usage
Once the program is compiled, you can execute it using the following command:
./main (or .\main.exe on Windows)

## Configuration
The program reads configuration from a `.env` file. Ensure that you have a `.env` file in the same directory as the executable with the following format:

URL=https://api.example.com/
POST_PAYLOAD={"key": "value"}
PUT_PAYLOAD={"key": "updated_value"}
ID_GET=123
ID_UPDATE=456
ID_DELETE=789

Replace the values with your actual API URL, payload data, and IDs.

## Contributing
If you'd like to contribute to this project, feel free to fork the repository and submit a pull request. Contributions, issues, and feature requests are welcome!
