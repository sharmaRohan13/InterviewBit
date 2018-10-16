vector<Interval> Solution::insert(vector<Interval> &intervals, Interval newInterval) {
    
    int n = intervals.size();
    vector<Interval> finalIntervalSet = intervals;
    
    //Place all intervals on number line, divide them into numbered sections
    //A section includes the left boundary but excludes right
    
    
    //Special Cases
    if(n == 0) {
        finalIntervalSet.push_back(newInterval);
        return finalIntervalSet;
    }
    if(newInterval.end < intervals[0].start) {
        finalIntervalSet.insert(finalIntervalSet.begin(), newInterval);
        return finalIntervalSet;
    }
    if(newInterval.start > intervals[n-1].end){
        finalIntervalSet.insert(finalIntervalSet.end(), newInterval);
        return finalIntervalSet;
    }
    if(newInterval.start == intervals[n-1].end) {
        finalIntervalSet[n-1].end = newInterval.end;
        return finalIntervalSet;
    }
    
    //Intially defined section numbers where are array will enter.
    int entry = 0, exits = 2*n;
    for(int i=n-1; i>=0; i--) {
        if(entry!=0 && exits!=2*n)
            break;
        if(entry==0) {
            if(newInterval.start >= intervals[i].start && newInterval.start < intervals[i].end)
                entry = 2*i+1;
            else if(i!=n-1 && newInterval.start > intervals[i].end && newInterval.start < intervals[i+1].start)
                entry = 2*(i+1);
            else if(i!=n-1 && newInterval.start == intervals[i].end)
                entry = 2*(i)+1;
        }
        if(exits==2*n){
            if(newInterval.end >= intervals[n-i-1].start && newInterval.end < intervals[n-i-1].end)
                exits = 2*(n-i-1)+1;
            else if(i!=n-1 && newInterval.end >= intervals[n-i-2].end && newInterval.end < intervals[n-i-1].start)
                exits = 2*(n-i-1);
        }
    }
    
    //Even section number represents between two intervals
    //Odd represents within an interval
    Interval replacementInterval;
    if(entry%2==0) 
        replacementInterval.start = newInterval.start;
    else 
        replacementInterval.start = intervals[(entry-1)/2].start;
    if(exits%2==0) 
        replacementInterval.end = newInterval.end;
    else 
        replacementInterval.end = intervals[(exits-1)/2].end;
    
    
    //Special Cases
    if(entry==exits){
        if(entry%2 == 0)
            finalIntervalSet.insert(finalIntervalSet.begin()+ entry/2, replacementInterval);
        return finalIntervalSet;
    }
    
    if(entry%2 != 0) entry--;
    if(exits%2 != 0) exits++;
    entry /= 2; exits /= 2;
    
    finalIntervalSet.erase(finalIntervalSet.begin()+entry, finalIntervalSet.begin()+exits);
    finalIntervalSet.insert(finalIntervalSet.begin()+entry, replacementInterval);
    return finalIntervalSet;
}
