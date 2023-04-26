 #include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& list, int first, int last) {
  // The pivot should be the median of the
  // first, middle, and last elements.

    int num1 = first;
    int num2 = (first + last) / 2;
    int num3 = last;

    int pivot;
    if ((list.at(num1) >= list.at(num2) && list.at(num1) <= list.at(num3)) || (list.at(num1) <= list.at(num2) && list.at(num1) >= list.at(num3)))
        pivot = num1;
    else if ((list.at(num2) >= list.at(num1) && list.at(num2) <= list.at(num3)) || (list.at(num2) <= list.at(num1) && list.at(num2) >= list.at(num3)))
        pivot = num2;
    else
        pivot = num3;

	int smallIndex = first;

  // partition procedure
  // swap the pivot and the first element in the list
	swap(list.at(pivot), list.at(first));

    // for the remaining elements, if the current element is smaller than the pivot,
    // increment small index and swap current element with element at smallIndex
    for (int i = 1; i < list.size(); i++) {
	    if (list.at(i) < list.at(0)) {
            smallIndex++;
            swap(list.at(smallIndex), list.at(i));
	    }
    }

    // return the pivot element to its original position
    swap(list.at(smallIndex), list.at(first));
	return smallIndex;  
}

void recQuickSort(vector<int>& list, int first, int last) {
    int pivotLocation;

    if(first < last) {
        pivotLocation = partition(list, first, last);
        recQuickSort(list, first, pivotLocation - 1);
        recQuickSort(list, pivotLocation + 1, last);
    }
}

void quicksort(vector<int>& list, int first, int last) {
    recQuickSort(list, 0, list.size() - 1);
}

struct element{
    int value;
    int parentVector;
};

struct elementGreater{
    bool operator()(const element a, const element b){
        return a.value > b.value;
    }
};

void multiway_merge(
  vector<vector<int> >& input_lists, vector<int>& output_list)
{
    // create a heap of all the first elements in the lists
    priority_queue <element, vector<element>, elementGreater > heap;
    for (int i = 0; i < input_lists.size(); ++i) {
        element tmp;
        tmp.parentVector = i;
        tmp.value = input_lists.at(i).at(0);
        heap.push(tmp);
        input_lists.at(i).erase(input_lists.at(i).begin());
    }

    // output the min element to the output list and pull the successor into the heap.
    bool complete = false;
    int outIt = 0;
    while (!complete){
        // check to see if the process is complete
        if (heap.empty()){
            complete = true;
        }

        // if not complete push the min element to the output list
        else{
            output_list.at(outIt) = heap.top().value;
            outIt++;

            // get the successor and remove it from the input list while pushing to the heap IF IT EXISTS
            if (!input_lists.at(heap.top().parentVector).empty()){
                element tmp;
                tmp.parentVector = heap.top().parentVector;
                tmp.value = input_lists.at(tmp.parentVector).at(0);
                input_lists.at(tmp.parentVector).erase(input_lists.at(tmp.parentVector).begin());
                heap.pop();
                heap.push(tmp);
            }
            else{
                heap.pop();
            }
        }
    }

} 

int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;

  return 1;
}
