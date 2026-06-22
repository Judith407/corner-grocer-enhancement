#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// class to be able to track and print the items and be able to set the max number for the array and keep a record of them  
class TrackItems {
public:
	TrackItems();
	void AddItem(string addItem);
	int GetItemCount(string addItem);
	void PrintAllIterations();
	void PrintHistogram();
	void BackupAccumulatedData();

private:
	static const int maxNumOfItems = 200;
	// arrays being used
	string items[maxNumOfItems];
	int iterate[maxNumOfItems];
	// tracks how many items are stored
	int itemCount;

};
//Set the item count to zero
TrackItems::TrackItems() {
	itemCount = 0;
}

//check for items and be able increment them if they have already appeared in list
void TrackItems::AddItem(string addItem) {
	bool appeared = false;

	// check if item is already in list. If the item is found it iterates the count in the array for the item.
	for (int i = 0; i < itemCount; ++i) {
		if (items[i] == addItem) {
			iterate[i]++;
			appeared = true;
			break;
		}
	}

	//If the item has not been added before we need to add it to the items array and start the count as 1 for the new item.
	if (!appeared && itemCount < maxNumOfItems) {
		items[itemCount] = addItem;
		iterate[itemCount] = 1;
		itemCount++;
	}
}
//be able to return the times an item appeared 
int TrackItems::GetItemCount(string addItem) {
	for (int i = 0; i < itemCount; ++i) {
		if (items[i] == addItem) {
			return iterate[i];
		}
	}
	return 0;
}
//print all the items and the times they have appeared
void TrackItems::PrintAllIterations() {
	for (int i = 0; i < itemCount; ++i) {
		cout << items[i] << " " << iterate[i] << endl;
	}
}

//print a histogram that shows the items and the times they have appeared with the symbol *
void TrackItems::PrintHistogram() {
	//for each item in the list print the item name and asteriks that count how many times the item appeared.
	for (int i = 0; i < itemCount; ++i) {
		//print the name of the item
		cout << items[i] << "";
		for (int h = 0; h < iterate[i]; ++h) {
			//print one asterik for all the times the item has appeared
			cout << "*";
		}
		cout << endl;
	}
}

//backup the accumilated data to a file
void TrackItems::BackupAccumulatedData() {
	ofstream backupFile("frequency.dat");

	if (backupFile.is_open()) {
		for (int i = 0; i < itemCount; ++i) {
			backupFile << items[i] << "" << iterate[i] << endl;
		}
		backupFile.close();
	}
	else {
		cout << "Error when opening file." << endl;
	}
}

int main() {
	TrackItems tracker;
	string item;
	int menuOption;

	ifstream inputFile("InputFile.txt");

	//check to see if the file was opened correctly
	if (inputFile.is_open()) {
		while (inputFile >> item) {
			tracker.AddItem(item);
		}
		//close the file
		inputFile.close();
	}
	else {
		cout << "Error could not open InputFile.txt" << endl;
		return 1;
	}

	//main loop for the menu to be able to see which menu option they would want to look at
	while (true) {
		cout << "1. Look up how many times item has been purchased" << endl;
		cout << "2. Print items and how many times they have been purchased" << endl;
		cout << "3. Print histogram of item list and how many times they have been purchased shown by asteriks" << endl;
		cout << "4. Exit the program" << endl;
		cin >> menuOption;

		if (menuOption == 1) {
			cout << "Enter the item: ";
			cin >> item;
			int frequencyOfItem = tracker.GetItemCount(item);
			cout << frequencyOfItem << endl;
		}
		else if (menuOption == 2) {
			tracker.PrintAllIterations();
		}
		else if (menuOption == 3) {
			tracker.PrintHistogram();
		}
		else if (menuOption == 4) {
			tracker.BackupAccumulatedData();
			break;
		}
		else {
			cout << "Invalid, try again." << endl;
		}
	}
	return 0;
}



