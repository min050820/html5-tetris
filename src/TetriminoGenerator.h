#ifndef TETRIMINO_GENERATOR_H_
#define TETRIMINO_GENERATOR_H_


#include <array>
#include <random>

#include "Tetrimino.h"


class TetriminoGenerator {
public:
	TetriminoGenerator();
	TetriminoShape next();
	std::array<TetriminoShape, 6> peek();

private:
	void generateNextPieces();

private:
	std::vector<TetriminoShape> _nextPieces;
	std::default_random_engine _random;
};


#endif