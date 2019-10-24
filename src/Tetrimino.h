#ifndef TETRIMINO_H_
#define TETRIMINO_H_


#include <exception>


enum class TetriminoBlock : unsigned char {
	EMPTY = 0,
	I, O, T, S, Z, J, L
};

enum class TetriminoShape : unsigned char {
	INVALID = 0,
	I, O, T, S, Z, J, L
};


constexpr char I_SHAPE_ARRAY[] = {
	"...."
	"####"
	"...."
	"...."

	"..#."
	"..#."
	"..#."
	"..#."

	"...."
	"...."
	"####"
	"...."

	".#.."
	".#.."
	".#.."
	".#.."
};

constexpr char O_SHAPE_ARRAY[] = {
	".##."
	".##."
	"...."
	"...."

	".##."
	".##."
	"...."
	"...."

	".##."
	".##."
	"...."
	"...."

	".##."
	".##."
	"...."
	"...."
};

constexpr char T_SHAPE_ARRAY[] = {
	".#.."
	"###."
	"...."
	"...."

	".#.."
	".##."
	".#.."
	"...."

	"...."
	"###."
	".#.."
	"...."

	".#.."
	"##.."
	".#.."
	"...."
};

constexpr char S_SHAPE_ARRAY[] = {
	".##."
	"##.."
	"...."
	"...."

	".#.."
	".##."
	"..#."
	"...."

	"...."
	".##."
	"##.."
	"...."

	"#..."
	"##.."
	".#.."
	"...."
};

constexpr char Z_SHAPE_ARRAY[] = {
	"##.."
	".##."
	"...."
	"...."

	"..#."
	".##."
	".#.."
	"...."

	"...."
	"##.."
	".##."
	"...."

	".#.."
	"##.."
	"#..."
	"...."
};

constexpr char J_SHAPE_ARRAY[] = {
	"#..."
	"###."
	"...."
	"...."

	".##."
	".#.."
	".#.."
	"...."

	"...."
	"###."
	"..#."
	"...."

	".#.."
	".#.."
	"##.."
	"...."
};

constexpr char L_SHAPE_ARRAY[] = {
	"..#."
	"###."
	"...."
	"...."

	".#.."
	".#.."
	".##."
	"...."

	"...."
	"###."
	"#..."
	"...."

	"##.."
	".#.."
	".#.."
	"...."
};


inline TetriminoBlock getTetriminoRasterShape(TetriminoShape shape, int rotation, int y, int x) {
	if (shape == TetriminoShape::I)
		return I_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::I : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::O)
		return O_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::O : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::T)
		return T_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::T : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::S)
		return S_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::S : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::Z)
		return Z_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::Z : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::J)
		return J_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::J : TetriminoBlock::EMPTY;
	if (shape == TetriminoShape::L)
		return L_SHAPE_ARRAY[rotation * 16 + (3 - y) * 4 + x] == '#' ? TetriminoBlock::L : TetriminoBlock::EMPTY;

	throw std::exception("Tried to get invalid TetriminoShape's raster shape");
}


#endif