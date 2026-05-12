#include<omp.h>
#include<iostream>
#include<chrono>

using namespace std;
using namespace std::chrono;

void displayArray(int nums[],int length){
    cout<< "Nums:[";

    for(int i=0;i<length;i++){
        cout<< nums[i] << " ";
    }

    cout<< "]" << endl;
}

void minOperation(int nums[],int length){
    int minValue = nums[0];

    #pragma omp parallel for reduction(min : minValue)
    for(int i=0;i<length;i++){
    
        minValue=(nums[i]<minValue) ? nums[i] : minValue;
        
        }

    cout<< "Min Value: " << minValue << endl;
    }
    

void maxOperation(int nums[],int length){
    int maxValue = nums[0];

    #pragma omp parallel for reduction(max : maxValue)
    for(int i=0;i<length;i++){
    
        maxValue=(nums[i]>maxValue) ? nums[i] : maxValue;
        
        }

    cout<< "Max Value: " << maxValue << endl;
    }
    

void sumOperation(int nums[],int length){
    int sum = 0;

    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<length;i++){
        sum += nums[i];
    }

    cout<< "Sum: " << sum << endl;
}
        
void averageOperation(int nums[],int length){
    float sum = 0;

    #pragma omp parallel for reduction(+: sum)
    for(int i=0;i<length;i++){
    
        sum += nums[i];
        
        }

    cout<< "Average: " << (sum / length) << endl;
    }

int main(){
    int length;
    cout<< "Enter the Number of elements: ";
    cin>> length;

    int*nums= new int[length];

    cout<< "Enter the elements:\n ";

    for(int i=0;i<length;i++){
        cin>> nums[i];
    }

    auto start = high_resolution_clock::now();

    displayArray(nums,length);
    minOperation(nums,length);
    maxOperation(nums,length);
    sumOperation(nums,length);
    averageOperation(nums,length);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout<< "\nExecution time:"
         << duration.count()
         << "microseconds" << endl;

    delete[] nums;
    return 0;

}
    
      
