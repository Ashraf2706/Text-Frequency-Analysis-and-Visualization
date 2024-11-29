#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar(){
    m_fileName = "test.txt"; // set default filename
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename){
    m_fileName = filename; // set filename to input argument
    m_data = new LL<string>; // dynamically allocate m_data
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar (){
    delete m_data; // deallocate m_data
    m_data = nullptr;
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start(){
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    //m_data->Display(); //Display the sorted data(for testing purposes)
    DisplayBars();
    Export();
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile(){
    ifstream myfile(m_fileName);
    if(!myfile){
        cout << "Error: Failed to open file " << m_fileName << endl;
        return; 
    }
    int count = 0;
    string word;
    //Read each word from the file then remove punctuations and then 
    //insert the word into m_data
    while(myfile >> word){
        RemovePunct(word);
        m_data->Insert(word);
        count++;
    }
    cout << count << " loaded" << endl;
    myfile.close(); //Close file
}

// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& word){
    //Convert the string to lowercase
    for(long unsigned int i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
    }

    //Remove punctuation from beginning of string
    while(word.length() > 0 && ispunct(word[0])){
        word.erase(0, 1);
    }

    //Remove punctuation from the end of the string
    while(word.length() > 0 && ispunct(word[word.length() - 1])){
        word.erase(word.length()-1, 1);
    }
}

// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon(){
    string input;
    cout << "Would you like to remove all common words (Only use with essays)?" << endl;
    cin >>  input;
    if(input == "yes"){
        //Iterate through m_data backwards to avoid issues with index shifting during removal
        for(int i = (m_data->GetSize()-1); i >= 0; i--){
            //Check if word is in EXCLUDE_LIST
            if((*m_data)[i].first == EXCLUDE_LIST[i]){
                //remove the word from m_data
                m_data->RemoveAt((*m_data)[i].first);
            }
        }
        cout << "All common words removed" << endl;
    }else{
        return;
    }
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles(){
    int count = 0;
    string response;
    cout << "Would you like to remove all words with a frequency of 1?" << endl;
    cin >> response;
    if(response == "yes"){
        //Iterate through m_data backwards to avoid issues with index shifting during removal
        for(int i = (m_data->GetSize()-1); i >= 0; i--){
            //Check if word has a frequency of 1
            if((*m_data)[i].second == 1){
                //remove the word from m_data
                m_data->RemoveAt((*m_data)[i].first);
                count++;
            }
        }
        cout << count << " words removed" << endl;

    }else{
        return;
    }
}

// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData(){
    //Create a map to store each word and its frequency
    map<string, int> freqMap;
    //Iterate through m_data and insert each word and its frequency into freqMap
    for(int i = 0; i < m_data->GetSize(); i++){
        string word = (*m_data)[i].first;
        freqMap[word] = (*m_data)[i].second;
    }
    //Iterate through freqMap and insert each pair into m_dataSorted with the frequency as the key
    for(map<string, int>::iterator pair = freqMap.begin(); pair != freqMap.end(); pair++){
        string word = pair->first;
        int freq = pair->second;
        m_dataSorted.insert(make_pair(freq, word));
    }
}

// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars(){
    //Get reverse iterator for m_dataSorted
    multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin();
    //Iterate through m_dataSorted and display bar chart for each item
    while(it != m_dataSorted.rend()){
        string word = it->second;
        int freq = it->first;
        //Display word and its frequency and a bar chart for word frequency
        cout << setw(15) << left << word << ": ";
        for(int i = 0; i < freq; i++){
            cout << "*";
        }
        cout << endl;
        it++;// Move iterator to next item
    }
}

// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export(){
    string filename;
    cout << "What would you like to call the export file?" << endl;
    cin >> filename;

    ofstream outfile(filename);
    if(!outfile){
        cout << "Error: could not open file " << filename << "for writing" << endl;
        return;
    }
    //Get reverse iterator for m_dataSorted
    multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin();
    //Iterate through m_dataSorted and export bar chart for each item to file
    while(it != m_dataSorted.rend()){
        string word = it->second;
        int freq = it->first;
        //Export word and its frequency to file and bar char for word frequency to file
        outfile << setw(15) << left << word << ": ";
        for(int i = 0; i < freq; i++){
            outfile << "*";
        }
        outfile << endl;
        it++; //Move iterator to next item
    }
    
    outfile.close(); //Close file
    cout << "Output to exportFile " << filename << endl;
}
