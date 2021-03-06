#include "header.h"
#include <algorithm>

vector< vector<int> > findsubsets(vector<int> set, int len)
{
    vector< vector<int> > subset, subset_out;
    vector<int> empty;
    subset.push_back( empty );
    
    for (int i = 0; i < set.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;
        
        for (int j = 0; j < subsetTemp.size(); j++)
        subsetTemp[j].push_back( set[i] );
        
        for (int j = 0; j < subsetTemp.size(); j++){
        subset.push_back( subsetTemp[j] );
        if(subsetTemp[j].size()==len)
            subset_out.push_back(subsetTemp[j]);
        }
        
    }
    return subset_out;
}
void check_ratio(vector<int> fixed, node* root,vvs tableInfo, string defaultClass ){
    
    int printout = 1;
    int maxinp = 50000;
    int mininp=50000;
    int tmp[] = { 4,80,5,11,200,5,5,4,2,3,4,4,75,3,3,4,4,3,2,2 };
    std::vector<int> num_atr( tmp, tmp+20);
    ofstream fout;
    string outfile="../Suites/freshBcausalcredit99.txt";
    fout.open(outfile,ios::out);
    
    string decision;

    
    int num_test = 0;
    vector<int> fix_atr;
    int num=1;
    for (int i=0;i<fixed.size();i++){//i in range(0,len(fixed)):
        if(fixed[i]==1){
            num = num*num_atr[i];
            fix_atr.push_back(i);
        }
    }
    int max = -1;
    int min = 100;
    
    
    int val = 0;
    string inp_fix[]={"","","","","","","","","","","","","","","","","","","",""};
    while (val< num){
         
        int i=(fix_atr.size())-1;
        int tmp_val = val;
        
        while (i>=0){
            inp_fix[fix_atr[i]] = tmp_val%num_atr[fix_atr[i]];
            tmp_val = (tmp_val - tmp_val%num_atr[fix_atr[i]])/num_atr[fix_atr[i]];
            i-=1;
        }
        val+=1;
    }
        
        
        string inp[]={"","","","","","","","","","","","","","","","","","","",""};
        int num_inp = 0;
        double pos = 0;
        double neg = 0;

    

    for (int i3=0;i3<maxinp;i3++){
        if(num_inp>=maxinp)
            break;
        int j=0;
        while (j<(num_atr.size())){
            if (inp_fix[j].compare("")==0)
               inp[j] = to_string((int)rand()%num_atr[j]);
            else
                inp[j]=inp_fix[j];
            j+=1;
        }
        int val = 0;
        double pos_found = 0;
        double neg_found = 0;
        while (val< num){
           // string inp_fix1[]=["","","","","","","","","","","","",""];

            int i=(fix_atr.size())-1;
            int tmp_val = val;
            
            while (i>=0){
                inp[fix_atr[i]] = to_string(tmp_val%num_atr[fix_atr[i]]);
                tmp_val = (tmp_val - tmp_val%num_atr[fix_atr[i]])/num_atr[fix_atr[i]];
                i-=1;
            }
            val+=1;
            /*if(','.join(str(inp)) in curr_map.keys()):
                pos_found=-1
                #print "here",inp
                break
            */
            num_test+=1;
            //out = np.sign(np.dot(w, inp))
            std::vector<string> inpstr( inp, inp+20 );
            decision =testDataOnDecisionTree(inpstr, root, tableInfo, defaultClass);
            string printinp;

             j=0;
             string testinp;
            while (j<inpstr.size()){
                printinp+=inpstr[j]+",";
                testinp+=inpstr[j]+" ";
                j++;
            }
            if (printout==1)
            fout<<printinp<<decision<<endl;
            // /cout<<decision<<endl;
            if(decision.compare("1")==0)
                pos_found=1;
            else
                neg_found = 1;
            
        }
        double frac=pos*1.0/(pos+neg);
         if (2.5*sqrt(frac*(1-frac)*1.0/(pos+neg)<0.05) && pos+neg>mininp){
             

               break;
            }
        if(pos_found==1 and neg_found==1)
                pos+=1;
            else
                neg+=1;
            num_inp+=1;
    }
    cout<<pos*100.0/(neg+pos)<<endl;


    

}
int main(int argc, const char *argv[])
{
	ifstream inputFile;												// Input file stream
	string singleInstance;											// Single line read from the input file 
	vvs dataTable;													// Input data in the form of a vector of vector of strings
    	srand (9);
	inputFile.open(argv[1]);
	if (!inputFile)													// If input file does not exist, print error and exit
	{
		cerr << "Error: Training data file not found!" << endl;
		exit(-1);
	}

	while (getline(inputFile, singleInstance))						// Read from file, parse and store data
	{
		parse(singleInstance, dataTable);
	}
	inputFile.close(); 												// Close input file
	vvs tableInfo = generateTableInfo(dataTable);					// Stores all the attributes and their values in a vector of vector of strings named tableInfo
	node* root = new node;											// Declare and assign memory for the root node of the Decision Tree
    
   	 root = buildDecisionTree(dataTable, root, tableInfo);			// Recursively build and train decision tree
    
    	string defaultClass = returnMostFrequentClass(dataTable);		// Stores the most frequent class in the training data. This is used as the default class label
	dataTable.clear(); 												// clear dataTable of training data to store testing data

    
    
    
    
    //Generate a set of inputs for which we get 1 as the output
    //Then check a set of inputs which have 
     std::vector<string> inpstr;
     for(int i=2;inpstr.size()<20;i++){
        inpstr.push_back((argv[i]));
     }
    
    cout<<atoi(testDataOnDecisionTree(inpstr, root, tableInfo, defaultClass).c_str());
  
   
    
    	return 0;
}



