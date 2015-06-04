#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include "../Application/Context.h"
namespace Framework
{
	class Utils
	{
	private:
		static unsigned int nextId;
	public:
		static unsigned int getNextId()
		{
			return nextId++;
		}

		static std::string getPathOfFile(std::string filePath)
		{
			unsigned found = filePath.find_last_of("/\\");
			if (found == std::string::npos)
				return "";
			else
				return filePath.substr(0, found);
		}

		static std::string getNameOfFile(std::string filePath)
		{
			unsigned found = filePath.find_last_of("/\\");
			if (found == std::string::npos)
				return filePath;
			else
				return filePath.substr(found + 1);
		}
		static std::string getNameWithoutExt(std::string filePath)
		{
			std::string nameOffile = getNameOfFile(filePath);
			unsigned found = nameOffile.find_first_of(".");
			if (found == std::string::npos)
				return nameOffile;
			else
				return nameOffile.substr(0, found);
		}
		static bool isPath(std::string filePath)
		{
			unsigned found = filePath.find_first_of("/\\");
			if (found == std::string::npos)
				return false;
			else
				return true;
		}

		/*
		* CLIP ALGORITHMS
		* http://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
		*
		*/



		typedef int OutCode;
		static const int INSIDE = 0; // 0000
		static const int LEFT = 1;   // 0001
		static const int RIGHT = 2;  // 0010
		static const int BOTTOM = 4; // 0100
		static const int TOP = 8;    // 1000

		// Compute the bit code for a point (x, y) using the clip rectangle
		// bounded diagonally by (xmin, ymin), and (xmax, ymax)

		// ASSUME THAT xmax, xmin, ymax and ymin are global constants.
		static OutCode ComputeOutCode(double x, double y, double xmin, double xmax, double ymin, double ymax)
		{
			OutCode code;

			code = INSIDE;			//initialised as being inside of clip window

			if (x < xmin)           // to the left of clip window
				code |= LEFT;
			else if (x > xmax)      // to the right of clip window
				code |= RIGHT;
			if (y < ymin)           // below the clip window
				code |= BOTTOM;
			else if (y > ymax)      // above the clip window
				code |= TOP;

			return code;
		}

		// Cohen–Sutherland clipping algorithm clips a line from
		// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with 
		// diagonal from (xmin, ymin) to (xmax, ymax).
		static RECT CohenSutherlandLineClip(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax)
		{
			RECT clip;
			clip.left = -1; clip.right = -1; clip.top = -1; clip.bottom = -1;

			// compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
			OutCode outcode0 = ComputeOutCode(x0, y0, xmin, xmax, ymin, ymax);
			OutCode outcode1 = ComputeOutCode(x1, y1, xmin, xmax, ymin, ymax);

			bool accept = false;
			while (true)
			{
				if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
					accept = true;
					break;
				}
				else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
					break;
				}
				else
				{
					// failed both tests, so calculate the line segment to clip
					// from an outside point to an intersection with clip edge
					double x, y;

					// At least one endpoint is outside the clip rectangle; pick it.
					OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

					// Now find the intersection point;
					// use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
					if (outcodeOut & TOP) {           // point is above the clip rectangle
						x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
						y = ymax;
					}
					else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
						x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
						y = ymin;
					}
					else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
						y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
						x = xmax;
					}
					else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
						y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
						x = xmin;
					}

					// Now we move outside point to intersection point to clip
					// and get ready for next pass.
					if (outcodeOut == outcode0) {
						x0 = x;
						y0 = y;
						outcode0 = ComputeOutCode(x0, y0, xmin, xmax, ymin, ymax);
					}
					else {
						x1 = x;
						y1 = y;
						outcode1 = ComputeOutCode(x1, y1, xmin, xmax, ymin, ymax);
					}
				}
			}
			if (accept)
			{
				// Following functions are left for implementation by user based on
				// their platform (OpenGL/graphics.h etc.)
				//DrawRectangle(xmin, ymin, xmax, ymax);
				//LineSegment(x0, y0, x1, y1);
				clip.left = x0;
				clip.right = x1;
				clip.top = y0;
				clip.bottom = y1;
				return clip;
			}
			return clip;
		}

		static RECT RectClip(RECT bound1, RECT bound2)
		{
			RECT clip = CohenSutherlandLineClip(bound1.left, bound1.top, bound1.right, bound1.bottom,
				bound2.left, bound2.right, bound2.top, bound2.bottom);
			return clip;
		}
	};
}

#endif