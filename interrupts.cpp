/**
 *
 * @file interrupts.cpp
 * @author wendingsha
 *
 */

#include "interrupts.hpp"

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    int current_time = 0;
    const int context_save_time = 10;
    const int switch_kernel_time = 1;
    const int find_vector_time = 1;
    const int find_device_time = 1;
    const int load_addr_time = 1;
    const int iret_time = 1;
    const int execute_ISR_time = 40;


    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        if(activity == "CPU"){
            execution += std::to_string(current_time) + "," + std::to_string(duration_intr) + ", CPU executing\n";
            current_time += duration_intr;
        }
        else if (activity == "SYSCALL" || activity == "END_IO"){
            int deviceNum = duration_intr;

            if (deviceNum < 0 || deviceNum >= delays.size() || deviceNum >= vectors.size()){
                execution += std::to_string(current_time) + "," + std::to_string(0) + ", WarningL invalid device number " + std::to_string(deviceNum) + "int trace.txt\n";
                continue;
            }

            auto [exeCute, time_after_exeCute] = intr_boilerplate(current_time, deviceNum, context_save_time, vectors);
            execution += exeCute;
            current_time = time_after_exeCute;

            int reamaining = delays[deviceNum];
            while (reamaining > 0)
            {
                int temp = (reamaining >= execute_ISR_time ) ? execute_ISR_time :reamaining;
                execution += std::to_string(current_time) + "," + std::to_string(temp) + ", execute ISR activity\n";
                current_time += temp;
                reamaining -= temp;

            }


            execution += std::to_string(current_time) + "," + std::to_string(iret_time) + ", IRET\n";
            current_time += iret_time;
            
            execution += std::to_string(current_time) + "," + std::to_string(context_save_time) + ", context restored\n";
            current_time += context_save_time;

            execution += std::to_string(current_time) + ", " + std::to_string(switch_kernel_time) + ", switch to user model\n";
            current_time += switch_kernel_time;

            if (activity == "END_IO"){
                execution += std::to_string(current_time) + ", " + std::to_string(delays[deviceNum]) + ": interrupt\n";

            }
        

        }
        else{
            execution += std::to_string(current_time) + ", 0, Unknown activity: " + activity + "\n";
        }

        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
