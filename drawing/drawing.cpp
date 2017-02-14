// drawing.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <algorithm>

class Figure
{
public:
	Figure(const int nrow, const int ncol, const int color) : nrow_(nrow), ncol_(ncol), nelem_(ncol * nrow)
	{
		storage = new int[nelem_];
		for (int ii=0; ii < nelem_; ++ii)
		{
			storage[ii] = color;
		}
	}

	~Figure()
	{
		// delete the heap
		delete storage;
	}

	void Print() const
	{
		// reverse order to get a nicer representation
		for (int jj = nrow_ - 1; jj >= 0; --jj)
		{			
			for (int ii = 0; ii<ncol_; ++ii)
			{
				// coordinate conversion
				int zz;
				XY2Z(ii, jj, zz);
				// print the point
				std::cout << storage[zz];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void DrawPoint(const int xx, const int yy, const int color)
	{
		// coordinate conversion
		int zz;
		XY2Z(xx, yy, zz);
		// check
		if (zz<0 || zz>=nelem_)
		{
			std::cout << "The point is out of the figure. Nothing happens.\n";
			return;
		}
		// write the point
		storage[zz] = color;
	}

	void DrawRectangle(int x1, int y1, int x2, int y2, const int color)
	{
		// sorting
		SortAb(x2, x1);
		SortAb(y2, y1);

		// resizing if necessary
		if (x1 < 0) { x1 = 0; }
		if (y1 < 0) { y1 = 0; }
		if (x2 >= ncol_) { x2 = ncol_-1; }
		if (y2 >= nrow_) { y2 = nrow_-1; }

		for (int ii = x1; ii <= x2; ++ii)
		{
			for (int jj = y1; jj <= y2; ++jj)
			{
				// coordinate conversion
				int zz;
				XY2Z(ii, jj, zz);
				// write the point
				storage[zz] = color;
			}
		}
	}

	void DrawLine(int x1, int y1,int x2,int y2, const int color)
	{
		// resolve the point case
		if (x1 == x2 && y1 == y2) { DrawPoint(x1, y1, color); return; }

		// checks
		int z1;
		XY2Z(x1, y1, z1);		
		if (z1 < 0 || z1 >= nelem_) { std::cout << "Point 1 is out of the figure. Nothing happens.\n"; return; }
		int z2;
		XY2Z(x2, y2, z2);
		if (z2 < 0 || z2 >= nelem_) { std::cout << "Point 2 is out of the figure. Nothing happens.\n"; return; }

		int deltaXabs = std::abs(x1 - x2);
		int deltaYabs = std::abs(y1 - y2);

		if (deltaXabs >= deltaYabs)
		{
			// sort points
			SortAbCd(x2, x1, y2, y1);
			const int deltaX = x2 - x1;
			const int deltaY = y2 - y1;

			for (int ii = x1; ii <= x2; ++ii)
			{
				const int jj = FX2Y(x1, y1, deltaX, deltaY, ii);
				// coordinate conversion
				int zz;
				XY2Z(ii, jj, zz);
				// write the point
				storage[zz] = color;
			}
		}
		else
		{
			// sort points
			SortAbCd(y2, y1, x2, x1);
			const int deltaX = x2 - x1;
			const int deltaY = y2 - y1;

			for (int jj = y1; jj <= y2; ++jj)
			{
				const int ii = FX2Y(y1, x1, deltaY, deltaX, jj);
				// coordinate conversion
				int zz;
				XY2Z(ii, jj, zz);
				// write the point
				storage[zz] = color;
			}
		}
	}

private:

	inline void XY2Z(const int X, const int Y, int& Z) const { Z = ncol_ * Y + X; }

	inline void Z2XY(const int Z, int& X, int& Y) const { X = Z % ncol_; Y = Z / ncol_; }

	// sort a and b. At the end A is always >= b
	inline void SortAb(int& A, int& b) { if (A < b) { int temp = A; A = b; b = temp; } }

	// sort A, b, C, d based on A and b
	inline void SortAbCd(int& A, int& b, int& C, int& d) { if (A < b) {int temp = A; A = b; b = temp; temp = C; C = d; d = temp; } }

	// determine the jj index of a discrete line y = f(x). x1 < x2 is a requirement
	inline int FX2Y(const int x1, const int y1, const int deltaX, const int deltaY, const int ii) { return (deltaY * (ii - x1 + (deltaX+1)/(deltaY+1) -1) + deltaX * y1) / deltaX; }

	// --- variables --- //
	int* storage;
	const int nrow_;
	const int ncol_;
	const int nelem_;
};

int main()
{
	auto figp = std::make_unique<Figure>(10, 10, 0);

	figp->DrawLine(9, 9, 0, 0, 1);
	figp->Print();

	std::cin.get();
	return 0;
}
