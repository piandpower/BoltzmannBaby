#include <iostream>
#include <vector>

using namespace std;

struct RBM
{
	unsigned num_v;
	unsigned num_h;

	unsigned avg_v;
	unsigned avg_h;
	
	float error;
	float s;
	float f;

	vector< vector<float> > W;
	vector< vector<float> > dW;
	vector< vector<float> > dW_last;
	

	vector< float > V;	//Output Values of visible layer 	(v_data)
	vector< float > H;	//Output Values of hidden layer  	(h_data)

        vector< float > Vp;	//Output probabilities of visible neurons in layer	(p_model)
        vector< float > Hp;	//Output probabilities of hidden neurons in layer	(q_model)

        vector< float > Vs;	//Sample-based reconstruction of visible layer		(v_model)
        vector< float > Hs;	//Sample-based reconstruction of hidden layer		(h_model)

	vector< float > biasV;
	vector< float > biasH;	

	vector< float > res;	//Residuals of inputs vs targets

	
};


class DeepNet
{

public:

	typedef vector< vector<int> > Matrix;

	DeepNet();

	vector<RBM> Chain;

	vector<vector<float>> ACCUM_GRAD;							//Matrix for summing all RBM's gradient contributions

	float NUM_SAMPLES;
	float NUM_EPOCHS;
	float F;
	float S;
	float RATE;										//Learning rate
	float TIME;										//Actual time (or individual sample #)
	float ERROR;										//Accumulated error from each RBM as we go down the chai
	float TERROR;
	float DEPTH;
	float ITERATION;									//the sample number (which iteration of the batch we're on)
	float BATCH;

	void InitRBM(RBM &myRBM, unsigned num_v_neurons, unsigned num_h_neurons);		//inits 2-layer neural net of given topology

	void BuildChain(RBM myRBM);		 						//builds chain of RBMs with selected number of neurons in each layer
	
	void FeedForwardVisible(RBM &myRBM, vector<float> inputVals, vector<float> dataVp);	//set output values of hidden layer given visible
	
	void FeedForwardHidden(RBM &myRBM, vector<float> inputHiddens, vector<float> dataHp);	//set output values of visible layer given hidden

	void StochasticGradientDecent(RBM &myRBM, vector<float> targetVals, bool OUTPUT_LAYER);	//Calculate Gradient based on targetVals, update weights

	void GetError(vector<float> outputVals, vector<float> targetVals, float &avg_error);

	void GetVisibleSample(RBM &myRBM);

	void GetHiddenSample(RBM &myRBM);

	void UpdateBias(RBM &myRBM, RBM dataRBM);						//Update visible and hidden bias neurons

	void WeightGradient(RBM &modelRBM, RBM dataRBM, float &dwavg);				//Calculate a single RBM's contribution to the gradient

	void ResetGradient(RBM &modelRBM);
	
	void NormalizeWeights(RBM &modelRBM);

	void NormalizeGradient(RBM &modelRBM);

	void Stats(RBM &m);

	void getOutputs(RBM &myRMB);			 					//Update output and prob value arrays, set Vs and Hs sample arrays for next layer

	void UpdateWeights(RBM &sampleRBM, RBM myRBM, float &norm, float K_MAX, bool OUTPUT_LAYER);	

	void Backprop(RBM &modelRBM, vector<float> inputVals, vector<float> targetVals);

	void SetupInputs(string f, unsigned num_f_bins, unsigned num_t_bins, Matrix &visible);

	void SampleToString(Matrix Map, int num_f_bins, int num_t_bins);

	void FillStringVector(string Filename, vector<string> &Book, int num_t_bins);

	void NormalizeLayer(vector<float> &layer);
	

	












};
