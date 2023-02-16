#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  char *mypipe = (char *)"/home/solmaz/Documents/intership c++ code/IPC_Binary2/mypipe"; 
  int ret = mkfifo(mypipe, 0666);

  // Get binary input from the user
  std::string binary;
  std::cout << "Enter a binary number: ";
  std::cin >> binary;

  // Convert the binary string to a binary buffer
  size_t binary_size = binary.size();
  char binary_buffer[binary_size + 1];
  std::strcpy(binary_buffer, binary.c_str());

  // Open the named pipe for writing
  int write_fd = open(mypipe, O_WRONLY);

  if (write_fd == -1)
  {
    perror("Failed to open named pipe");
    return 1;
  }

  // Write the binary buffer to the named pipe
  write(write_fd, binary_buffer, binary_size + 1);

  // Close the named pipe for writing
  close(write_fd);

  return 0;
}