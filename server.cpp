#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
int main()
{
    int server, client;
    struct sockaddr_in addserver, addclient;

    server = socket(AF_INET,SOCK_STREAM,0);  //create a socket for server
    if (server == 0)
    {
        cerr << "Can not create server" << endl;
        return 1;
    }

    addserver.sin_family = AF_INET;  // this is to communicate between processes on different hosts connected by IPV4
    addserver.sin_addr.s_addr = 0;
    addserver.sin_port = htons(8080);

    if (bind(server, (struct sockaddr *)&addserver, sizeof(addserver)) < 0)   // to help bind the socket
    {
        cerr << "Binding error" << endl;
        return 1;
    }
  
    listen(server, 5);          // this is to listen for socket
    cout << "Localhost" << endl;

    char buffer[1024] = {0};

    while (true)
    {
        client = accept(server, (struct sockaddr *)&addclient, (socklen_t *)&addclient);  // this is to accept the file in server side
        if (client < 0)
        {
            cerr << "error" << endl;
        }

        int value = read(client, buffer, 1024);
        if (value < 0)
        {
            cerr << "Reading error" << endl;
            close(client);
        }

        string file_name;
        ifstream file(file_name, ios::binary);   // this part will help to open the file
        if (!file.is_open())
        {
            cerr << "Error opening file: " << file_name << endl;
            close(client);
        }

        int size = file.tellg();
        
        char *file_contents = new char[size];
        file.read(file_contents, size);
        file.close();

        cout<<client<<file_contents<<size<<endl;

        delete[] file_contents;
        close(client);
    }

    close(server);
    return 0;
}
