// note the different names for the C libraries
#include <cstdio>     //  cstdio   instead of stdio.h
#include <cstdlib>    //  sstdlib  instead of stdlib.h

// a simple class to explore the ideas of:
//    data members
//    access modifiers of private, public
//    keyword static
class LabExample
{
private:
	int storage;

public:
	void setStorage(int s)      {
		storage = s;
		// this->storage = s;
	}

	int getStorage()      {
		// return storage;
		return this->storage;
	}

	void modStorage()      {
		storage = storage * 2;
	}

	static void staticMethod()      {
		printf("Inside staticMethod()\n");

		// the following would cause an error if attempted
		//printf ("The value of storage is: %d\n", storage);
	}
};


int main(int argc , char** argv) {
	// create two instances of the above class
	LabExample inst1 , inst2;                // LINE 1

	printf("Inside main\n");

	inst1.setStorage(5);                   // LINE 2
	inst2.setStorage(1);                   // LINE 3

	printf("inst1 contains: %d \n" , inst1.getStorage());     // LINE 4
	printf("inst2 contains: %d \n" , inst2.getStorage());
	inst1.modStorage();
	inst1.modStorage();
	inst2.modStorage();
	printf("inst1 now contains: %d \n" , inst1.getStorage());
	printf("inst2 now contains: %d \n" , inst2.getStorage()); // LINE 5

	// repeat above with pointers to the above class
	LabExample* ptr1 , * ptr2;              // LINE 6

	// Use malloc to allocte heap memory and store address in pointers
	ptr1 = (LabExample*)malloc(sizeof(LabExample));   // LINE 7
	ptr2 = (LabExample*)malloc(sizeof(LabExample));   // LINE 8

	// must use -> instead of . since these are pointers
	ptr1->setStorage(15);                                     // LINE 9
	ptr2->setStorage(11);
	printf("ptr1 contains: %d \n" , ptr1->getStorage());
	printf("ptr2 contains: %d \n" , ptr2->getStorage());
	ptr1->modStorage();
	ptr1->modStorage();
	ptr2->modStorage();
	printf("ptr1 now contains: %d \n" , ptr1->getStorage());
	printf("ptr2 now contains: %d \n" , ptr2->getStorage()); // LINE 10

	// de-allocate the pointers
	free(ptr1);     // Use free() when allocated with malloc()   LINE 11
	free(ptr2);     // Use free() when allocated with malloc()   LINE 12

	// call the static method
	LabExample::staticMethod();          //   LINE 13

	printf("End of main\n");

	return 1;
}
