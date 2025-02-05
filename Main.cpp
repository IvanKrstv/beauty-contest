#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
using namespace std;

struct Participants
{
	int number, age;
	char name[80];
	char gender[7];
	float hips, shoulders, necks, calves;
	float results;
};

const int max_participants_size = 30;

const int no_column_width = 5;
const int age_column_width = 5;
const int gender_column_width = 8;
const int hips_column_width = 8;
const int shoulders_column_width = 11;
const int neck_column_width = 8;
const int calves_column_width = 8;
const int table_width_without_name = no_column_width + age_column_width + gender_column_width + hips_column_width + shoulders_column_width + neck_column_width + calves_column_width + 9;

const char text_file[] = "participants.txt";
const char binary_file[] = "participants.bin";

void Input(Participants participants[], int& size, int& max_name, int &saved_into_file);

void Output(Participants participants[], int size, int max_name);

void SubMenu(Participants participants[], int size, int max_name);
void SearchYoungest(Participants participants[], int size);
void SearchByName(Participants participants[], int size, int max_name);

void SortByAge(Participants participants[], int size);

void FileSubMenu(Participants participants[], int &size, bool &entered, int &max_name, int &saved_into_file);
void OutputFile(Participants participants[], int size);
void InputFile(Participants participants[], int &size, bool &entered, int &max_name, int &saved_into_file);

void AdditionalFunctions(Participants participants[], int size, int max_name);
void SortByAgeWithoutChanging(Participants participants[], int size, int max_name);
void SearchByAge(Participants participants[], int size, int max_name);
void SearchByGender(Participants participants[], int size, int max_name);

void AgeCategories(Participants participants[], int size, Participants c1[], int& c1_size, Participants c2[], int& c2_size, Participants c3[], int& c3_size, Participants c4[], int& c4_size, int max_name, int &sorted, bool &category1_entered, bool& category2_entered, bool& category3_entered, bool& category4_entered);
void SplitIntoCategories(Participants participants[], int size, Participants c1[], int& c1_size, Participants c2[], int& c2_size, Participants c3[], int& c3_size, Participants c4[], int& c4_size, bool& entered1, bool& entered2, bool& entered3, bool& entered4, int &sorted);

void Winners(Participants p[], int size, int max_name, Participants c1[], int &c1_size, Participants c2[], int &c2_size, Participants c3[], int &c3_size, Participants c4[], int &c4_size, int &sorted, bool& category1_entered, bool& category2_entered, bool& category3_entered, bool& category4_entered);
void CalculateResults(Participants participants[], int size);
void CategoryWinner(Participants c[], int c_size, int max_name, int number_category, int a, int b);
void BubbleSortDescending(Participants p[], int size);
void BubbleSortAscending(Participants p[], int size);
void BodyOfTableForCategories(Participants c[], int c_size, int max_name);
void HeaderRowOfTableForCategories(int max_name);
void TitleRowOfTableForCategories(int max_name);

void AutoInput(Participants participants[], int& size, int& max_name, bool &entered, int &saved_into_file);
void AutoOutput(Participants participants[], int size, int &saved_into_file);

void HeaderRowOfTable(int max_name);
void TitleRowOfTable(int max_name);
void BodyOfTable(Participants participants[], int size, int max_name, int i);

bool CheckParticipantsEntered(bool entered);
void CheckMaxName(Participants participants[], int size, int& max_name);
bool CheckCin();
void PressEnterToContinue();
void PressEnterToContinueAfterIgnore();
void ClearBuffer();

