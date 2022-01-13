#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include "csvstream.h"
using namespace std;

// class to performan training and testing
class Classifier {
public:
    
  Classifier(bool debugflag = false) : debug(debugflag), numPosts(0) {
  }

  void train(ifstream& file) {
    csvstream csv(file);
    vector<string> head = csv.getheader();
    vector<pair<string, string>> line;
    int tag = find(head, "tag");
    int cont = find(head, "content");
    
    if (debug)
    {
        cout << "training data:" << endl;
    }

    while (csv >> line) {
      string label = line[tag].second;
      if (debug) {
        cout << "  label = " << label << ", content = "
             << line[cont].second << endl;
      }
      numPosts++;
      
      if (lblPosts.find(label) == lblPosts.end()) {
        lblPosts.insert(make_pair(label, 1));
        lwPosts.insert(make_pair(label, map<string, int>()));
      } else {
        ++lblPosts[label];
      }
      
      set<string> words = unique_words(line[cont].second);
      map<string, int>& lblMap = lwPosts[label];
      for (const string& w : words) {
        if (wordPosts.find(w) == wordPosts.end())
          wordPosts.insert(make_pair(w, 1));
        else
          ++wordPosts[w];
        
        if (lblMap.find(w) == lblMap.end())
          lblMap.insert(make_pair(w, 1));
        else
          ++lblMap[w];
      }
    }
    cout << "trained on " << numPosts << " examples" << endl;
    if (debug)
      cout << "vocabulary size = " << wordPosts.size() << endl;
    cout << endl;
    calculate();
  }

  void test(ifstream& file) {
    csvstream csv(file);
    vector<string> head = csv.getheader();
    vector<pair<string, string>> line;
    int tag = find(head, "tag");
    int cont = find(head, "content");
    
    // read line by line
    int numTest = 0;
    int numCorrect = 0;
    cout << "test data:" << endl;
    while (csv >> line) {
      string label = line[tag].second;
      set<string> words = unique_words(line[cont].second);
      numTest++;
      
      string testLbl = "";
      double logLbl = 0;
      for (auto& i : logPrior) {
        double logTemp = calcLog(i.first, i.second, words);
        if (testLbl == "" || logTemp > logLbl) {
          testLbl = i.first;
          logLbl = logTemp;
        }
      }
      
      cout << "  correct = " << label << ", predicted = " << testLbl
           << ", log-probability score = " << logLbl << endl;
      cout << "  content = " << line[cont].second << endl << endl;
      
      if (testLbl == label)
        numCorrect++;
    }
    cout << "performance: " << numCorrect << " / " << numTest
         << " posts predicted correctly" << endl;
  }

private:
  // EFFECTS: find the index of word in the vector
  int find(const vector<string>& line, const string& w) {
    for (int i = 0; i < (int)line.size(); i++) {
      if (line[i] == w)
        return i;
    }
    return -1;
  }
  
  // EFFECTS: Returns a set containing the unique "words" in the original
  //          string, delimited by whitespace.
  set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;

    // Read word by word from the stringstream and insert into the set
    while (source >> word) {
      words.insert(word);
    }
    return words;
  }
  
  // calculate the log
  double calcLog(const string& lbl, double logLbl, set<string>& words) {
    double result = logLbl; // ln(P(C))
    map<string, double>& mapLog = lwLog[lbl];
    for (auto& w : words) {
      // calculate ln(P(w|C))
      auto itlog = mapLog.find(w);
      if (itlog != mapLog.end()) {
        result += itlog->second;
      } else {
        auto it = wordPosts.find(w);
        if (it != wordPosts.end())
          result += log(it->second / (double)numPosts);
        else
          result += log(1 / (double)numPosts);
      }
    }
    return result;
  }
  
  // calculate and display log probability
  void calculate() {
    if (debug)
      cout << "classes:" << endl;
    for (auto& i : lblPosts) {
      double pr = log(i.second / (double)numPosts);
      logPrior[i.first] = pr;
      
      if (debug)
        cout << "  " << i.first << ", " << i.second
             << " examples, log-prior = " << pr << endl;
    }
    
    if (debug)
      cout << "classifier parameters:" << endl;
      
    for (auto& i : lwPosts) {
      map<string, int>& mapWords = i.second;
      int numLblPosts = lblPosts[i.first];
      map<string, double>& mapLogs = lwLog[i.first];
      for (auto& j : mapWords) {
        double pr2 = log(j.second / (double)numLblPosts);
        mapLogs[j.first] = pr2;
        if (debug)
          cout << "  " << i.first << ":" << j.first << ", count = "
               << j.second << ", log-likelihood = "
               << mapLogs[j.first] << endl;
      }
    }
    if (debug)
      cout << endl;
  }

  bool debug;
  int numPosts;
  map<string, int> wordPosts; // number of posts for each word
  map<string, int> lblPosts; // number of posts for each label
  map<string, map<string, int>> lwPosts; // number of posts for label & word
  
  map<string, double> logPrior; // probability for label
  map<string, map<string, double>> lwLog; // probability for word
};


int main (int argc, char* argv[]) {
  cout.precision(3);
  if (argc < 3 || argc > 4 || (argc == 4 && string(argv[3]) != "--debug")) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return -1;
  }
  
  ifstream trainfile(argv[1]);
  ifstream testfile(argv[2]);
  if (!trainfile.is_open()) {
    cout << "Error opening file: " << argv[1] << endl;
    return -1;
  }
  if (!testfile.is_open()) {
    cout << "Error opening file: " << argv[2] << endl;
    return -1;
  }
       
  Classifier c(argc == 4);
  c.train(trainfile);
  c.test(testfile);
  
  return 0;
}

