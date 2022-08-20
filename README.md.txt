30_Second_Test:
	This test just uses one arduino to trigger interrupts every 2 seconds for a 30 second duration.
	Another arduino receives these inturrpts and will transmit a LoRa packet.

Precise_Offset:
	Experiment requires three nodes, the sync_main node will periodically trigger an interrupt
	on the two sync_nodes. One node needs an offset of 0uS while the other node can have an incr, and
	offset value set to any number of uSeconds of offset desired.

Random_Network:
	Same setup as Random_Offset experiment, but nodes now will follow a poisson distribution without
	a beacon between each transmission. This will most similarly demonstrate an open network with truly
	random traffic.

Random_Offset:
	Experiment requires N-Nodes and one beacon node. A beacon will periodically trigger all nodes
	to transmit a message. Each node will have a dedicated ID, and this ID will seed a random offset
	to within one message length. This uniformly distributed, random offset will force random colisions
	between the N nodes.