#include "client/socket.h"

#include <stdio.h>

Socket::Socket(Context *context, int port, std::string hostname) : context(context), Number(0) {
    // Connect to the server
    Connected = (socket.Connect(port, hostname) == sf::Socket::Done);
    
    socket.SetBlocking(false);
}

Socket::Socket(Context *context, sf::SocketTCP socket) : context(context), socket(socket), Number(0) {
    socket.SetBlocking(false);
}

void Socket::DoStep() {
    sf::Packet In;
    
    while (socket.Receive(In) == sf::Socket::Done) {
        std::string command;
        In >> command;
        
        if (command == "First, I have to let you in on this secret.")
            In >> context->world->ChunkSize;
        else if (command == "Take this chunk. It will be useful in times of need.")
            context->world->LoadChunk(In);
        else if (command == "Take a number") {
            In >> Number;
            Players[Number] = *context->player;
        } else if (command == "Player wants to move") {
            int who;
            In >> who;
            Player player = Players[who];
            In >> &player; // TODO: yea I had no idea what I was doing there...
        } else
            printf("Got strange packet: %s\n", command.c_str());
    }

    if ((context->player->Dirty && (updateTimer.GetElapsedTime() > 0.5f))
     || (updateTimer.GetElapsedTime() > 5.f)) {
        sf::Packet Out;
        Out << "Move me or ELSE!" << context->player;
        socket.Send(Out);
        
        context->player->Dirty = false;
        updateTimer.Reset();
    }
}

void Socket::Close() {
    socket.Close();
}
