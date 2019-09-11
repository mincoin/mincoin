### QoS (Quality of service) ###

This is a Linux bash script that will set up tc to limit the outgoing bandwidth for connections to the Mincoin network. It limits outbound TCP traffic with a source or destination port of 9334, but not if the destination IP is within a LAN.

This means one can have an always-on mincoind instance running, and another local mincoind/mincoin-qt instance which connects to this node and receives blocks from it.
