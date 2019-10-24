#include "TetriminoGenerator.h"

#include <random>


TetriminoGenerator::TetriminoGenerator() {
}


TetriminoShape TetriminoGenerator::next() {
	// 남은 조각이 없다면, 새로운 조각들을 생성
	if (_nextPieces.empty())
		generateNextPieces();

	// 제일 앞에 있는 조각을 빼줌
	TetriminoShape nowShape = _nextPieces[0];

	// 제일 앞의 조각을 삭제
	_nextPieces.erase(_nextPieces.begin());

	// 리턴
	return nowShape;
}

std::array<TetriminoShape, 6> TetriminoGenerator::peek() {
	std::array<TetriminoShape, 6> ret;
	
	// 남은 조각이 6개 미만이라면, 새로운 조각들을 생성
	if (_nextPieces.size() < 6)
		generateNextPieces();

	// 리턴할 변수로 내용을 복사
	std::copy(_nextPieces.begin(), _nextPieces.begin() + 6, ret.begin());

	// 리턴
	return ret;
}

void TetriminoGenerator::generateNextPieces() {
	// 새로운 조각을 생성
	std::array<TetriminoShape, 7> newPieces;

	// [0, 7) 범위에서 조각들을 순서대로 지정
	for (int i = 0; i < 7; i++)
		newPieces[i] = (TetriminoShape) i;

	// 조각들을 섞어줌
	// (구현 필요)

	// 조각들을 큐에 넣어줌
	auto endIterator = _nextPieces.end();
	_nextPieces.insert(endIterator, newPieces.begin(), newPieces.end());
}