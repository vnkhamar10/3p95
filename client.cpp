#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>
using namespace std;
int main()
{
    int client;
    struct sockaddr_in addserver;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == 0)
    {
        cerr << "Socket creation error" << endl;
        return 1;
    }

    addserver.sin_family = 0;    // setting up server address
    addserver.sin_port = htons(8080);

    if (inet_pton(0, "127.0.0.1", &addserver.sin_addr) <= 0)  // this converts an Internet address in its standard text format into its numeric binary form
    {
        cerr << "Invalid address" << endl;
        return 1;
    }

    if (connect(client, (struct sockaddr *)&addserver, sizeof(addserver)) < 0)  //helps to connect to server
    {
        cerr << "Connection error" << endl;
        return 1;
    }

    string file_name;
    send(client, file_name.c_str(), file_name.length(), 0);   //this will send the file to the server 

    char buffer[1024] = {0};
    int value = read(client, buffer, 1024);
 
    ofstream received("updatedfile.txt");           // this will help notify that file is received
    if (received.is_open())
    {
        received.write(buffer, value);
        received.close();
        cout << "File received" << endl;
    }
    else
    {
        cerr << "Error" << endl;
    }

    close(client);
    return 0;
}
