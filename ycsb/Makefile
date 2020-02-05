all: ycsb ycsb_throughput ycsb_graph ycsb_nn
SEASTAR = ../seastar
ycsb_throughput : ycsb_throughput.cc
	c++ -std=c++14 -o ycsb_throughput `pkg-config --cflags --libs $(SEASTAR)/build/release/seastar.pc` ycsb_throughput.cc
ycsb: ycsb.cc
	c++ -std=c++14 -o ycsb `pkg-config --cflags --libs $(SEASTAR)/build/release/seastar.pc` ycsb.cc
ycsb_graph: ycsb_graph.cc
	c++ -std=c++14 -o ycsb_graph `pkg-config --cflags --libs $(SEASTAR)/build/release/seastar.pc` ycsb_graph.cc
ycsb_nn: ycsb_nn.cc
	c++ -std=c++14 -o ycsb_nn `pkg-config --cflags --libs $(SEASTAR)/build/release/seastar.pc` ycsb_nn.cc

.PHONY: clean

clean:
	rm -f *.o 
