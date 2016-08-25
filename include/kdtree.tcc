/**
 * @file kdtree.tcc
 * @author Shahzad Bhatti
 * @Date Summer 2015
 * Implementation of kd_tree class.
 */

#include "kdtree.h"
#include <cmath>     // abs in find_nearest_neighbor 


template <int Dim>
bool kd_tree<Dim>::smaller_in_dimension(const point<Dim>& first, const point<Dim>& second, int curDim) const
{
    if (first[curDim] < second[curDim])
    	return true;
    else if (first[curDim] > second[curDim])
    	return false;
    else
    	return first < second;  
 // if the two points have same value in curDim, break the tie by selecting smaller point 	   	
}    	

template <int Dim>
bool kd_tree<Dim>::should_replace(const point<Dim>& target, const point<Dim>& current_best, const point<Dim>& potential) const
{
    auto dist_tc = sDistance(target, current_best);
    auto dist_tp = sDistance(target, potential);
    if (dist_tp < dist_tc)
    	return true;
    else if (dist_tp > dist_tc)
    	return false;
    else
     	return potential < current_best;	
   // if the two points have same value in curDim, break the tie by selecting smaller point 	  	
}											

template <int Dim>
int kd_tree<Dim>::sDistance(const point<Dim>& p1, const point<Dim>& p2) const
{
	int dist = 0;
	for (int i = 0; i <Dim; ++i)
		dist+= (p1[i] - p2[i]) * (p1[i] - p2[i]);
	return dist;	 
}

template <int Dim>
kd_tree<Dim>::kd_tree(const std::vector<point<Dim>>& newPoints)
{
	if (!newPoints.empty())
	{
		for (auto x : newPoints)
			points.push_back(x);
	    construct(0, points.size() - 1, 0); 
	}	    
}

template <int Dim>
void kd_tree<Dim>::construct(size_t start, size_t end, int depth)
{
	if (start == end)   // if leaf node
		return;
	
	auto axis = depth % (Dim);
	// if only two points are left make smaller as parent and larger as its right child
	if (end - start == 1)		
	{	
		if (!smaller_in_dimension(points[start], points[end], axis))
			std::swap(points[start], points[end]);
		return;		
	}	
	auto median = (start + end)/2;     
	select(axis, start, end, median);  
	construct(start, median - 1, depth + 1);
	construct(median + 1, end, depth + 1);				
}
template <int Dim>
void kd_tree<Dim>::select(int axis, size_t start, size_t end, size_t median)
{
	if (start == end)	// if only one point return
		return;
	while(true)
	{
		auto pivotIdx = (start + end)/2;
		//shuffle the vector such that all element to the left of median are smaller and to the right are larger.
		pivotIdx = partition(axis, start, end, pivotIdx);  
		if (pivotIdx == median)
			return;
		else if (pivotIdx < median)
			start = pivotIdx + 1;
		else	 	
			end = pivotIdx - 1;
	}	
}

template <int Dim>
size_t kd_tree<Dim>::partition(int axis, size_t start, size_t end, size_t pivotIdx)
{
	if (start == end) 	// if only one point return it. 
		return start;

	auto pivotValue = points[pivotIdx]; 	
	std::swap(points[pivotIdx], points[end]); 	// move pivot element to the end
	// all points at index less than storeIdx are smaller than pivot
	auto storeIdx = start;						
	for(auto i = start; i < end; ++i)
	{
		if (smaller_in_dimension(points[i], pivotValue, axis))
		{
			std::swap(points[i], points[storeIdx]);	
			++storeIdx;
		}
	}
	// moving pivot to the storeIdx. all points to the left of pivot are smaller than it.
	std::swap(points[storeIdx], points[end]);   
	return storeIdx;	
}

template <int Dim>
point<Dim> kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query) const
{
	if (points.empty())		
		throw std::runtime_error{"The tree is empty"};

	int cur_best = -1;	
	find_nearest_neighbor(query, cur_best, 0, points.size()-1, 0);
	return points[cur_best];
}

template <int Dim>
void kd_tree<Dim>::find_nearest_neighbor(const point<Dim>& query, int& cur_best, size_t start, size_t end, int depth) const
{
	auto axis = depth % Dim;	// finding spliting dimension 
	
	if(start == end) 			// if at leaf node
	{
		if (cur_best == -1)		// first visit to any leaf
			cur_best = start;
		if(should_replace(query, points[cur_best], points[end]))
			cur_best = start;
		return;
	}
	if (end - start == 1)  	// if parent has only one child
	{	
		find_nearest_neighbor(query, cur_best, end, end, depth+1);
		if (should_replace(query, points[cur_best], points[start]))
			cur_best = start;
		return;	
	}	
	auto median = (start + end)/2;

	// if true move left, else move right
	if(smaller_in_dimension(query, points[median], axis))	
		find_nearest_neighbor(query, cur_best, start, median - 1, depth + 1);	
	else													
		find_nearest_neighbor(query, cur_best, median + 1, end, depth + 1);
	
	// check if cur_best needs to be updated
	if (should_replace(query, points[cur_best], points[median]))	
		cur_best = median;

	auto sDist2split = std::abs(points[median][axis] - query[axis]) * std::abs(points[median][axis] - query[axis]);

	// check if we need to traverse along the other brach
	if (sDistance(query, points[cur_best]) >= sDist2split)			
	{
		// if true move left, else move right
		if (smaller_in_dimension(query, points[median], axis))		
			find_nearest_neighbor(query, cur_best, median+1, end, depth+1);
		else													
			find_nearest_neighbor(query, cur_best, start, median-1, depth+1);	
	}
		
}

