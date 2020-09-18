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
SORT_ORDER temp;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

//clears vector (or whatever datastructure you choose) holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to the vector holding these structs
//ignore malformed rows (see 'Project 1 Description')
//if ignoreFirstRow ==true then discard the first row
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename, bool ignoreFirstRow) {

	stats.clear();
	string str;

	ifstream inFile;
	inFile.open(filename);

	//Checks if file has been opened successfully
	//Returns COULD_NOT_OPEN_FILE if check determines open == false
	if (!inFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	//if ignoreFirstRow ==true then discard the first row
	if (ignoreFirstRow) {
		getline(inFile, str);
	}

	//While we are able to read lines from file continue
	while (getline(inFile, str)) {
		stringstream stream(str);
		vector<string>  vals;
		string temp;

		//Iterates through line parsing by CHAR_TO_LOOK_FOR(',')
		//Adds parsed line to temporary string vector vals
		while (getline(stream, temp, CHAR_TO_SEARCH_FOR)) {
			vals.push_back(temp);
		}

		//If vectors size doesn't equal 4, we know we have a corrupted line and need to skip
		//Additionally, if we find a space or empty character in our vector we skip due to corruption
		if ((vals.size() == 4) && !count(vals.begin(), vals.end(), " ") && !count(vals.begin(), vals.end(), "")) {
			process_stats ps;

			ps.process_number = stringToInt(vals[0].c_str());
			ps.start_time     = stringToInt(vals[1].c_str());
			ps.cpu_time       = stringToInt(vals[2].c_str());
			ps.io_time        = stringToInt(vals[3].c_str());

			stats.push_back(ps);
		}
	}

	return SUCCESS;
}

//Constructor for helper function sortt
bool sortt(process_stats, process_stats);

//will sort according to user preference
//sorts the vector, returns nothing
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	temp = mySortOrder;
	sort(stats.begin(), stats.end(), sortt);
}

//Helper function for sortData
//Switch statement utilizes enum value to determine what needs to be sorted
bool sortt(process_stats one, process_stats two) {
	switch (temp){
	case CPU_TIME:
		return (one.cpu_time < two.cpu_time);
		break;

	case PROCESS_NUMBER:
		return (one.process_number < two.process_number);
		break;

	case START_TIME:
		return (one.start_time < two.start_time);
		break;

	case IO_TIME:
		return (one.io_time < two.io_time);
		break;
	}

	return false;
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats myFirst;
	myFirst = stats.front();
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}