int main()
{
	int choice;
	bool exit = false;
	bool entered_participants = false;
	int saved_into_file = 0;

	Participants participants[max_participants_size];
	int size = 0;
	Participants category1[max_participants_size], category2[max_participants_size],
				 category3[max_participants_size], category4[max_participants_size];
	int category1_size = 0, category2_size = 0, category3_size = 0, category4_size = 0; int sorted_into_categories = 0;
	bool category1_entered = false, category2_entered = false, category3_entered = false, category4_entered = false;

	int max_name = 0;
	AutoInput(participants, size, max_name, entered_participants, saved_into_file);
	do
	{
		cout << "Beauty contest" << endl;
		cout << endl;
		cout << "1. Add new participants;" << endl;
		cout << "2. Display all participants;" << endl;
		cout << "3. Search participants;" << endl;
		cout << "4. Sort the participants in ascending order by their age;" << endl;
		cout << "5. Manage file;" << endl;
		cout << "6. Additional actions;" << endl;
		cout << "7. Split into categories;" << endl;
		cout << "8. Winners from each category;" << endl;
		cout << "9. Exit." << endl;
		cout << "\nEnter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 9)
		{
			switch (choice)
			{
			case 1: Input(participants, size, max_name, saved_into_file);
				entered_participants = true;
				break;

			case 2: if (CheckParticipantsEntered(entered_participants))
			{
				Output(participants, size, max_name);
				PressEnterToContinue();
			}
				break;

			case 3: if (CheckParticipantsEntered(entered_participants))
			{
				system("cls");
				SubMenu(participants, size, max_name);
			}
				  break;

			case 4: if (CheckParticipantsEntered(entered_participants))
				SortByAge(participants, size);
				  break;

			case 5: system("cls");
				FileSubMenu(participants, size, entered_participants, max_name, saved_into_file);
				break;

			case 6: if (CheckParticipantsEntered(entered_participants))
			{
				system("cls");
				AdditionalFunctions(participants, size, max_name);
			}
				  break;

			case 7: if (CheckParticipantsEntered(entered_participants))
			{
				CalculateResults(participants, size);
				AgeCategories(participants, size, category1, category1_size, category2, category2_size, category3, category3_size, category4, category4_size, max_name, sorted_into_categories, category1_entered, category2_entered, category3_entered, category4_entered);
				PressEnterToContinue();
			}
				break;

			case 8: if (CheckParticipantsEntered(entered_participants))
			{
				CalculateResults(participants, size);
				Winners(participants, size, max_name, category1, category1_size, category2, category2_size, category3, category3_size, category4, category4_size, sorted_into_categories, category1_entered, category2_entered, category3_entered, category4_entered);
				PressEnterToContinue();
			}
				break;

			case 9: exit = true;
				break;
			}
		}
		else
		{
			cout << "Invalid choice! Try again!" << endl;
			PressEnterToContinue();
		}
		system("cls");
	} while (!exit);
	AutoOutput(participants, size, saved_into_file);
	cout << "Participants data has been written to participants.txt" << endl;
	return 0;
}


void Input(Participants participants[], int& size, int& max_name, int &saved_into_file)
{
	int new_participants;

	cout << "How many new participants would you like to add? ";
	cin >> new_participants;
	cout << endl;
	if (new_participants > max_participants_size - size)
		cout << "There are not enough places left. You can add only up to " << max_participants_size - size << " participants more." << endl;
	else
	{
		for (int i = 0; i < new_participants; i++)
		{
			cout << "Participant No. " << size + 1 << ':' << endl;
			cout << endl;

			cout << "Number: "; cin >> participants[size].number;
			if (!CheckCin())
				return;

			ClearBuffer();
			cout << "Name: "; cin.getline(participants[size].name, 79);
			CheckMaxName(participants, size, max_name);

			cout << "Age: "; cin >> participants[size].age;
			if (!CheckCin())
				return;

			ClearBuffer();
			cout << "Gender: "; cin.getline(participants[size].gender, 7);

			cout << "Hip circumference: "; cin >> participants[size].hips;
			if (!CheckCin())
				return;

			cout << "Shoulder circumference: "; cin >> participants[size].shoulders;
			if (!CheckCin())
				return;

			cout << "Neck circumference: "; cin >> participants[size].necks;
			if (!CheckCin())
				return;

			cout << "Calf circumference: "; cin >> participants[size].calves;
			if (!CheckCin())
				return;

			cout << endl;
			size++;
			AutoOutput(participants, size, saved_into_file);
		}
	}
}


