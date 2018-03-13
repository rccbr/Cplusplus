#ifndef SENSORYNEURONS_H

#include "Neuron.h"

namespace nervous
{
	enum Stimulis
	{
		NONE,
		SMELL,
		LIGHT,
		SOUND,
		TASTE,
		SIGHT
	};

	class SensoryNeuron;

	typedef Stimulis (SensoryResponse)(SensoryNeuron *);

	class SensoryNeuron : Neuron
	{
	protected:

		Stimulis _stimulis;

	private:

		// string constants
		const string RECEIVINGFROM = "Sensory neuron receiving from ";
		const string TRANSMITINGTO = " Sensory neuron transmiting to ";

	public:
		SensoryNeuron(Axon * _rhsAxon, Synapse * _rhsSynapse, Dentrity * _rhsDentrity, Stimulis stimulis);
		~SensoryNeuron();

		void Receive(SensoryNeuron * _receiveNeuron, Axon * _receiveAxon, Synapse * _receiveSynapse, Dentrity * _receiveDentrity, NeuronInformation * _neuronInfo);

		void Process(NeuronModulator * neuronModulator, Pulse * pulse, Stimulis stimulis);

		void Transmit(SensoryNeuron * _destNeuron, Axon * _destAxon, Synapse * _destSynapse, Dentrity * _destDentrity, NeuronInformation * _neuronInfo);

		Stimulis ReactToStimulis(SensoryNeuron * _rhsSensoryNeuron);
	};
}

#endif SENSORYNEURONS_H
