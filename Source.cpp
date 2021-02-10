#include <iostream>
#include <time.h>

# include <sys/time.h> 
using namespace std; 
template <typename ITEM> void selectionSort(ITEM * items, int list_size)
{
	for (int y = 0; y < list_size - 1; y++)
	{
		int min = y; // assume the min is the first element 
					 // loop to find the smallest item in sub array [y+1 - n-1]    
		for (int x = y+1; x < list_size; x++)
		{ // if the current element is less, then it is the new minimum 
		if (items[x] < items[min]) min = x; 
		} 
		// If the minimum is different from the original one swap   
		if (min != y) swap(items[y], items[min]);
	} 

}

template <typename ITEM> void bubbleSort(ITEM * items, int list_size) 
{ 
	bool swapped = true;  
	for (int x = 0; x< list_size && swapped; x++)   // Loop as long as swap is true; at least one swap took place 
	{
		swapped = false; // Set swap to false      
		for(int y=0;y< list_size-x;y++) // Loop on un-bubbled items 
		{
			// Swap each two adjacent elements if  not ordered       
			if(items[y]>items[y+1])           
			{        // Set swap to true to indicate that a swap took place at least once in the inner loop       
				swapped = true;            
				swap(items[y],items[y+1]);         
		    }       
	     } 
	} 
}
template <typename ITEM> void insertionSort(ITEM * items, int list_size)
{

	if (list_size <= 1) return; // check if the list size is one or less return 
	for (int i = 1; i < list_size; i++)  // loop untill the list size 
	{
		ITEM tmp = items[i];  // make temp equal the item in the array i 
		int j = i;    
		for (; j > 0 && tmp < items[j - 1]; j--) //loop for j 
			items[j] = items[j - 1]; 
		items[j] = tmp;       // make the array at j to temp 
	}
}
template <typename ITEM>
void heapify(ITEM * items, int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

					   // If left child is larger than root 
	if (l < n && items[l] > items[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && items[r] > items[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(items[i], items[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(items, n, largest);
	}
}
template <typename ITEM> void HeapSort(ITEM * items, int list_size)
{
	// Build heap (rearrange array) 
	for (int i = list_size / 2 - 1; i >= 0; i--)
		heapify(items, list_size, i);

	// One by one extract an element from heap 
	for (int i = list_size - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(items[0], items[i]);

		// call max heapify on the reduced heap 
		heapify(items, i, 0);
	}
}
template <typename ITEM> void merge(ITEM * items, ITEM * tempArr, int leftPos, int rightPos, int rightEnd)

{
	int leftEnd = rightPos - 1; // the left end is equal to the right possition minus one 
	int tmpPos = leftPos;   
	int numElements = rightEnd - leftPos + 1;    
	while (leftPos <= leftEnd && rightPos <= rightEnd)    
		if (items[leftPos] <= items[rightPos])      // check if the right is bigger than the left or not   
			tempArr[tmpPos++] = std::move(items[leftPos++]); //if so, move     
		else tempArr[tmpPos++] = std::move(items[rightPos++]);
	while (leftPos <= leftEnd)    // Copy rest of first half    
		tempArr[ tmpPos++ ] = std::move( items[ leftPos++ ] );   
	while( rightPos <= rightEnd )    // Copy rest of first half  
		tempArr[ tmpPos++ ] = std::move( items[ rightPos++ ] );    
	for(int i=0;i < numElements; ++i, --rightEnd ) // Copy tmpArray back  
		items[ rightEnd ] = std::move( tempArr[ rightEnd ] ); 
}
template <typename ITEM> void mergeSortt(ITEM * items, ITEM * tempArr, int left, int right)
{ 
	if (left < right)
	{ 
		int center = (left + right) / 2;   //make the center by getting the difference between the  left and the right divide it by two   
		mergeSortt(items, tempArr, left, center); 
		mergeSortt(items, tempArr, center + 1, right);    
		merge(items, tempArr, left, center + 1, right); 
	} 
}

template <typename ITEM> void mergeSort(ITEM * items, int list_size)
{ 
	ITEM * tempArr = (ITEM *)calloc(list_size, sizeof(ITEM)); //make an array pointer of the size and type ITEM
	mergeSortt(items, tempArr, 0, list_size - 1);   
	free(tempArr); 
}

template <typename ITEM> const ITEM & median3(ITEM * items, int left, int right) // median of the indexs 
{ 
	int center = (left + right) / 2;   // mean
	if (items[center] < items[left]) std::swap(items[left], items[center]);    
	if (items[right] < items[left]) std::swap(items[left], items[right]);  
	if (items[right] < items[center]) std::swap(items[center], items[right]);  
	std::swap(items[center], items[right - 1]); 
	return items[right - 1]; //return the median 
}
template <typename ITEM>  void quickSortt(ITEM * items, int left, int right)
{ 
	if (left + 50 <= right)
	{ 
		const ITEM & pivot = median3(items, left, right);  
		int i = left, j = right - 1;      
		for (;;) {
			while (items[++i] < pivot);     // while loop untill the pivot is less than the items in the array  
			while (pivot < items[--j]);       
			if (i < j) std::swap(items[i], items[j]); else break; 
		}        std::swap(items[i], items[right - 1]);  
		quickSortt(items, left, i - 1);    // recrsuin to left 
		quickSortt(items, i + 1, right);   // recrsuin of right 
	} 
	else insertionSort(items + left, right - left + 1); 
}
template <typename ITEM>  void quickSort(ITEM * items, int list_size)
{ 
	quickSortt(items, 0, list_size - 1); 
}

int main ()
{
	int ans;     // for the answer of the user about the data type
	int s;      // answer about the type of the sort 
        struct timeval start, end;  // for the clock 
        double t;
   // asking the user about the data type 
	cout << "choose the type of the data base"<< endl;  
	cout << "(1)------->Randomly Generated Dataset" << endl << "(2)----------> Presorted Dataset in Ascending Order"
		<< endl << "(3)-------->Presorted Dataset in Descending Order"<<endl; 
	cin >> ans; 
   //asking the user about the sorting type 
	cout << " choose the type of sort " << endl << "(1)---> selection sort" <<endl<< "(2)----> bubble sort" << endl
		<< "(3)----> Insertion sort" << endl << "(4)-----> Heap sort" << endl << "(5)---> Merg Sort " << endl
		<< "(6)-----> Quick Sort" << endl; 
	cin >> s;

	switch (s)  // swich to choose the sort type 
	{
	case 1: // selection sort 

		if (ans == 1) // random dataset 
		{       
                     uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t)); //intializing the array of type ITEM
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
                        gettimeofday(&start, NULL);
			selectionSort<uint64_t>(items, size);
                       gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"selection sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;  // increase the size by the multiple of 10
                         }
	}
		if (ans == 2)  //presorted dataset "ascending"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t)); //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);  // calculate the starting time 
			selectionSort<uint64_t>(items, size);
                       gettimeofday(&end, NULL);  // calculate the end time 
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ; // the difference between the start and end time
                  cout <<"selection sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3)   // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
			selectionSort<uint64_t>(items, size);
                       gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"selection sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break; 
	case 2: // bubble Sort
		if (ans == 1)  // random dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));   //intializing the array of type ITEM
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
                        gettimeofday(&start, NULL);
			bubbleSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"bubble sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		if (ans == 2) // ascending presorted dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);
			bubbleSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"bubble sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3)  // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));   //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
			bubbleSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"bubble sort of" << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break;
	case 3: // Insertion sort 
		if (ans == 1)  // random dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));   //intializing the array of type ITEM
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
                        gettimeofday(&start, NULL);
			insertionSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Insertion sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		if (ans == 2)  // ascending presorted dataset
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);
			insertionSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Insertion sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3) // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
			insertionSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Insertion sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break;
	case 4: // Heap sort 
		if (ans == 1)  // random dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));   //intializing the array of type ITEM
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
                        gettimeofday(&start, NULL);
			HeapSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Heap sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		if (ans == 2)  // ascending presorted dataset
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);
			HeapSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Heap sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3)    // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
			HeapSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
                  cout <<"Heap sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break;
	case 5: // Merge sort 
		if (ans == 1)   // random dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));  //intializing the array of type ITEM
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
			gettimeofday(&start, NULL);
		        mergeSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Merge sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		if (ans == 2)    // ascending presorted dataset
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);
		        mergeSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Merge sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3)   // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
		        mergeSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                   t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"Merge sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break;
	case 6: // QUICK sort 
		if (ans == 1)   // random dataset 
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));
			srand(time(NULL));
			for (int i = 0; i < size; i++) items[i] = rand();
			gettimeofday(&start, NULL);
			quickSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"QUICK sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		if (ans == 2)  // ascending presorted dataset
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)  // looping for the multiple of 10 untill 100000000
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));
			for (uint64_t i = 0; i < size; i++) items[i] = i;
			gettimeofday(&start, NULL);
			quickSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"QUICK sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }

		}
		if (ans == 3) // presorted dataset "descinding"
		{
			uint64_t size = 10;
                       for(int i=0 ; i<8; i++)
			{
			uint64_t * items = (uint64_t *)calloc(size, sizeof(uint64_t));
			for (uint64_t i = 0; i < size; i++) items[i] = size - i;
			gettimeofday(&start, NULL);
			quickSort<uint64_t>(items, size);
                        gettimeofday(&end, NULL);
                        t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) ;
                  cout <<"QUICK sort of " << size<< "  items ....... time:   " << t <<endl;
                    size= size*10;
                         }
		}
		break;
	default:
		break;
	}
	
	








system("pause");	
return 0; 
}
