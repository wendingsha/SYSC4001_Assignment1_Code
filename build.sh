
g++ -std=c++17 -Wall -O2 interrupts.cpp -o interrupt


if [ $? -eq 0 ]; then
    echo "Build success, running program..."
    ./interrupt trace.txt vector_table.txt device_table.txt
else
    echo "Build failed!"
fi

