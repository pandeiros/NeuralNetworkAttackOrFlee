//layer class

#ifndef NETWORK
#define NETWORK

#include"Layer.h"
#include<vector>


class Network {
public:
	Network ();
	~Network ();

	bool shouldIStayOrShouldIGo (int hp, int enemies, int distance);
	void learn (bool wasItAGoodDecision);

private:
	std::vector < Layer* > layers;

};

#endif