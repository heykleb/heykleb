#include <iostream>
#include <string>
#include <algorithm>

class CheckAllNumbers {
private:
	bool dataCorrectness = true;
	int counter = 0;
public:
	CheckAllNumbers (std::string cardNumber) {
		while (cardNumber[counter] != '\0') {
			if (cardNumber[counter] < '0' || cardNumber[counter] > '9' ) {
				dataCorrectness = false;
				break;
			}
			counter++;
		}
		if (counter != 16) {
			dataCorrectness = false;
		}
	}

	bool isDataCorrect() {
		return dataCorrectness;
	}
};


class AlgorithmLuhn {
private:
	int sumOfNumbers = 0;
public:
	
	AlgorithmLuhn(std::string cardNumbers) {
		int sizeOfCardNumbers = cardNumbers.length();
		for (int i = sizeOfCardNumbers - 1; i >= 0; i--) {
			int IntegerNum = std::stoi(std::string(1, cardNumbers[i]));
			if (i % 2 == 0 ) {
				IntegerNum *= 2;
				if (IntegerNum > 9) {
					IntegerNum -= 9;
				}
			}
			sumOfNumbers += IntegerNum;
		}
	}

	int getSumOfNumbers() {
		return sumOfNumbers;
	}
};

int main() {
	int sumOfNumbers = 0;
	bool dataCorrectness;
	std::string userCardNumber{};

	std::cout << "This program uses the Luhn Algorigthm to validate a CC number." << std::endl;
	std::cout << "You can enter 'exit' anytime to quit." << std::endl << std::endl;

	while (1) {

		std::cout << "Enter your card number: ";
		std::getline(std::cin, userCardNumber);

		userCardNumber.erase(std::remove_if(userCardNumber.begin(), userCardNumber.end(), isspace), userCardNumber.end());

		if (userCardNumber != "exit") {

			CheckAllNumbers CheckAllNumbers(userCardNumber);

			if (CheckAllNumbers.isDataCorrect()) {

				AlgorithmLuhn AlgorithmLuhn(userCardNumber);
				sumOfNumbers = AlgorithmLuhn.getSumOfNumbers();

				if (sumOfNumbers % 10 != 0) {
					std::cout << "Incorrect card number entered" << std::endl << std::endl;
					continue;
				}
				else {
					std::cout << "The card data was entered correctly" << std::endl << std::endl;
				}

			}
			else {
				std::cout << "Incorrect card number entered" << std::endl << std::endl;
				continue;
			}
		}
		else {
			std::cout << "you are out of the program " << std::endl;
			break;
		}
	}

	return 0;
}