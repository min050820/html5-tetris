#include "TetriminoGenerator.h"

#include <random>


TetriminoGenerator::TetriminoGenerator() {
}


TetriminoShape TetriminoGenerator::next() {
	// ���� ������ ���ٸ�, ���ο� �������� ����
	if (_nextPieces.empty())
		generateNextPieces();

	// ���� �տ� �ִ� ������ ����
	TetriminoShape nowShape = _nextPieces[0];

	// ���� ���� ������ ����
	_nextPieces.erase(_nextPieces.begin());

	// ����
	return nowShape;
}

std::array<TetriminoShape, 6> TetriminoGenerator::peek() {
	std::array<TetriminoShape, 6> ret;
	
	// ���� ������ 6�� �̸��̶��, ���ο� �������� ����
	if (_nextPieces.size() < 6)
		generateNextPieces();

	// ������ ������ ������ ����
	std::copy(_nextPieces.begin(), _nextPieces.begin() + 6, ret.begin());

	// ����
	return ret;
}

void TetriminoGenerator::generateNextPieces() {
	// ���ο� ������ ����
	std::array<TetriminoShape, 7> newPieces;

	// [0, 7) �������� �������� ������� ����
	for (int i = 0; i < 7; i++)
		newPieces[i] = (TetriminoShape) i;

	// �������� ������
	// (���� �ʿ�)

	// �������� ť�� �־���
	auto endIterator = _nextPieces.end();
	_nextPieces.insert(endIterator, newPieces.begin(), newPieces.end());
}