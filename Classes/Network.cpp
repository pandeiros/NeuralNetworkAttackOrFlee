#include"Network.h"

Network::Network () {
	layers.push_back (new Layer (3, 1));
	layers.push_back (new Layer (5, 3));
	layers.push_back (new Layer (1, 5));
    Neuron::setParameters (0.1, 1.5, 0.05);
}

Network::~Network() {
}

bool Network::shouldIStayOrShouldIGo (int hp, int enemies, int distance) {
	float hapek, enem, dist;
	hapek = hp / 100.f;
	enem = enemies / 10.f;
	dist = distance / 1000.f;

	layers [0]->setOutput (hapek,enem,dist);

	for (unsigned int i = 1; i < layers.size () - 1; ++i) {
		layers [i]->commandToCalculate (*layers[i - 1]);
	}
	layers[layers.size () - 1]->calculateOutput (*layers[layers.size () - 2]);
	

	float result = layers [layers.size () - 1]->getOutput ();

	if (result > 0)
		return true;
	else
		return false;
}

void Network::learn (bool attackOrNotToAttack) {
	

	// PART 1 - INSTRUCTOR AND ERROR PROPAGATION
	if (attackOrNotToAttack)
		layers [layers.size () - 1]->outputLayerError (2.0f);
	else
		layers [layers.size () - 1]->outputLayerError (-2.0f);

	for (unsigned int i = layers.size () - 2; i >= 1; --i) {
		layers [i]->calculateErrors (*layers [i + 1]);
	}


	// PART 2 - WEIGHT CORRECTION

	for (unsigned int i = 1; i < layers.size (); ++i) {
		layers [i]->correctWeights (*layers [i - 1]);
	}
}