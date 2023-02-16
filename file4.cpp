#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <bitset>

int main(int argc, char **argv)
{
    char * mypipe= (char*)"/home/solmaz/Documents/intership c++ code/mypipe"; // Change to your desired pipe name
    const char* text_file = (char*)"/home/solmaz/Documents/intership c++ code/text_file.txt"; 

    // Open the named pipe for reading
    int read_fd = open(mypipe, O_RDONLY);

    if (read_fd == -1)
    {
        perror("Failed to open named pipe");
        return 1;
    }

   // Read the binary data from the named pipe
    char binary_buffer[256];
    ssize_t binary_size = read(read_fd, binary_buffer, 256);

    if (binary_size == -1)
    {
        perror("Failed to read from named pipe");
        close(read_fd);
        return 1;
    }

    // Print the binary data to the console
    std::cout << "Binary data received: ";
    for (int i = 0; i < binary_size; i++)
    {
        std::cout << (binary_buffer[i]) << " ";
    }
    std::cout << std::endl;

    // converting char array to equivalent integer
    std::cout << " the integer value of the binary number is: ";
    std::string binary_string(binary_buffer);    // Convert the char array to a std::string
    std::bitset<8> binary_number(binary_string); // Convert the binary string to a binary number using std::bitset

    std::cout << binary_number.to_ulong();
    std::cout << std::endl;

    // Close the named pipe for reading
    close(read_fd);

    return 0;
}