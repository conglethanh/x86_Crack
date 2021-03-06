// 3.1_Keygen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include "QInt.h"
#include <stack>

#define DOWN 0
#define UP 1
#define LEFT 2
#define RIGHT 3
#define ERR 100

string getStringMove_temp(int direction, int numMove)
{
	if (numMove < 1 || numMove>4)return "";
	string res = "";
	switch (direction)
	{
	case DOWN:
		if (numMove == 1)res = "0";
		else if (numMove == 2)res = "4";
		else if (numMove == 3) res = "8";
		else if (numMove == 4)res = "C";
		break;
	case UP:
		if (numMove == 1)res = "1";
		else if (numMove == 2)res = "5";
		else if (numMove == 3) res = "9";
		else if (numMove == 4)res = "D";
		break;
	case LEFT:
		if (numMove == 1)res = "2";
		else if (numMove == 2)res = "6";
		else if (numMove == 3) res = "A";
		else if (numMove == 4)res = "E";
		break;
	case RIGHT:
		if (numMove == 1)res = "3";
		else if (numMove == 2)res = "7";
		else if (numMove == 3) res = "B";
		else if (numMove == 4)res = "F";
		break;
	default:break;
	}
	return res;
}

string getStringMove(int direction, int numMove)
{
	if (direction < 0 || direction>3)return "";
	if (numMove < 1)return "";
	string res = "";
	while (numMove > 4)
	{
		res += getStringMove_temp(direction, 4);
		numMove -= 4;
	}
	res += getStringMove_temp(direction, numMove);
	return res;
}
string changeToKey(string s)
{
	string res = "";
	int i, j;
	while(s.length()>0)
	{
		i = 0;
		char t = s[0];
		for (j = i + 1; j < s.length(); j++)
		{
			if (s[j] != t)
			{
				break;
			}
		}
		int dir = t - 48;
		string r = s.substr(i, j);
		s.erase(i, j);
		res += getStringMove(dir, r.length());
	}
	return res;
}
string optimize(string s)
{
	if (s.length() < 31)return s;
	for (int i = 0; i < s.length(); i++)
	{
		string temp = s.substr(i, 31);
		if (temp == "0000000000000002111111111111111")
		{
			s.insert(i, "2");
			s.erase(i + 1, 31);
			i++;
		}
		else if (temp == "0000000000000003111111111111111")
		{
			s.insert(i, "3");
			s.erase(i + 1, 31);
			i++;
		}
		else if (temp == "1111111111111112000000000000000")
		{
			s.insert(i, "2");
			s.erase(i + 1, 31);
			i++;
		}
		else if (temp == "1111111111111113000000000000000")
		{
			s.insert(i, "3");
			s.erase(i + 1, 31);
			i++;
		}
	}
	return s;
}
//61626364->64636261
string dump(string s)
{
	string res = "";
	while (s.length() < 8)
	{
		s = "0" + s;
	}
	int n = s.length();
	for (int i = 0; i < n / 2; i++)
	{
		res += s.substr(s.length() - 2, 2);
		s.erase(s.length() - 2, 2);
	}
	return res;
}

string textToHex(string text)
{
	stringstream ss;
	for (int i = 0; i < text.length(); i++)
	{
		ss << std::hex << (int)text[i];
	}
	string res = ss.str();
	for (int i = 0; i < res.length(); i++)
	{
		if (res[i] >= 'a'&&res[i] <= 'f')
		{
			res[i] = res[i] - 32;
		}
	}
	return res;
}
string getLastChars(string s, int num) //num = số ký tự biểu diễn, số ô = 2*num, số bit=8*num
{
	//num=1, lấy 2 ô
	string res = "";
	int n = s.length();
	while (s.length() < 8)
	{
		s = "0" + s;
	}
	res = s.substr(s.length() - 2 * num, 2 * num);
	return res;
}
string getFirstChars(string s, int num)
{
	string res = "";
	int n = s.length();
	while (s.length() < 8)
	{
		s = "0" + s;
	}
	res = s.substr(0, 2 * num);
	return res;
}

struct Point2D
{
	int x;
	int y;
	Point2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	Point2D()
	{
		this->x = 0;
		this->y = 0;
	}
	Point2D& operator=(const Point2D& a)
	{
		this->x = a.x;
		this->y = a.y;
		return *this;
	}
};
class Keygen
{
private:
	string name; //numFoods = name.lenght()
	string key;
	char **grid;
	Point2D snake; //99
	
