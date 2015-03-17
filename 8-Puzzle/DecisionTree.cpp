#include "DecisionTree.h"

struct board NPuzzleSolver::create() {
	struct board board;
	board.cells[0][0] = 1;
	board.cells[0][1] = 2;
	board.cells[0][2] = 3;
	board.cells[1][0] = 4;
	board.cells[1][1] = 5;
	board.cells[1][2] = 6;
	board.cells[2][0] = 7;
	board.cells[2][1] = 8; 
	board.cells[2][2] = 0;// empty
	for (size_t i = 0; i < 15; i++) {
		if (i % 4 == 0) {
			if (canMove(board, 1, 0)) {
				board = move(board, 1, 0);
			}
			else if (canMove(board, -1, 0)) {
				board = move(board, -1, 0);
			}
		}
		else {
			if (canMove(board, 0, 1)) {
				board = move(board, 0, 1);
			}
			else if (canMove(board, 0, -1)) {
				board = move(board, 0, -1);
			}
		}
	}
	return board;
}

bool NPuzzleSolver::solve() {
	startNode.n = 0;
	startNode.board = create();
	moveCount = 0;
	bool solved = solve(startNode, 0);
	return solved;
}
void NPuzzleSolver::print(struct board& board) {
	for (size_t y = 0; y < 3; y++) {
		std::cout << "|";
		for (size_t x = 0; x < 3; x++) {
			std::cout << board.cells[y][x] << "|";
		}
		std::cout << std::endl;
	}
}
bool NPuzzleSolver::solve(node_t& node, int depth) {
	static int jee = 0;
	if (depth > MaxDepth) return false;

	if (isSolved(node.board)) {
		solution.push_back(node);
		return true;
	}

	// legal moves
	// left
	if (canMove(node.board, 0, -1)) {
		node_t p;
		p.n = &node;
		p.board = move(node.board, 0, -1);
		if (solve(p, depth + 1)) {
			solution.push_back(p);
			std::cout << jee++ << std::endl;
			print(p.board);
			return true;
		}
	} 
	// right
	if (canMove(node.board, 0, 1)) {
		node_t p ;
		p.n = &node;
		p.board = move(node.board, 0, 1);
		if (solve(p, depth + 1)) {
			solution.push_back(p);
			std::cout << jee++ << std::endl;
			print(p.board);
			return true;
		}
	}
	// up
	if (canMove(node.board, -1, 0)) {
		node_t p;
		p.n = &node;
		p.board = move(node.board, -1, 0);
		if (solve(p, depth + 1)) {
			solution.push_back(p);
			std::cout << jee++ << std::endl;
			print(p.board);
			return true;
		}
	}
	// down
	if (canMove(node.board, 1, 0)) {
		node_t p;
		p.n = &node;
		p.board = move(node.board, 1, 0);
		if (solve(p, depth + 1)) {
			solution.push_back(p);
			std::cout << jee++ << std::endl;
			print(p.board);
			return true;
		}
	}
	return false;
}

struct board NPuzzleSolver::move(struct board& board, int ydir, int xdir) {
	struct board b = board;
	int x, y;
	findEmpty(board, &x, &y);

	int x1 = x + xdir;
	int y1 = y + ydir;
	int temp = board.cells[y1][x1];
	b.cells[y][x] = temp;
	b.cells[y1][x1] = 0;
	return b;
}

bool NPuzzleSolver::canMove(struct board& board, int ydir, int xdir) {
	int x1, y1;
	findEmpty(board, &x1, &y1);
	int x = x1 + xdir;
	int y = y1 + ydir;
	if (x < 0 || x >= 3) return false;
	if (y < 0 || y >= 3) return false;
	return true;
}

void NPuzzleSolver::findEmpty(struct board& board, int* x, int* y) {
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			if (!board.cells[i][j]) {
				*y = i;
				*x = j;
				return;
			}
		}
	}
}

bool NPuzzleSolver::isSolved(struct board& board) {
	for (size_t y = 0, a = 1; y < 3; y++) {
		for (size_t x = 0; x < 3 && a <= 8; x++) {
			if (board.cells[y][x] != a++)
				return false;
		}
	}
	return true;
}

bool NPuzzleSolver::solveUsingBFS() {
	node_bfs startNode;
	startNode.n = 0;
	startNode.board = create();
	openList.push_back(startNode);
	
	while (openList.size() > 0) {
		node_bfs node = openList[0];
		openList.erase(openList.begin());
		closedList.push_back(node);
		if (isSolved(node.board)) {
			return true;
		}
		size_t index = closedList.size() - 1;
		// up
		if (canMove(node.board, -1, 0)) {
			openList.push_back(node_bfs{ index, move(node.board, -1, 0) });
		}
		// down
		if (canMove(node.board, 1, 0)) {
			openList.push_back(node_bfs{ index, move(node.board, 1, 0) });
		}
		// left
		if (canMove(node.board, 0, -1)) {
			openList.push_back(node_bfs{ index, move(node.board, 0, -1) });
		}
		//right
		if (canMove(node.board, 0, 1)) {
			openList.push_back(node_bfs{ index, move(node.board, 0, 1) });
		}
	}
	return false;
}

std::vector<node_bfs> NPuzzleSolver::getSolution() {
	node_bfs* node = &closedList.back();
	std::vector<node_bfs> solution;
	solution.push_back(*node);
	while (node->n) {
		node = &closedList[node->n];
		solution.push_back(*node);
	}
	return solution;
}