#include <iostream>
using namespace std;
#include "BHeap.cpp"

int main(){
    char K1[6] = {'a','f','g','h','i','j'};
    char K2[4] = {'b','c','d','e'};

    BHeap<char> myH1, myH2;
    for(int i=0; i<6; i++) myH1.insert(K1[i]);
    for(int i=0; i<4; i++) myH2.insert(K2[i]);


    std::cout << "\nH1\n";
    myH1.printKey();

    std::cout << "\nMerge\n";
    myH1.merge(myH2);

    std::cout << "\nH1\n";
    myH1.printKey();

    std::cout << "\nH2\n";
    myH2.printKey();

    std::cout << "Extracted: " << myH1.extractMin() << "\n";
    std::cout << "New Min: " << myH1.peekKey() << "\n";
    myH1.printKey();



    return 0;
	char K[6] = {'a','b','c','d','e','f'};
	
	BHeap<char> H1, H2;
	for(int i=0; i<6; i++) H1.insert(K[i]);
	
	cout << H1.extractMin() << endl; //Should output a
	
	H1.printKey();
	//Should output "B2:\n b c d e\n B0:\n f \n"
	
	H1.insert('g'); H1.insert('h'); H1.insert('a'); H1.insert('i');
	
	H1.printKey();
	//Should output "B0:\n a\n B2:\n b c d e\n B0:\n f\n B0:\n g\n B0:\n h\n B0:\n i\n"
	
	cout << H1.extractMin() << endl; 	//Should output a

	H1.printKey();	
	//Should output "B3: b c d e f g h i\n"
	
	H1.insert('j'); H1.insert('k'); H1.insert('l');
    
	cout << H1.extractMin() << endl;	//Should output b

	H1.printKey();
	//Should output	B3:\n c j d e f g h i\n B1:\n k l\n"
	
	H2.insert('A'); H2.insert('B'); H2.insert('C'); H2.insert('D');
	cout<< H2.extractMin() << endl;	//Should output A

	H2.printKey();
	//Should output "B1:\n B C\n B0:\n D\n"
	
	H1.merge(H2); H1.printKey();
	//Should output "B1: B C\n B0:\n D\n B3:\n c j d e f g h i\n B1:\n k l\n"
	
	cout << H1.extractMin() << endl;	//Should output B

	H1.printKey();
	//Should output "B2:\n C D k l\n B3:\n c j d e f g h i\n"
	
	return 0;
}