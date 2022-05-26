#!/bin/bash
echo "_____________________________________________________________________"
echo "Here is the average time for message passing (client) data transfer"
gcc time_msg_client.c -o client
chmod +x client
./client
