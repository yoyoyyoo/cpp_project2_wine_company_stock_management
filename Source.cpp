#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// COMP1200 Assignment3 by Yanan
// This is a program to manage the wines record of a company.

const int SIZE = 10;
const int NO_WINES = 25;
const int NO_SALES = 4;
void printReport(ofstream&, const string[], const double[][NO_SALES], const double[], int, int);
void loadArrays(ifstream&, string[], double[][NO_SALES], int& );
void computeSum(const double[][NO_SALES], double[SIZE], int);
void findWine(const double[][NO_SALES], int&, int&, int);
void mostWineSold(const double[], int&, int);

int main()
{
	double salesAmt[SIZE][4];  //no need to change your variable names to match mine!
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);

	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;

	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");
}

//function to load array from file
void loadArrays(ifstream& fin, string wine[], 
	            double salesAmt[][NO_SALES], int& noWines )
{
	for (noWines = 0; noWines < NO_WINES; noWines++)
	{
		getline(fin, wine[noWines]);
		
		if (fin.eof())
			break;

		for (int col = 0; col < NO_SALES; col++)
		{
			fin >> salesAmt[noWines][col];
		}

		fin.ignore(80, '\n');
	}
	
}

//function to compute sum
void computeSum(const double salesAmt[][NO_SALES], 
	            double yearlySales[SIZE], int noWines)
{
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < NO_SALES; col++)
			yearlySales[row] += salesAmt[row][col];
	}
}

//function to print report
void printReport(ofstream& fout, const string wine[], 
	             const double salesAmt[][NO_SALES], const double yearlySales[],
                 int mostSold, int noWines)
{
	double sum = 0.0;
	fout << left << setw(30) << "Wine" << setw(30) << "Quarterly Sales" << endl
		 << right << setw(15) << "1st" 
		          << setw(10) << "2nd" 
		          << setw(10) << "3rd" 
		          << setw(10) << "4th" 
		          << setw(10) << "Yearly" << endl;

	for (int row = 0; row < noWines; row++)
	{
		fout << left << setw(7) << wine[row];
		for (int col = 0; col < NO_SALES; col++)
		{
			fout << right << setw(10) << salesAmt[row][col];
		}
		fout << right << setw(10) << yearlySales[row];
		if (row == mostSold)
			fout << "***most sold***" ;
		fout << endl << endl;

		sum += yearlySales[row];
	}

	fout << "Total Sales Amount $" << sum << endl << endl;

}

//function to find the highest quartely sales amout
void findWine(const double salesAmt[][NO_SALES], int& highestRow, 
	          int& highestCol, int noWines)
{   
	highestCol = 0;
	highestRow = 0;
	for (int row = 0; row < noWines ; row++)
	{
		for (int col = 0; col < NO_SALES; col++)
		{
			if (salesAmt[row][col] > salesAmt[highestRow][highestCol])
			{
				highestRow = row;
				highestCol = col;
			}
		}
	}
}

//function to find the most wine sold
void mostWineSold(const double yearlySales[], int& mostSold, int noWines)
{
	mostSold = 0;
	for (int index = 0; index < noWines; index++)
	{
		if (yearlySales[index] > yearlySales[mostSold])
			mostSold = index;
	}
}

/* I/O 
* 

Load arrays



=======================================================



Compute yearly Sale



=======================================================



Find best selling wine and highest sales amount:



White had the highest sales amount = $300000.00


=======================================================



Find the most sold wine:



 Most sold wine is White


=======================================================



=======================================================

program ended successfully


 Printing wines.dat file

Red
200000.00       50000.00        57000.00        16800.00
Rose
25000.00                0.00      4500.00         7800.00
White
300000.00            4400.00            23000.00              5300.00

 Printing winesales.rpt file

Wine                          Quarterly Sales
            1st       2nd       3rd       4th    Yearly
Red     200000.00  50000.00  57000.00  16800.00 323800.00

Rose     25000.00      0.00   4500.00   7800.00  37300.00

White   300000.00   4400.00  23000.00   5300.00 332700.00***most sold***

Total Sales Amount $693800.00

Press any key to continue . . .

F:\Yanan\SLC\semester2\COMP1200 C++\ass\Ass3\COMP1200Ass3\Debug\COMP1200Ass3.exe (process 27880) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .


*/