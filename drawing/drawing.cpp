// drawing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <algorithm>





class Figure
{
public:
	Figure(int nrow = 30, int ncol = 40) : nrow_(nrow), ncol_(ncol)
	{


		fig_.resize(nrow, std::vector<int>(ncol,0));
	}

	void Print() const
	{
		for (auto vecRow : fig_)
		{
			for (auto elem : vecRow)
			{				
				std::cout << elem << ' ';
			}
			std::cout << std::endl;
		}
	}

	void CreateRect(int color, int x1, int y1, int x2, int y2)
	{
		// checks
		if (x1 < 0 || x1 > ncol_ || x2 < 0 || x2 > ncol_ || y1 < 0 || y1 > nrow_ || y2 < 0 || y2 > nrow_)
		{
			std::cout << "points are out of reach. Nothing happens\n";
			return;
		}

		std::vector<int> XX = { x1, x2 };
		std::vector<int> YY = { y1, y2 };
		std::sort(XX.begin(), XX.end());
		std::sort(YY.begin(), YY.end());


		for (int jj = XX[0]; jj <= XX[1]; ++jj)
		{
			for (int ii = YY[0]; ii <= YY[1]; ++ii)
			{
				(fig_.at(ii)).at(jj) = color;
			}
		}
	}


	void CreateLine(int color, int x1, int y1, int x2, int y2)
	{
		// checks
		if (x1 < 0 || x1 > ncol_ || x2 < 0 || x2 > ncol_ || y1 < 0 || y1 > nrow_ || y2 < 0 || y2 > nrow_)
		{
			std::cout << "points are out of reach. Nothing happens\n";
			return;
		}

		int distX = std::abs(x1 - x2);
		int distY = std::abs(y1 - y2);

		if (distX == 0 && distY == 0)
		{
			fig_.at(y1).at(x1) = color;
		}
		else if (distY > distX)
		{
			int incr = 1;
			if (y2 < y1)
			{
				incr = -1;
			}


			for (int jj = y1; jj != y2 + incr; jj += incr)
			{
				const int ii = X2Y(jj, y1, x1, y2, x2);
				fig_.at(jj).at(ii) = color;
			}
		}
		else
		{
			int incr = 1;
			if (x2 < x1)
			{
				incr = -1;
			}

			for (int ii = x1; ii != x2 + incr; ii += incr)
			{
				const int jj = X2Y(ii, x1, y1, x2, y2);
				fig_.at(jj).at(ii) = color;
			}

		}

	}


private:

	int X2Y(const int &xx, const int &x1, const int &y1, const int &x2, const int &y2) const
	{
		const double alpha = ((double) (y2 - y1)) / (x2 - x1);
		const double q = y1 - x1 * alpha;
		return std::round(alpha * xx + q);
	}

	std::vector<std::vector<int> > fig_;
	const int nrow_;
	const int ncol_;
};

int main()
{
	char conti = 'y';

	auto figp = std::make_unique<Figure>(10, 10);
	figp->CreateLine(1, 1, 1, 5,7);
	figp->CreateRect(2, 7,1, 9, 3);

	while (conti == 'y')
	{

		figp->Print();

		std::cout << "Do you want to continue? [y/anything else, please a char :P] ";
		std::cin >> conti;
	}
    return 0;
}


