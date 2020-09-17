/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

vector<process_stats> stats;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {

	stats.clear();
	string str;

	ifstream inFile;
	inFile.open(filename);

	if (!inFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	if (ignoreFirstRow) {
		getline(inFile, str);
	}

	while (getline(inFile, str)) {
		stringstream stream(str);
		vector<string>  vals;
		string temp;

		while (getline(stream, temp, CHAR_TO_SEARCH_FOR)) {
			vals.push_back(temp);
		}

		if (vals.size() == 4 && none_of(vals.begin(), vals.end(), " ") && none_of(vals.begin(), vals.end(), "")) {
			process_stats ps;

			ps.cpu_time       = stringToInt(vals[0].c_str());
			ps.process_number = stringToInt(vals[1].c_str());
			ps.start_time     = stringToInt(vals[2].c_str());
			ps.io_time        = stringToInt(vals[3].c_str());

			stats.push_back(ps);
		}
	}

	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


