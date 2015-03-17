#pragma once

#include <vector>
#include <ostream>
#include <iostream>
struct board {
	int cells[3][3];
};

struct node_t {
	struct node_t* n;
	board board;
};

struct node_bfs {
	size_t n;
	board board;
};

class NPuzzleSolver {
private:
	node_t startNode;
	size_t moveCount;
	struct board create();
	void findEmpty(struct board&, int*, int*);

	struct board move(struct board& board, int ydir, int xdir);
	bool solve(node_t& node,int depth);
	std::vector<node_t> solution;
public:
	static const int MaxDepth = 10;
	bool canMove(struct board& board, int ydir, int xdir);
	NPuzzleSolver(){
		create();
	}
	
	bool solve();
	~NPuzzleSolver() = default;
	size_t getMoveCount() {
		return solution.size();
	}
	bool isSolved(struct board&);
	void print(struct board& board);

	std::vector<node_bfs> openList;
	std::vector<node_bfs> closedList;
	bool solveUsingBFS();

	std::vector<node_bfs> getSolution();
	
};