void Output(Participants participants[], int size, int max_name)
{
	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
		BodyOfTable(participants, size, max_name, i);
}


void SubMenu(Participants participants[], int size, int max_name)
{
	int choice;
	bool back = false;
	do
	{
		cout << "1. Search youngest participants;" << endl;
		cout << "2. Search by name;" << endl;
		cout << "3. Back" << endl;
		cout << "\nEnter your choice: "; cin >> choice;

		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 3)
		{
			switch (choice)
			{
			case 1: SearchYoungest(participants, size);
				PressEnterToContinue();
				break;
			case 2: SearchByName(participants, size, max_name);
				PressEnterToContinueAfterIgnore();
				break;
			case 3: back = true;
				break;
			}
		}
		else 
		{
			cout << "No such choice!" << endl;
			PressEnterToContinue();
		}
		system("cls");
	} while (!back);
}
void SearchYoungest(Participants participants[], int size)
{
	int min_age = participants[0].age, counter = 0;

	for (int i = 1; i < size; i++)
	{
		if (participants[i].age < min_age)
			min_age = participants[i].age;
	}

	for (int j = 0; j < size; j++)
	{
		if (participants[j].age == min_age)
		{
			if (counter >= 1)
				cout << ", ";
			cout << participants[j].name;
			counter++;
		}
	}

	cout << endl;
	if (counter > 1)
		cout << "These participants are " << min_age << " years old." << endl;
	else cout << "The participant is " << min_age << " years old." << endl;
}
void SearchByName(Participants participants[], int size, int max_name)
{
	char target_name[80]; bool found = false;

	cout << "Name: ";
	ClearBuffer();
	cin.getline(target_name, 79);

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(target_name, participants[i].name) == 0)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}

	if (!found)
		cout << "No participant with such name." << endl;
}


void SortByAge(Participants participants[], int size)
{
	Participants temp;
	bool swap = false;
	for (int i = 0; i < size - 1; i++)
	{
		swap = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (participants[j].age > participants[j + 1].age)
			{
				temp = participants[j];
				participants[j] = participants[j + 1];
				participants[j + 1] = temp;
				swap = true;
			}
		}
		if (!swap)
			break;
	}
}


void FileSubMenu(Participants participants[], int &size, bool &entered, int &max_name, int &saved_into_file)
{
	int choice; bool exit = false;
	do
	{
		cout << "1. Output to file;" << endl;
		cout << "2. Input from file;" << endl;
		cout << "3. Back." << endl;
		cout << endl;
		cout << "Enter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;

		switch (choice)
		{
		case 1: if (entered)
			OutputFile(participants, size);
			break;
		case 2: InputFile(participants, size, entered, max_name, saved_into_file);
			entered = true;
			PressEnterToContinue();
			break;
		case 3: exit = true;
			break;
		default: cout << "No such choice!" << endl;
		}
		system("cls");
	} while (!exit);
}
void OutputFile(Participants participants[], int size)
{
	ofstream out_file(binary_file, ios_base::binary);
	if (!out_file)
	{
		cout << "Error opening file." << endl;
		return;
	}
	for (int i = 0; i < size; i++)
	{
		out_file.write((char*)&participants[i], sizeof(Participants));
	}
	out_file.flush();
	out_file.close();
}
void InputFile(Participants participants[], int &size, bool& entered, int &max_name, int &saved_into_file)
{
	ifstream in_file(binary_file, ios::binary);
	if (!in_file)
	{
		cout << "Error opening file." << endl;
		return;
	}
	while (size < max_participants_size && in_file.read((char*)&participants[size], sizeof(Participants)))
	{
		cout << "\nParticipant No. " << size + 1 << endl;
		cout << "\nNumber: " << participants[size].number << endl;
		cout << "Name: " << participants[size].name << endl; CheckMaxName(participants, size, max_name);
		cout << "Age: " << participants[size].age << endl;
		cout << "Gender: " << participants[size].gender << endl;
		cout << "Hips circumference: " << participants[size].hips << endl;
		cout << "Shoulders circumference: " << participants[size].shoulders << endl;
		cout << "Neck circumference: " << participants[size].necks << endl;
		cout << "Calves circumference: " << participants[size].calves << endl;
		size++;
		AutoOutput(participants, size, saved_into_file);
		entered = true;
	}
	if (size >= max_participants_size)
		cout << "No more places left!" << endl;
	in_file.close();
}


