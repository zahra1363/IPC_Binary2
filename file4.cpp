#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <bitset>
#include <fstream>

int main(int argc, char **argv)
{
    char *mypipe = (char *)"/home/solmaz/Documents/intership c++ code/IPC_Binary2/mypipe"; // Change to your desired pipe name
    const char *text_file = (char *)"/home/solmaz/Documents/intership c++ code/IPC_Binary2/text_file.txt";

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
    std::cout << "The integer value of the binary number is: ";
    std::string binary_string(binary_buffer);    // Convert the char array to a std::string
    std::bitset<8> binary_number(binary_string); // Convert the binary string to a binary number using std::bitset
    std::cout << binary_number.to_ulong();
    std::cout << std::endl;

    std::cout << "Binary data is writting in the text file ..." << std::endl;
    // Open the file for writing
    std::ofstream outfile;
    outfile.open(text_file);

    // Write the binary to the file
    outfile << binary_buffer;

    // Close the file
    outfile.close();

    // Close the named pipe for reading
    close(read_fd);

    return 0;
}