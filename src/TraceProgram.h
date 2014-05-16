#ifndef TRACEPROGRAM_H
#define TRACEPROGRAM_H

#include "OutputBitmap.h"
#include <string>
#include <list>
#include "Primitive.h"
#include "common.h"
#include "Raytracer.h"

using namespace std;

class TraceProgram
{
	private:
		unsigned int width;
		unsigned int height;
		string filename;
		bool debug;
		Raytracer* tracer;

		OutputBitmap* canvas;

		bool initCanvas();
		bool hasEnding(string haystack, string needle);
		void loadTestScene();

	public:
		static const unsigned int DEFAULT_WIDTH;
		static const unsigned int DEFAULT_HEIGHT;

		TraceProgram();
		~TraceProgram();

		void parseArguments(int argc, char** argv);

		bool init();
		void trace();
		bool write();
};

#endif