void AdditionalFunctions(Participants participants[], int size, int max_name)
{
	int choice; bool back = false;
	do
	{
		cout << "1. Display all participants sorted by age;" << endl;
		cout << "2. Search by age;" << endl;
		cout << "3. Search by gender;" << endl;
		cout << "4. Back" << endl;
		cout << "\nEnter your choice: "; cin >> choice;
		if (!CheckCin())
			continue;
		cout << endl;

		if (choice >= 1 && choice <= 4)
		{
			switch (choice)
			{
			case 1: SortByAgeWithoutChanging(participants, size, max_name);
				PressEnterToContinue();
				break;
			case 2: SearchByAge(participants, size, max_name);
				break;
			case 3: SearchByGender(participants, size, max_name);
				PressEnterToContinueAfterIgnore();
				break;
			case 4: back = true;
				break;
			}
		}
		else {
			cout << "No such choice!" << endl;
			PressEnterToContinue();
		}
		system("cls");
	} while (!back);
}
void SortByAgeWithoutChanging(Participants participants[], int size, int max_name)
{
	Participants temp_participants[max_participants_size];
	for (int i = 0; i < size; i++)
		temp_participants[i] = participants[i];

	SortByAge(temp_participants, size);
	Output(temp_participants, size, max_name);
}
void SearchByAge(Participants participants[], int size, int max_name)
{
	int target_age; bool found = false;
	cout << "Age: "; cin >> target_age;
	if (!CheckCin())
		return;
	cout << endl;

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (participants[i].age == target_age)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}
	
	if (!found)
		cout << "No participant is this age." << endl;
	PressEnterToContinue();
}
void SearchByGender(Participants participants[], int size, int max_name)
{
	char target_gender[7]; bool found = false;
	cout << "Gender: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cin.getline(target_gender, 7);
	cout << endl;

	HeaderRowOfTable(max_name);
	TitleRowOfTable(max_name);
	HeaderRowOfTable(max_name);

	for (int i = 0; i < size; i++)
	{
		if (strcmp(target_gender, participants[i].gender) == 0)
		{
			found = true;
			BodyOfTable(participants, size, max_name, i);
		}
	}

	if (!found)
		cout << "No participant is this gender." << endl;
}


