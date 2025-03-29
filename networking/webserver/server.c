#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handleConnection(int client_fd, const char *dir);

int main(int argc, char *argv[]) {
  char *dir = "."; // Default to current dir

  // Parse --dir argument
  if (argc >= 3 && strcmp(argv[1], "--dir") == 0) {
    dir = argv[2];
  }

  // Create socket
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    perror("socket failed");
    return 1;
  }

  // Set up address
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(PORT); // Fixed: 0x901f -> htons(PORT)

  // Bind
  if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind failed");
    close(server_fd);
    return 1;
  }

  // Listen
  if (listen(server_fd, 10) < 0) {
    perror("listen failed");
    close(server_fd);
    return 1;
  }

  printf("Server running on port %d, serving from %s\n", PORT, dir);

  // Accept loop
  while (1) {
    int addrlen = sizeof(addr);
    int client_fd =
        accept(server_fd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);
    if (client_fd < 0) {
      perror("accept failed");
      continue; // Keep server running
    }

    handleConnection(client_fd, dir);
    close(client_fd); // Close after handling
  }

  close(server_fd); // Unreachable—loop is infinite
  return 0;
}

void handleConnection(int client_fd, const char *dir) {
  // Read client request
  char buffer[BUFFER_SIZE] = {0};
  read(client_fd, buffer, BUFFER_SIZE);
  printf("Client request: %s\n", buffer);

  // Build file path (e.g., "./html/index.html")
  char filepath[BUFFER_SIZE];
  snprintf(filepath, BUFFER_SIZE, "%s/index.html", dir);

  // Open file
  FILE *file = fopen(filepath, "r");
  if (!file) {
    char *error =
        "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\nFile not found";
    write(client_fd, error, strlen(error));
    return;
  }

  // Get file size
  fseek(file, 0, SEEK_END);
  long filesize = ftell(file);
  rewind(file);

  // Read file content
  char *content = malloc(filesize + 1);
  if (!content) {
    fclose(file);
    char *error = "HTTP/1.1 500 Internal Server Error\nContent-Type: "
                  "text/plain\n\nMemory error";
    write(client_fd, error, strlen(error));
    return;
  }
  fread(content, 1, filesize, file);
  content[filesize] = '\0'; // Null-terminate
  fclose(file);

  // Build HTTP response
  char header[BUFFER_SIZE];
  snprintf(header, BUFFER_SIZE,
           "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %ld\n\n",
           filesize);

  // Send response: header + content
  write(client_fd, header, strlen(header));
  write(client_fd, content, filesize);

  free(content); // Clean up
}
