#include <iostream>
#include <algorithm>
#include <limits>

int main() {

	int A = 29; //Amount to make change for
	int v[] = {1,3,7,12}; //Denominations

	int m[A+1]; //min amount of coins per level of A
	int n = sizeof(v)/sizeof(v[0]); //how many denominations
	int c[A+1][n]; //2D array of how many of each type to use

	for (int i = 0; i < n; i++) {
		c[0][i] = 0; //Init first row as zeros
	}

	m[0] = 0;

	int min, candidate, candidate_index,
		successful_candidate_index, successful_denomination;

	for (int i = 1; i <= A; i++) {

		min = std::numeric_limits<int>::max();

		for (int j = 0; j < n; j++) {
			
			if (i > v[j]) {
				candidate_index = i - v[j];
				candidate = m[candidate_index];
				if (candidate < min) {
					min = candidate;
					successful_candidate_index = candidate_index;
					successful_denomination = j;
				}
			}
			else if (i == v[j]) { //This is if a coin exactly matches amount
				min = 0;
				successful_candidate_index = 0;
				successful_denomination = j;
				break; //No need to check higher denominations
			}
			else { //If amount is lower than current and future denominations
				break; //No need to check higher denominations
			}

		}

		m[i] = min + 1;

		for (int k = 0; k < n; k++) {
			//Copy coin config of successful candidate
			c[i][k] = c[successful_candidate_index][k];
		}
		//Increment successful denomination
		c[i][successful_denomination]++;

	}

	// Print results for each amount en route to A
	for (int i = 0; i <= A; i++) {
		std::cout << "[";
		for (int j = 0; j < n; j++) {
			std::cout << c[i][j];
			if (j != (n-1))
				std::cout << ", ";
		}
		std::cout << "]" << std::endl << m[i] << std::endl;
	}

	return 0;
}