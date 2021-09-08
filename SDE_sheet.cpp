// sort 0,1,2 ....

void sortColors(vector<int>& nums) {
      int n=(int)nums.size();
      int low=0,mid=0,high=n-1;
      while(mid<=high){
          if(nums[mid] == 0){
              // swap mid and low
              swap(nums[mid] , nums[low]);
              low++,mid++;
          }else if(nums[mid] == 1){
              //won't do anything
              mid++;
          }else{
              swap(nums[high] , nums[mid]);
              high--;
          }
      }
  }

// find missing and repeating :

// idea 1 : find the sum of first n element and sum of square of first n element and then subtract with array's sum and do some math.

// idea 2 : do the xor of array's element and again do xor with (1...n) and divide x^y ..