	Point2D dest; //DD
	vector<Point2D> tempDest;
	vector<Point2D> foods; //CC

	
	vector<int> dir;
	void generate()
	{
		vector<string> temp;
		for (int i = 0; i < 256; i++)
		{
			temp.push_back("00");
		}
		string s = textToHex(name);
		QInt x("00", "16");
		QInt y("00", "16");
		string AL = "", DL = "00";
		for (int i = 0; i < 2 * name.length(); i += 2)//lấy 1 lần 2 ô ~ 1 biểu diễn ký tự
		{
			AL = s.substr(i, 2);
			x.setData(AL, "16");
			y.setData(DL, "16");
			DL = (y + x).toString("16");
			DL = getLastChars(DL, 1);
		}
		//string ecx = "00000000";
		int pos;
		for (int i = 0; i < 2 * name.length(); i += 2)
		{
			AL = s.substr(i, 2);
			x.setData(AL, "16");
			y.setData(DL, "16");
			AL = (x ^ y).toString("16");
			AL = getLastChars(AL, 1);

			Label0:
			x.setData(AL, "16");
			y.setData(DL, "16");
			DL = (y - x).toString("16");
			DL = getLastChars(DL, 1);

			x.setData(AL, "16");
			pos = atoi(x.toString("10").c_str());

			if (temp[pos] == "CC")
			{
				y.setData(DL, "16");
				x.setData("01", "16");
				DL = (y - x).toString("16");
				DL = getLastChars(DL, 1);
				goto Label0;
			}
			else temp[pos] = "CC";
		}
		x.setData(AL, "16");
		y.setData(DL, "16");
		DL = getLastChars((y^x).toString("16"), 1);

	Label1:
		x.setData(AL, "16");
		y.setData(DL, "16");
		AL = getLastChars((x - y).toString("16"), 1);
		x.setData(AL, "16");
		pos = atoi(x.toString("10").c_str());

		if (temp[pos] == "CC")
		{
			y.setData(DL, "16");
			x.setData("01", "16");
			DL = getLastChars((y - x).toString("16"), 1);
			goto Label1;
		}

	
		x.setData(AL, "16");
		pos = atoi(x.toString("10").c_str());

		temp[pos] = "DD";
		AL = DL;

	Label2:
		x.setData(AL, "16");
		pos = atoi(x.toString("10").c_str());

		if (temp[pos] == "CC" || temp[pos] == "DD")
		{
			x.setData(AL, "16");
			y.setData("01", "16");
			AL = getLastChars((x - y).toString("16"), 1);
			goto Label2;
		}

		x.setData(AL, "16");
		pos = atoi(x.toString("10").c_str());

		temp[pos] = "99";

		int i = 0, j = 0;
		for (int k = 0; k < 256; k++)
		{
			/*if (k % 16 == 0)cout << endl;
			cout << temp[k] << " ";*/
			
			if (temp[k] == "DD")
			{
				dest.x = i;
				dest.y = j;
				grid[i][j] = 'D';
			}
			if (temp[k] == "CC")
			{
				Point2D food;
				food.x = i;
				food.y = j;
				foods.push_back(food);
				grid[i][j] = 'C';
			}
			if (temp[k] == "99")
			{
				snake.x = i;
				snake.y = j;
				grid[i][j] = '9';
			}
			j++;
			if ((k+1) % 16 == 0)
			{
				j = 0;
				i++;
			}
		}
	}
public:
	vector<Point2D> tempSnake;
	vector<Point2D> pos;
	vector<Point2D> tempFoods;
	Keygen(string name)
	{
		this->name = name;
		this->key = "";
		grid = new char*[16];
		for (int i = 0; i < 16; i++)
		{
			grid[i] = new char[16];
			for (int j = 0; j < 16; j++)
			{
				grid[i][j] = '0';//00
			}
		}
		generate();
		tempFoods = foods;
		tempDest.push_back(dest);
		tempSnake.push_back(snake);
	}
	~Keygen()
	{
		for (int i = 0; i < 16; i++)
		{
			delete[] grid[i];
			grid[i] = NULL;
		}
		delete[] grid;
		grid = NULL;
	}
	void printGrid()
	{
		for (int k = 0; k < 16; k++)
		{
			cout << 'F' << ' ';
		}
		cout << endl;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				cout << grid[i][j] << ' ';
			}
			cout << endl;
		}
		for (int k = 0; k < 16; k++)
		{
			cout << 'F' << ' ';
		}
	}
	void setGrid()
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				grid[i][j] = '0';
			}
		}
		for (int i = 0; i < tempFoods.size(); i++)
		{
			grid[tempFoods[i].x][tempFoods[i].y] = 'C';
		}
		grid[dest.x][dest.y] = 'D';
		grid[tempSnake[0].x][tempSnake[0].y] = '9';

	}
	void solve()
	{
		string tmp = "";
		string tmp2 = "";
		key = "";
		int countFoods = tempFoods.size();
		int n = 0;
		for (int k = 0; k < countFoods; k++)
		{
			
			if (solveGrid(tempSnake[0].x, tempSnake[0].y, 'C') == true)
			{
				n = tempSnake.size() + 1;
				tempSnake.clear();
				for (int i = 0; i < n; i++)
				{
					tempSnake.push_back(pos[i]);
				}
				pos.clear();
				setGrid();
				for (int i = key.length() - 1; i >= 0; i--)
				{
					//tmp += key[i];
					tmp2 += key[i];
				}
				tmp2 = optimize(tmp2);
				tmp += tmp2;
				tmp2 = "";
				key = "";
			}
		}
		//setGrid();
		if (solveGrid(tempSnake[0].x, tempSnake[0].y, 'D') == true)
		{
			n = tempSnake.size() + 1;
			tempSnake.clear();
			for (int i = 0; i < n; i++)
			{
				tempSnake.push_back(pos[i]);
			}
			pos.clear();
			setGrid();
			for (int i = key.length() - 1; i >= 0; i--)
			{
				//tmp += key[i];
				tmp2 += key[i];
			}
			tmp2 = optimize(tmp2);
			tmp += tmp2;
			tmp2 = "";
			key = "";
		}
		//setGrid();
		key = tmp;
	}
	string getKey()
	{
		solve();
		string res = changeToKey(key);
		if (tempFoods.size() > 0 || tempDest.size() == 1 || res.length() > 126)
		{
			return "unsolvable";
		}
		return res;
		//return key;
	}
	bool solveGrid(int x, int y, char dest)
	{
		if (x < 0 || x > 16 - 1 || y < 0 || y > 16 - 1) return false;
		if (grid[x][y]==dest)
		{
			int m = tempFoods.size();
			for (int i = 0; i < m; i++)
			{
				if (x == tempFoods[i].x&&y == tempFoods[i].y)
				{
					tempFoods.erase(tempFoods.begin()+i);
					break;
				}
			}
			if (x == tempDest[0].x&&y == tempDest[0].y)
			{
				tempDest.pop_back();
			}
			//grid[x][y] = '9';
		
			return true;
		}

		if (grid[x][y] != '0'&& grid[x][y] != '9') return false;
		for (int i = 1; i < tempSnake.size(); i++)
		{
			if (x == tempSnake[i].x&&y == tempSnake[i].y)
			{
				return false;
			}
		}

		grid[x][y] = '+';

		if (solveGrid(x - 1, y, dest) == true)
		{
			key += '1';
			pos.push_back(Point2D(x - 1, y));
			return true;
		}
		if (solveGrid(x + 1, y, dest) == true)
		{
			key += '0';
			pos.push_back(Point2D(x + 1, y));
			return true;
		}
		if (solveGrid(x, y + 1, dest) == true)
		{
			key += '3';
			pos.push_back(Point2D(x, y + 1));
			return true;
		}
		if (solveGrid(x, y - 1, dest) == true)
		{
			key += '2';
			pos.push_back(Point2D(x, y - 1));
			return true;
		}

		grid[x][y] = ' ';
		return false;
	}
};

int main()
{
	cout << "1612774 - 1612829 - 1612842" << endl;
	cout << "Keygen for 3.1" << endl;
	cout << "Nobody's perfect! You should input name with number of char < 10" << endl << endl;
	while (1)
	{
		string username;
		while (1)
		{
			fflush(stdin);
			cout << "Username: ";
			getline(cin, username);
			int n = username.length();
			if (n <= 9)break;
		}
		Keygen k(username);
		//k.printGrid();
		//cout << endl;
		cout << "Serial: " << k.getKey() << endl;
	}

	system("pause");
    return 0;
}

