#include "duplicatefinder.h"
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
    DuplicateFinder finder("samples/");

	list<Duplicate> duplicates = finder.find_duplicates();
	
	foreach(Duplicate dup, duplicates)
		cout << dup.original << endl << dup.duplicate << endl;
		
	char cr;
	cin >> cr
	
    return 0;
}