void AgeCategories(Participants participants[], int size, Participants c1[], int &c1_size, Participants c2[], int &c2_size, Participants c3[], int &c3_size, Participants c4[], int &c4_size, int max_name, int &sorted, bool &category1_entered, bool& category2_entered, bool& category3_entered, bool& category4_entered)
{	
	SplitIntoCategories(participants, size, c1, c1_size, c2, c2_size, c3, c3_size, c4, c4_size, category1_entered, category2_entered, category3_entered, category4_entered, sorted);

	if (category1_entered)
	{
		cout << "Category 1 (14-16 years)" << endl;
		cout << endl;
		Output(c1, c1_size, max_name);
	}
	else cout << "No participants in category 1 (14-16 years)." << endl;

	if (category2_entered)
	{
		cout << "\nCategory 2 (17-19 years)" << endl;
		cout << endl;
		Output(c2, c2_size, max_name);
	}
	else cout << "No participants in category 2 (17-19 years)." << endl;

	if (category3_entered)
	{
		cout << "\nCategory 3 (20-22 years)" << endl;
		cout << endl;
		Output(c3, c3_size, max_name);
	}
	else cout << "No participants in category 3 (20-22 years)." << endl;

	if (category4_entered)
	{
		cout << "\nCategory 4 (23-25 years)" << endl;
		cout << endl;
		Output(c4, c4_size, max_name);
	}
	else cout << "\nNo participants in category 4 (23-25 years)." << endl;
}
void SplitIntoCategories(Participants participants[], int size, Participants c1[], int& c1_size, Participants c2[], int& c2_size, Participants c3[], int& c3_size, Participants c4[], int& c4_size, bool &entered1, bool &entered2, bool &entered3, bool &entered4, int &sorted)
{
	for (int i = sorted; i < size; i++)
	{
		if (14 <= participants[i].age && participants[i].age <= 16)
		{
			c1[c1_size] = participants[i];
			c1_size++;
			entered1 = true;
		}
		else if (17 <= participants[i].age && participants[i].age <= 19)
		{
			c2[c2_size] = participants[i];
			c2_size++;
			entered2 = true;
		}
		else if (20 <= participants[i].age && participants[i].age <= 22)
		{
			c3[c3_size] = participants[i];
			c3_size++;
			entered3 = true;
		}
		else if (23 <= participants[i].age && participants[i].age <= 25)
		{
			c4[c4_size] = participants[i];
			c4_size++;
			entered4 = true;
		}
		sorted++;
	}
}


void Winners(Participants p[], int size, int max_name, Participants c1[], int &c1_size, Participants c2[], int &c2_size, Participants c3[], int &c3_size, Participants c4[], int &c4_size, int &sorted, bool& category1_entered, bool& category2_entered, bool& category3_entered, bool& category4_entered)
{
	SplitIntoCategories(p, size, c1, c1_size, c2, c2_size, c3, c3_size, c4, c4_size, category1_entered, category2_entered, category3_entered, category4_entered, sorted);
	if (category1_entered) CategoryWinner(c1, c1_size, max_name, 1, 14, 16);
	else cout << "No participants in category 1 (14-16 years)." << endl;
	if (category2_entered) CategoryWinner(c2, c2_size, max_name, 2, 17, 19);
	else cout << "No participants in category 2 (17-19 years)." << endl;
	if (category3_entered) CategoryWinner(c3, c3_size, max_name, 3, 20, 22);
	else cout << "No participants in category 3 (20-22 years)." << endl;
	if (category4_entered) CategoryWinner(c4, c4_size, max_name, 4, 23, 25);
	else cout << "No participants in category 4 (23-25 years)." << endl;
}
void CalculateResults(Participants participants[], int size)
{
	for (int i = 0; i < size; i++)
	participants[i].results = participants[i].hips / (participants[i].shoulders + participants[i].necks + participants[i].calves);

}
void CategoryWinner(Participants c[], int c_size, int max_name, int number_category, int a, int b)
{
	Participants c_optimal[max_participants_size], c_bigger[max_participants_size], c_smaller[max_participants_size];
	int c_optimal_size = 0, c_bigger_size = 0, c_smaller_size = 0;

	for (int i = 0; i < c_size; i++)
	{
		if (0.54 <= c[i].results && c[i].results <= 0.62)
		{
			c_optimal[c_optimal_size] = c[i];
			c_optimal_size++;
		}
		else if (c[i].results <= 0.53)
		{
			c_smaller[c_smaller_size] = c[i];
			c_smaller_size++;
		}
		else if (c[i].results >= 0.63)
		{
			c_bigger[c_bigger_size] = c[i];
			c_bigger_size++;
		}
	}
	cout << "Category " << number_category << "(" << a << " - " << b << " years)" << endl;
	cout << endl;
	HeaderRowOfTableForCategories(max_name); 
	TitleRowOfTableForCategories(max_name);
	HeaderRowOfTableForCategories(max_name);

	BubbleSortDescending(c_optimal, c_optimal_size);
	BodyOfTableForCategories(c_optimal, c_optimal_size, max_name);

	BubbleSortAscending(c_bigger, c_bigger_size);
	BodyOfTableForCategories(c_bigger, c_bigger_size, max_name);

	BubbleSortAscending(c_smaller, c_smaller_size);
	BodyOfTableForCategories(c_smaller, c_smaller_size, max_name);

	string winner;
	if (c_optimal_size > 0)
		winner = c_optimal[0].name;
	else if (c_bigger_size > 0)
		winner = c_bigger[0].name;
	else if (c_smaller_size > 0)
		winner = c_smaller[c_smaller_size - 1].name;
	cout << "\nWinner of category " << number_category << " is " << winner << "." << endl;
	cout << endl;
}
void BubbleSortDescending(Participants p[], int size)
{
	Participants temp;
	bool swap = false;

	for (int i = 0; i < size - 1; i++)
	{
		swap = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (p[j].results < p[j + 1].results)
			{
				temp = p[j + 1];
				p[j + 1] = p[j];
				p[j] = temp;
				swap = true;
			}
		}
		if (!swap)
			break;
	}
}
void BubbleSortAscending(Participants p[], int size)
{
	Participants temp;
	bool swap = false;

	for (int i = 0; i < size - 1; i++)
	{
		swap = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (p[j].results > p[j + 1].results)
			{
				temp = p[j + 1];
				p[j + 1] = p[j];
				p[j] = temp;
				swap = true;
			}
		}
		if (!swap)
			break;
	}
}

