# Assignment1_Part2_code
A simple simulator demonstrates the switching of user mode to kernel mode.

Code was run in an ubuntu window using WSL.

Navigate to the root folder location on your system, then run the following commands through WSL (ubuntu)

Tools setup:

sudo apt update
sudo apt install -y g++ dos2unix

then run:

1. dos2unix build.sh
2. chmod +x build.sh
3. ./build.sh
4. ./bin/interrupts input_files/trace.txt input_files/vector_table.txt input_files/device_table.txt

you can now view the execution.txt file in "output_files" folder


