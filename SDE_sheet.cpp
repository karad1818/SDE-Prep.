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

// merge sorted array : already know brute force and merge sort technique so here's optimized one :

// so idea is to start with some gap and move 2 pointer mainting gap distance between each and do swaping
// then gap/=2 same until gap become 0 or 1 

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  int gap = (n+m);
      
  if(n == 0)
      return ;
      
  if(m == 0){
      // if m == 0 then just move element from nums2 to nums1
      for(int i=m;i<m+n;i++){
          nums1[i] = nums2[i-m];
      }
      return ;
  }

  while(gap > 0){
      // incase of odd gap will take ceil of gap/2
      gap = (gap + 1)/2;
        
      int i=0,j=gap;
      bool ok1=0,ok2=0;
      // in starting if gap is already more then elements in first then move second pointer in 2nd array with mainting that gap
      if(j>=m){
          ok2 = 1;
          j%=m;
      }
        
      for(int cnt=0;cnt<m+n;cnt++){
          // if ok1 == 1 that means in first pointer we're in second array same with ok2 
          if((ok1 ? nums2[i] : nums1[i]) >= (ok2 ? nums2[j] : nums1[j])){
              swap((ok1 ? nums2[i] : nums1[i]) , (ok2 ? nums2[j] : nums1[j]));
          }
          i++,j++;
            
          // if second pointer is outside second array then just finish 
          if(j>=n and ok2 == 1){
              break;
          }
          // move first pointer in second array
          if(i>=m and ok1 == 0){
              i%=m;
              ok1=1;
          }
          // move second pointer in second array
          if(j>=m and ok2 == 0){
              j%=m;
              ok2=1;
          }
      }
      // we're done with gap = 1 then finish
      if(gap == 1)
          break;
  }
      
  // now move all elements from second array to the first
  for(int i=m;i<m+n;i++){
      nums1[i] = nums2[i-m];
  }
}