void BodyOfTableForCategories(Participants c[], int c_size, int max_name)
{
	for (int i = 0; i < c_size; i++)
	{
		cout << fixed << setprecision(2);
		cout << "| " <<
			setw(no_column_width - 2) << right << c[i].number << " | " <<
			setw(max_name + 1) << left << c[i].name << "| " <<
			setw(age_column_width - 2) << right << c[i].age << " | " <<
			setw(gender_column_width - 2) << left << c[i].gender << " | " <<
			setw(hips_column_width - 2) << right << c[i].hips << " | " <<
			setw(shoulders_column_width - 2) << right << c[i].shoulders << " | " <<
			setw(neck_column_width - 2) << right << c[i].necks << " | " <<
			setw(calves_column_width - 2) << right << c[i].calves << " | " << 
			setw(7) << right << c[i].results << " |" << endl;
		for (int j = 0; j < table_width_without_name + max_name + 2 + 10; j++)
			cout << "-";
		cout << endl;
	}
}
void HeaderRowOfTableForCategories(int max_name)
{
	cout << "+"; for (int i = 0; i < no_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < max_name + 2; i++) cout << "-"; cout << "+"; for (int i = 0; i < age_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < gender_column_width; i++) cout << "-"; cout << "+"; for (int i = 0; i < hips_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < shoulders_column_width; i++) cout << "-"; cout << "+"; for (int i = 0; i < neck_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < calves_column_width; i++) cout << "-"; cout << "+"; for (int i = 0; i < 9; i++) cout << "-"; cout << "+" << endl;
}
void TitleRowOfTableForCategories(int max_name)
{
	cout << "| No. |" << setw(max_name + 2) << left << " Name" << "| Age | Gender |  Hips  | Shoulders |  Neck  | Calves | Results |" << endl;
}


