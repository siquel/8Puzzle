#include "DecisionTree.h"
#include <algorithm>
int main() {
	NPuzzleSolver solver;


	std::cout << solver.solveUsingBFS() << std::endl;
	std::cout << "move count " << solver.getSolution().size() << std::endl;;

	auto vec = solver.getSolution();
	std::for_each(vec.begin(), vec.end(), [&solver](node_bfs& n) {
		solver.print(n.board);
		std::cout << std::endl;
	});
	return 0;
}