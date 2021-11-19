// 1. sort 0,1,2 ....

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

// --------------------------------------------------------------------------------------------------------------------------

// 2. find missing and repeating :

// idea 1 : find the sum of first n element and sum of square of first n element and then subtract with array's sum and do some math.

// idea 2 : do the xor of array's element and again do xor with (1...n) and divide x^y ..

// --------------------------------------------------------------------------------------------------------------------------

// 3. merge sorted array : already know brute force and merge sort technique so here's optimized one :

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

// --------------------------------------------------------------------------------------------------------------------------

// 4. Kadane : max subarray sum  
// idea : if sum becomes < 0 then make it 0 cause it's not useful

int maxSubArray(vector<int>& nums) {
  int sum=0;
  int ans = INT_MIN;
  for(auto i : nums){
      sum += i;
      ans = max(ans , sum);
      if(sum < 0)
          sum = 0;
  }
  return ans;
}


// --------------------------------------------------------------------------------------------------------------------------

// 5. Merge Interval : very easy

vector<vector<int>> merge(vector<vector<int>>& x) {
  sort(x.begin(),x.end());
  if(x.size()==0){
      return {};
  }
  vector<vector<int>>ans;
  ans.push_back({x[0][0],x[0][1]});
  for(int i=1;i<x.size();i++){
      if(ans[ans.size()-1][1]>=x[i][0]){
          int d=ans[ans.size()-1][0];
          int e=ans[ans.size()-1][1];
          int mi=min(x[i][0],d);
          int mx=max(x[i][1],e);
          ans.pop_back();
          ans.push_back({mi,mx});
      }else{
          ans.push_back({x[i][0],x[i][1]});
      }
  }
  return ans;
}

// --------------------------------------------------------------------------------------------------------------------------

// 6. find the duplicate number 

// idea 1 : modify array by doing negation
int findDuplicate(vector<int>& nums) {
  for(auto i : nums){
      int index = abs(i);
      if(nums[index] < 0){
          return index;
      }
      nums[index] *= -1;
  }
  return 0;
}

// idea 2 : do some mapping :
int store(vector<int>& nums , int pointer){
  if( pointer == nums[pointer] )
      return pointer;
  int next = nums[pointer];
  nums[pointer] = pointer;
  return store(nums,next);
}
int findDuplicate(vector<int>& nums) {
  return store(nums,0);
}

// idea 3 : cycle finding
int findDuplicate(vector<int>& nums) {
  int slow = nums[0],fast = nums[0];
  do{
      slow = nums[slow];
      fast = nums[nums[fast]];
  }while(slow != fast);

  fast = nums[0];
  while(slow != fast){
      slow = nums[slow];
      fast = nums[fast];
  }
  return slow;
}

// set matrix zeros
void setZeroes(vector<vector<int>>& matrix) {
  int n=(int)matrix.size();
  int m=(int)matrix[0].size();
  bool col=0,row=0;
  for(int i=0;i<n;i++){
      col |= (matrix[i][0] == 0);
  }
  for(int j=0;j<m;j++){
      row |= (matrix[0][j] == 0);
  }
  for(int i=1;i<n;i++){
      for(int j=1;j<m;j++){
          if(matrix[i][j] == 0){
              matrix[i][0] = 0;
              matrix[0][j] = 0;
          }
      }
  }
  for(int i=1;i<n;i++){
      for(int j=1;j<m;j++){
          if(!matrix[i][0] or !matrix[0][j])
              matrix[i][j] = 0;
      }
  }
  if(col){
      for(int i=0;i<n;i++)
          matrix[i][0] = 0;
  }
  if(row){
      for(int j=0;j<m;j++)
          matrix[0][j] = 0;
  }
}


// find in sorted rotated array

// first find min number so that you can figureout how many times array is rotated
// then simply do the BS
int search(vector<int>& nums, int target) {
  int n = (int)nums.size();
  int l = 0,r = n-1;
  while(l<r){
      int mid = (l+r)/2;

      if(nums[mid] > nums[r]){
          // 4 5 6 1 2 3
          l = mid + 1;
      }else{
          r = mid;
      }
  }

  int rot = l;

  l = 0 , r = n-1;
  while(l<=r){
      int mid = (l+r)/2;
      int real_mid = (mid + rot)%n;
      if(nums[real_mid] == target){
          return real_mid;
      }
      if(nums[real_mid] > target){
          r = mid - 1;
      }else{
          l = mid + 1;
      }
  }
  return -1;
}

// traping rain water
int trappingWater(int arr[], int n){

    // Your code here
    int ans = 0;
    int left = 0 ,right = n-1;
    int sum = 0;
    int leftMax = 0 , rightMax = 0;
    while(left < right){
        if(arr[left]<arr[right]){
            if(leftMax <= arr[left]){
                leftMax = arr[left];
            }else{
                ans += leftMax - arr[left];
            }
            left++;
        }else{
            if(rightMax <= arr[right]){
                rightMax = arr[right];
            }else{
                ans += rightMax - arr[right];
            }
            right--;
        }
    }
    return ans;
    
}
