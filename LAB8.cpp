 /**
* @bonusLab.cpp
* @author Kirill Melnikov
* @Date 7/09/2017
* @version 1.0
* @section Takes in a vector, and stores author, book title, and date book was created into a database which is outputted
*/
// I declare that this assignment is my own work and that I have correctly acknowledged the
// work of others. I acknowledged that I have read and followed the Academic Honesty and
// Integrity related policies as outlined in the syllabus.
//
// __Kirill Melnikov___ (PRINT YOUR NAME HERE) ____ _____(DATE)____7/17/2018__________
//
// ____ (STUDENT ID) _301312400_____
//

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<iterator>
#include<iomanip>
using namespace std;

const int MAX_SIZE = 2519; //initialized to 50000, incase csv file goes beyond the original 2500 line length
const int lengthYears = 119; //giving a range of 1900 to 2018 for the amount of years that could be used to calculate stock price
void wordOutFile(string fileArray[]);

class Stock
{
public:
	Stock();
	double getHighPrice();
	string getDate();
	void setDate(string Date);
    void setHighPrice(double HighPrice);
	friend bool operator < (const Stock& object1, const Stock& object2);
	void output(ofstream& outfile);

private:
	string date;
	double highPrice;
};


int main ()
{
	vector <Stock> list;
	vector <Stock>::iterator it;
	vector <double> yearAvg;
	vector <double> monthlyAvg;
	vector <double> highestP;
	vector <double> lowestP;
	Stock stockData[MAX_SIZE];
	double average[lengthYears] = {0.0};
	ofstream outFile;
	int avg[lengthYears];
	double avgMonthly[13] = {0.0};
	int avgM[13];
	string arrayPrices[MAX_SIZE];
	string comma = ",";
	int temp = 0;
	string holdValue;
	string highPrice[MAX_SIZE];
	string date[MAX_SIZE];
	double hold = 0.0;
	double highestPrice[lengthYears] = {0.0};
	string highestPriceDay[lengthYears];
	string lowestPriceDay[lengthYears];
	double tempValueLowest[MAX_SIZE] = {0.0};
	int pos1 = 0;
	int pos2 = 0;
	int pos3 = 0;
	string year[120];
	int posDiff = 0; //finds position of commas on a per line basis, need 3 positions b/c high prices are located just before 3rd comma. 
	//This is needed b/c data extracted based on position of commas.

	for(int i = 0; i <= lengthYears; i++)
	{
		temp = 1900 + i; //intiial range can start from anywhere, 1900 is picked because data before that is probably not used
 		year[i] = to_string(temp);
	}


	wordOutFile(arrayPrices); //arrayPrices now holds the stock prices file. 
	

	for(int i = 2; i < MAX_SIZE; i++)
	{
		pos1 = arrayPrices[i].find(comma); //position of 1st comma
		pos2 = arrayPrices[i].find(comma, pos1+1); //position of 2nd comma
		pos3 = arrayPrices[i].find(comma, pos2+1); //position of 3rd comma

		posDiff = pos3 - pos2 - 1; // -1 added in to ingnore extra comma.

		highPrice[i - 2] = arrayPrices[i].substr(pos2+1, posDiff); //start from i - 2 to have elements filled from 0 to MAX.

		cout.precision(10);//make it so that 6 decimal values are extracted; stod by itself would lose data w/o this

		hold = stold(highPrice[i - 2]); //right now, hold converts value of high price into double
		holdValue = arrayPrices[i].substr(0,pos1);




		for(int j = 0; j <= lengthYears; j++) //take in a value for that year
		{
			if(((holdValue.substr(5,4) == year[j]) || (holdValue.substr(4,4) == year[j])) && tempValueLowest[j] <= 0.0) //instead of using array, do checkign by using "2008", or "2009", etc.
			{	
					tempValueLowest[j] = hold;	
			}
		}

	
		stockData[i - 2].setHighPrice(hold); //set value of hold for the highPrice
		stockData[i - 2].setDate(arrayPrices[i].substr(0,pos1)); //extract the date from element to 0, to first comma(i.e extract date).



		//-------------------------FINDING AVERAGE PER YEAR----------------------------

		for(int j = 0; j <= lengthYears; j++)
		{
			if((holdValue.substr(5,4) == year[j]) || (holdValue.substr(4,4) == year[j]))
			{

				average[j] += hold;
				avg[j]++;
			}
		}
		
		//-----------------END OF FINDING AVERAGE PRICE PER YEAR----------------




		//-----------------FIND HIGHEST & LOWEST PRICE PER YEAR---------------------


		//-------------------HIGHEST PRICE
		for(int k = 0; k <= lengthYears; k++) //must complete to find highest and lowest value
		{
		     if((holdValue.substr(5,4) == year[k]) || (holdValue.substr(4,4) == year[k])) 
		     {
		        if(hold > highestPrice[k])
		        {
		       		 highestPrice[k] = hold;
		       		 highestPriceDay[k] = holdValue;

		        }
		    }

		}
		//-------------------HIGHEST PRICE DONE



		//--------------------LOWEST PRICE
		for(int s = 0; s <= lengthYears; s++) //must complete to find highest and lowest value
		{
		     if((holdValue.substr(5,4) == year[s]) || (holdValue.substr(4,4) == year[s])) 
		     {
		        if(hold < tempValueLowest[s])
		        {
		       		 tempValueLowest[s] = hold;
		       		 lowestPriceDay[s] = holdValue;

		        }

		        else if(hold == tempValueLowest[s])
		        {
		        	tempValueLowest[s] = hold;
		        	lowestPriceDay[s] = holdValue;
		        }

		    }
		}
		//------------------LOWEST PRICE DONE



		//-----------------FINDING AVERAGE PER MONTH---------------------------
		
		if(holdValue.substr(0,1) == "1" && holdValue.substr(1,1) != "0"  &&  holdValue.substr(1,1) != "1" && holdValue.substr(1,1) != "2" )
		{
			avgMonthly[0] += hold;
			avgM[0]++;
		}

		if(holdValue.substr(0,1) == "2")
		{
			avgMonthly[1] += hold;
			avgM[1]++;
		}

		if(holdValue.substr(0,1) == "3")
		{
			avgMonthly[2] += hold;
			avgM[2]++;
		}

		if(holdValue.substr(0,1) == "4")
		{
			avgMonthly[3] += hold;
			avgM[3]++;
		}

		if(holdValue.substr(0,1) == "5")
		{
			avgMonthly[4] += hold;
			avgM[4]++;
		}

		if(holdValue.substr(0,1) == "6")
		{
			avgMonthly[5] += hold;
			avgM[5]++;
		}

		if(holdValue.substr(0,1) == "7")
		{
			avgMonthly[6] += hold;
			avgM[6]++;
		}

		if(holdValue.substr(0,1) == "8")
		{
			avgMonthly[7] += hold;
			avgM[7]++;
		}
		if(holdValue.substr(0,1) == "9")
		{
			avgMonthly[8] += hold;
			avgM[8]++;
		}
		
		if(holdValue.substr(0, 2) == "10")
		{
			avgMonthly[9] += hold;
			avgM[9]++;
		}

		if(holdValue.substr(0,2) == "11")
		{
			avgMonthly[10] += hold;
			avgM[10]++;
		}

		if(holdValue.substr(0,2) == "12")
		{
			avgMonthly[11] += hold;
			avgM[11]++;
		}

		//------------------END OF FINDING MONTHLY AVERAGE---------------------
		
		list.push_back(stockData[i - 2]); //pushes into vector list all the data, which is the high price and date
		
 	
	}

	cout << "Highest Price Per Year: " << endl;
	for(int i = 0; i <= lengthYears; i++) //storing avg price per year
	{
			
			highestP.push_back(highestPrice[i]);

			if(highestPrice[i] > 0)
			{
				cout << highestP[i] << " " << highestPriceDay[i] <<  endl;
			}

	}
	
	cout << endl;


	cout << "Lowest Price Per Year: " << endl;
	for(int i = 0; i <= lengthYears; i++) //storing avg price per year
	{
			
			lowestP.push_back(tempValueLowest[i]);

			if(tempValueLowest[i] > 0)
			{
				cout << lowestP[i] << " " << lowestPriceDay[i] << endl;
			}


	}
	
	cout << endl;


	cout << "Yearly Average, in Order: " << endl;
	for(int i = 0; i <= lengthYears; i++) //storing avg price per year
	{
			
			average[i] = average[i]/avg[i];
			yearAvg.push_back(average[i]);

			if(avg[i] != 0)
			{
				cout << yearAvg[i] << endl;
			}


	}
	cout << endl;


	cout << "Monthly Average in Order: " << endl;
	for(int i = 0; i <= 11; i++) //storing avg price per month
	{
		
		avgMonthly[i] = avgMonthly[i]/avgM[i];
		monthlyAvg.push_back(avgMonthly[i]);
		cout << monthlyAvg[i] << endl;
	}
	cout << endl;


	//------------PRINT IN ASCENDING ORDER--------------------
	
	outFile.open("sortPriceAscend.txt");
	sort(list.begin(), list.end());

    for(it = list.begin(); it != list.end(); ++it) 
    {

      it->output(outFile); // For each friend, print out their info

    }

   	 outFile.close();
   	 
    
   	 //-------------PRINT IN DESCENDING ORDER----------------------
	outFile.open("sortPriceDescend.txt");
    sort(list.rbegin(), list.rend());

    for ( it = list.begin(); it != list.end(); ++it ) 
    {
      // For each friend, print out their info
      it->output(outFile);
    }
   

	return 0;
}

Stock::Stock()
{
	//intentionally blank
}


double Stock::getHighPrice()
{
	return highPrice;
}


string Stock::getDate()
{
	return date;
}

bool operator < (const Stock& object1, const Stock& object2) //uses the overloaded operator to compare two objects
{
	return (object1.highPrice < object2.highPrice);
}

void Stock::setHighPrice(double HighPrice)
{ 
	highPrice = HighPrice;
}

void Stock::setDate(string Date)
{ 
	date = Date;
}


void Stock::output(ofstream& outfile)
{

		outfile << date << "	" << highPrice << setprecision(10) << endl;
}

void wordOutFile(string fileArray[]) //creates an array to store text file of words
{

	ifstream inFile;
	inFile.open("StockPrices.csv");


	if(inFile.good())
	{
		for(int i = 0; i < MAX_SIZE; i++)
		{
			inFile >> fileArray[i];
		}
	}
	
	inFile.close();
		
}