#!/bin/bash
echo "___________________________________________________________________"
echo "Here is the average time for message passing (server) data transfer"
gcc time_msg_server.c -o server
chmod +x server
./server
