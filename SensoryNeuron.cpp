#include "SensoryNeuron.h"

nervous::SensoryNeuron::SensoryNeuron(Axon * _rhsAxon, Synapse * _rhsSynapse, Dentrity * _rhsDentrity, Stimulis stimulis):
	Neuron(_rhsAxon, _rhsSynapse, _rhsDentrity)
{
	Signal signal;

	_stimulis = stimulis;

	//Inform the neuron statistics before contact
	PresentNeuronStats(new NeuronInformation(signal));
}

nervous::SensoryNeuron::~SensoryNeuron()
{
	delete _axon;
	_axon = NULL;
	delete _dentrity;
	_dentrity = NULL;
	delete _synapse;
	_synapse = NULL;

	_stimulis = NONE;
}


void nervous::SensoryNeuron::Receive(SensoryNeuron * _receiveNeuron, Axon * _receiveAxon, Synapse * _receiveSynapse, Dentrity * _receiveDentrity, NeuronInformation * _neuronInfo)
{
	// When receives contact from another neuron
	if (_receiveNeuron->hasBeenSynapticExcited)
	{
		_axon = _receiveAxon;
		_synapse = _receiveSynapse;
		_dentrity = _receiveDentrity;

		_neuronInfo->Print(RECEIVINGFROM + _receiveNeuron->_name);

		// calculate neuron releases
		CalculateNeuroTRP();

		// calculate conductange change in the sensory nervous
		CalculatePostSynapticConductance();

		// Process the modulation of neurons transmission and reads its stimulis
		Process(_neuronModulator, _pulse, nervous::SensoryNeuron::ReactToStimulis(this));
	}
	else
		return;
}

void nervous::SensoryNeuron::Process(NeuronModulator * neuronModulator, Pulse * pulse, Stimulis stimulis)
{
	neuronModulator->Modulate();

	_stimulis = stimulis;
}

void nervous::SensoryNeuron::Transmit(SensoryNeuron * _destNeuron, Axon * _destAxon, Synapse * _destSynapse, Dentrity * _destDentrity, NeuronInformation * _neuronInfo)
{
	if (this->hasBeenSynapticInhibited && _destNeuron->hasBeenSynapticExcited)
	{
		_neuronInfo->Print(TRANSMITINGTO + _destNeuron->_name);

		CalculatePostSynapticConductance();
	}
	else
		return;
}

nervous::Stimulis nervous::SensoryNeuron::ReactToStimulis(SensoryNeuron * _rhsSensoryNeuron)
{
	return _rhsSensoryNeuron->_voltage / this->_reversalVoltage == 0 ? _stimulis = SMELL: _stimulis = LIGHT;
}