void AutoInput(Participants participants[], int& size, int& max_name, bool &entered, int &saved_into_file)
{
	char temp[10];

	ifstream in_file(text_file);
	if (!in_file)
	{
		cout << "Error opening file. No participants have been added." << endl;
		return;
	}
	while (!in_file.eof() && size < max_participants_size)
	{
		in_file >> temp;
		participants[size].number = atoi(temp);

		in_file.clear(); in_file.ignore(numeric_limits<streamsize>::max(), '\n');
		in_file.getline(participants[size].name, 80);
		CheckMaxName(participants, size, max_name);

		in_file >> temp;
		participants[size].age = atoi(temp);

		in_file.clear(); in_file.ignore(numeric_limits<streamsize>::max(), '\n');
		in_file.getline(participants[size].gender, 7);

		in_file >> temp;
		participants[size].hips = atof(temp);


		in_file >> temp;
		participants[size].shoulders = atof(temp);


		in_file >> temp;
		participants[size].necks = atof(temp);


		in_file >> temp;
		participants[size].calves = atof(temp);

		size++;
		saved_into_file++;
		entered = true;
	}
	in_file.close();
}
void AutoOutput(Participants participants[], int size, int &saved_into_file)
{
	ofstream out_file(text_file, ios::app);
	if (!out_file)
	{
		cout << "Error opening file." << endl;
		return;
	}
	if (saved_into_file == size)
	{
		out_file.close();
		return;
	}
	if (saved_into_file != 0)
		out_file << endl;
	for (;saved_into_file < size;)
	{
		out_file << participants[saved_into_file].number << endl;
		out_file << participants[saved_into_file].name << endl;
		out_file << participants[saved_into_file].age << endl;
		out_file << participants[saved_into_file].gender << endl;
		out_file << participants[saved_into_file].hips << endl;
		out_file << participants[saved_into_file].shoulders << endl;
		out_file << participants[saved_into_file].necks << endl;
		out_file << participants[saved_into_file].calves;
		if (saved_into_file != size - 1)
			out_file << endl;
		saved_into_file++;
	}
	out_file.close();
}


void HeaderRowOfTable(int max_name)
{
	cout << "+"; for (int i = 0; i < no_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < max_name + 2; i++) cout << "-"; cout << "+"; for (int i = 0; i < age_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < gender_column_width; i++) cout << "-"; cout << "+"; for (int i = 0; i < hips_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < shoulders_column_width; i++) cout << "-"; cout << "+"; for (int i = 0; i < neck_column_width; i++) cout << "-";
	cout << "+"; for (int i = 0; i < calves_column_width; i++) cout << "-"; cout << "+" << endl;
}
void TitleRowOfTable(int max_name)
{
	cout << "| No. |" << setw(max_name + 2) << left << " Name" << "| Age | Gender |  Hips  | Shoulders |  Neck  | Calves |" << endl;
}
void BodyOfTable(Participants participants[], int size, int max_name, int i)
{
	cout << fixed << setprecision(2);
	cout << "| " <<
		setw(no_column_width - 2) << right << participants[i].number << " | " <<
		setw(max_name + 1) << left << participants[i].name << "| " <<
		setw(age_column_width - 2) << right << participants[i].age << " | " <<
		setw(gender_column_width - 2) << left << participants[i].gender << " | " <<
		setw(hips_column_width - 2) << right << participants[i].hips << " | " <<
		setw(shoulders_column_width - 2) << right << participants[i].shoulders << " | " <<
		setw(neck_column_width - 2) << right << participants[i].necks << " | " <<
		setw(calves_column_width - 2) << right << participants[i].calves << " |" << endl;
	if (i != size - 1)
	{
		for (int j = 0; j < table_width_without_name + max_name + 2; j++)
			cout << "-";
		cout << endl;
	}
	else HeaderRowOfTable(max_name);
}


void CheckMaxName(Participants participants[], int size, int &max_name)
{
	if (strlen(participants[size].name) > max_name)
		max_name = strlen(participants[size].name);
}
bool CheckParticipantsEntered(bool entered)
{
	if (!entered)
	{
		cout << "There are no entered participants!" << endl;
		PressEnterToContinue();
		return false;
	}
	return true;
}
bool CheckCin()
{
	if (cin)
		return true;
	else
	{
		cout << "\nInvalid input!" << endl;
		PressEnterToContinue();
		system("cls");
		return false;
	}
}
void PressEnterToContinue()
{
	cout << "\nPress Enter to continue";
	ClearBuffer();
	cin.get();
}
void PressEnterToContinueAfterIgnore()
{
	cout << "\nPress Enter to continue";
	cin.get();
}
void ClearBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
