// Shpora.cpp : Defines the entry point for the console application.
//
#include <numeric>
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <math.h> 
#include <stack>
#include <set>

using namespace std;

int lift(vector<int>& A, vector<int>& B, int M, int X, int Y);
bool swapSort(vector<int>& A);
int suffixes(string s);
int count(int N);
vector<int> counter(int N, vector<int> &A);
int slices(vector<int> &A);

int main()
{
	vector<int> ops = { 4,2,2,5,1,5,8 };
	
	cout << slices(ops);

	return 0;
}

//передаётся инт, напиши ф-ю которая считает все возможные перестановки с учётом дупликатов и нулей (нули в начале нельзя)
int fact(int n)
{
	int res = 1;
	while (n > 1)
	{
		res *= n;
		n--;
	}
	return res;
}

int factz(int n, int z)
{
	int res = 1;
	for (int i = 0; i < n; i++)
	{
		res *= n - z;

		z--;
		n--;
		if (z < 0)
			z++;
	}
	return res;
}

int count(int N)
{	
	string s = to_string(N);
	int size = s.size();
	int zeros = count(begin(s), end(s), '0');
	
	auto last = std::unique(s.begin(), s.end());

	int uniqueNums = distance(s.begin(), --last);
	cout << "nums: " << uniqueNums << " Zeros: " << zeros << " Size: " << size << endl;


	int A = 0;
	A = factz(size,zeros);
	
	return A;
}



//в лифт входит вектор людей (вектор этажей на которые они едут), с вектором масс , в лифт помещается X людей с суммарной массой Y, и всего M этажей, сколько раз лифт остановится
vector<int> pushPeople(vector<int>::iterator& masses, vector<int>::iterator& destinations,const vector<int>::iterator& end, int maxPeople, int maxMass)
{
	int totalPeople = 0;
	int totalMass = 0;
	auto start = destinations;

	while (totalPeople < maxPeople  && masses != end)
	{
		if (totalMass + *masses > maxMass || totalPeople + 1 > maxPeople)
			break;
		else
		{
			totalPeople++;
			totalMass += *masses;
		}

		masses++;
		destinations++;
	}


	if (masses == end)
		destinations--;

	vector<int> dests(start, next(destinations));
	return dests;
}

int countStops(vector<int> stops)
{
	auto floors = unique(stops.begin(), stops.end());
	stops.resize(distance(stops.begin(), floors));

	return stops.size();
}

int lift(vector<int>& A, vector<int>& B, int M, int X, int Y)
{
	auto masses = begin(A);
	auto destinations = begin(B);
	int stops = 0;

	while (masses != A.end())
	{
		stops += countStops(pushPeople(masses, destinations, A.end(), X, Y));
	}
	return stops;
}

//строка может иметь суфиксы и префиксы аааббааа , найти длинну найбольшей строки которая является и суфиксом и префиксом.

int suffixes(string s)
{
	string suf = "";
	string pref = "";

	auto fIt = begin(s);
	auto bIt = rbegin(s);

	for (int i = 0; i < s.size() - 1; i++)
	{
		if (suf != pref)
			return i - 1;

		suf += *bIt;
		pref += *fIt;
		bIt++;
		fIt++;
	}

	return s.size() - 1;
}


//можно ли масив отсортировать одним свапом

bool swapSort(vector<int>& A) 
{
	auto oldVec = A;
	sort(begin(A), end(A));

	int j = 0;
	for (int i = 0; i < A.size(); i++) 
	{
		if (oldVec[i] != A[i])
			j++;

		if (j > 2)
			return false;
	}
	return true;
}

int gap(int N)
{
	int currentGap = 0;
	int maxGap = 0;
	int a = 0;

	while (N % 2 == 0 && N != 0)
	{
		N = N / 2;
	}

	while (N != 0)
	{
		a = N % 2;
		if (a == 0)
		{
			currentGap++;
		}
		else
		{
			if (maxGap < currentGap)
			{
				maxGap = currentGap;
			}
			currentGap = 0;
		}
		N = N / 2;
	}
	return maxGap;
}


vector<int> rot(vector<int> &A, int K) {

	if (K > A.size())
		return rot(A, K - A.size());

	vector<int> rotated(A.size());

	for (int i = 0; i < K; i++)
	{
		rotated[i] = A[A.size() - K + i];
	}

	for (int i = 0; i < A.size() - K; i++)
	{
		rotated[i + K] = A[i];
	}

	return rotated;
}


//Tape splitting
int solution(vector<int> &A) {

	int leftP = A[0];
	int rightP = 0;
	for (int i = 1; i < A.size(); i++)
		rightP += A[i];

	int result = abs(leftP - rightP);

	for (int i = 1; i < A.size(); i++)
	{
		leftP += A[i];
		rightP -= A[i];

		int currentRes = abs(leftP - rightP);
		if (currentRes < result)
			result = currentRes;
	}

	

	return result;
}

//Frog leaps how much seconds it will take
int frogLeaps(int X, vector<int> &A) {

	vector<bool> positions(X);
	for (bool p : positions)
		p = false;


	for (int i = 0; i< A.size(); i++)
	{
		if (!positions[A[i]])
		{
			positions[A[i]] = true;
			X--;
			//cout << X << endl;
		}
		if (X == 0)
			return i;
	}
	return -1;
}


// counters and operations
vector<int> counter(int N, vector<int> &A) {

	vector<int> counters(N);
	int maxEl = 0;
	int lastMass = 0;

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] <= N)
		{
			if (counters[A[i] - 1] < lastMass)
				counters[A[i] - 1] = lastMass + 1;
			else
				counters[A[i] - 1]++;

			if (counters[A[i] - 1] > maxEl)
				maxEl = counters[A[i] - 1];
		}
		else
			lastMass = maxEl;
	}

	for (int i = 0; i < counters.size(); i++)
	{
		if (counters[i] < lastMass)
			counters[i] = lastMass;
	}

	return counters;
}


//missing integer
int missing(vector<int> &A) {
	vector<bool> nums(A.size() + 1);

	if (A.size() == 0)
		return 1;

	if (A.size() == 1)
	{
		if (A[0] == 1)
			return 2;
		else return 1;
	}

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] > 0 && i < A.size())
		{
			nums[A[i] - 1] = true;
		}
	}


	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == false)
			return i + 1;
	}
}

//passing cars
int passing_cars(vector<int> &A) {
	int carsGoingWest = 0;
	int pairz = 0;

	for (int i = A.size() - 1; i > -1; i--)
	{
		if (A[i] == 1)
			carsGoingWest++;
		if (A[i] == 0)
		{
			pairz += carsGoingWest;
			if (pairz > 1000000000)
				return -1;
		}
	}
	return pairz;
}


//nucleotides
int getvalue(char c)
{
	switch (c)
	{
	case 'A':
		return 1;
	case 'C':
		return 2;
	case 'G':
		return 3;
	case 'T':
		return 4;
	}
	return 0;
}

vector<int> genom(string &S, vector<int> &P, vector<int> &Q) {

	vector<int> result(P.size());
	vector<int> factors(S.size());

	auto it = begin(S);
	for (int i = 0; i < factors.size(); i++)
	{
		factors[i] = getvalue(*it);
	}

	for (int i = 0; i < factors.size(); i++)
	{
		cout << factors[i];
	}
	return result;
}


//slices avg

int slices(vector<int> &A) {

	float min = 10000;
	int minIndex = 0;

	for (int i = 0; i < A.size() - 2; i++)
	{

		if ((float)(A[i] + A[i + 1]) / (float)2 < min)
		{
			min = (float)(A[i] + A[i + 1]) / (float)2;
			minIndex = i;
		}


		if ((float)(A[i] + A[i + 1] + A[i + 2]) / (float)3 < min)
		{
			min = (float)(A[i] + A[i + 1] + A[i + 2]) / (float)3;
			minIndex = i;
		}
	}

	if ((float)(A[A.size() - 2] + A[A.size() - 1]) / (float)2 < min)
	{
		minIndex = A.size() - 2;
	}

	return minIndex;

}

// Count divisionable numbers
int divisions(int A, int B, int K) {

	if (A % K == 0)
		return (B - A) / K + 1;
	else
		return (B - (A - A % K)) / K;

}

//build triangle
int triangle(vector<int> &A) {

	if (A.size() < 3)
		return 0;

	sort(begin(A), end(A));

	for (int i = 0; i < A.size() - 2; i++)
	{
		if (A[i] + A[i + 1] > A[i + 2])
			return 1;
	}
	return 0;

}

//intersections
int number_of_disc_intersections(const vector<int> &A) {
	int sum = 0;
	vector<int> start(A.size(), 0);
	vector<int> end(A.size(), 0);

	for (size_t i = 0; i<A.size(); i++) {
		if ((int)i<A[i]) 
			start[0]++;
		else        
			start[i - A[i]]++;
		if (i + A[i] >= A.size())   
			end[A.size() - 1]++;
		else                    
			end[i + A[i]]++;
	}

	int active = 0;

	for (size_t i = 0; i<A.size(); i++) {
		sum += active * start[i] + (start[i] * (start[i] - 1)) / 2;
		if (sum>10000000) 
			return -1;
		active += start[i] - end[i];
	}

	return sum;
}

//stone Wall
int stoneWall(vector<int> &H) {
	// write your code in C++14 (g++ 6.2.0)
	int N = H.size();
	vector<int> stack(N, 0);
	int ss = 0;
	int result = 0;

	for (int i = 0; i<N; i++)
	{
		while (ss>0 && stack[ss]>H[i])ss--;

		if (H[i] != stack[ss])
		{
			result++;
			stack[++ss] = H[i];
		}
	}
	return result;
}


//fish
int fishWar(vector<int> &A, vector<int> &B) {

	stack<int> st;
	int casualties = 0;

	for (size_t i = 0; i < A.size(); i++)
	{
		if (B[i] == 1)
		{
			st.push(A[i]);
		}
		if (B[i] == 0 && st.size() > 0)
		{
			if (st.top() < A[i])
			{
				st.pop();
				i--;
			}
			casualties++;
		}

	}

	return A.size() - casualties;
}

//leader
int leaderI(vector<int> &A) {

	int equi_leaders = 0;

	int leader = A[0];
	int ctr = 1;

	for (int i = 1; i < A.size(); i++) {
		if (A[i] == leader) ctr++;
		else ctr--;
		if (ctr == 0) {
			ctr = 1;
			leader = A[i];
		}
	}

	int total = 0;
	for (int i : A) {
		if (i == leader) total++;
	}

	if (total <= (A.size() / 2)) return 0;

	int ldrCount = 0;
	for (int i = 0; i < A.size(); i++) {
		if (A[i] == leader)
			ldrCount++;
		int leadersInRightPart = (total - ldrCount);
		if (ldrCount >(i + 1) / 2 && leadersInRightPart > (A.size() - i - 1) / 2)
		{
			equi_leaders++;
		}
	}

	return equi_leaders;
}

//maxSlice
int maxSlice(vector<int> &A) {
	int max_end = A[0];
	int max_slice = A[0];

	for (int i = 1; i < A.size(); i++)
	{
		max_end = (max_end + A[i] > A[i]) ? max_end + A[i] : A[i];
		max_slice = (max_end > max_slice) ? max_end : max_slice;
	}

	return max_slice;
}

//maxProfit
int maxProfit(vector<int> &A) {

	if (A.size() == 0)
		return 0;

	int min_day = A[0];
	int max_prof = 0;


	for (int i = 1; i < A.size(); i++)
	{
		min_day = (min_day < A[i]) ? min_day : A[i];
		max_prof = (max_prof > A[i] - min_day) ? max_prof : A[i] - min_day;
	}

	return max_prof;

}


//Double slice sum
int doubleSliceSum(vector<int> &A) {

	vector<int> K1(A.size());
	vector<int> K2(A.size());

	for (int i = 1; i < A.size() - 1; i++) {
		K1[i] = (K1[i - 1] + A[i] > 0) ? K1[i - 1] + A[i] : 0;
	}
	for (int i = A.size() - 2; i > 0; i--) {
		K2[i] = (K2[i + 1] + A[i] > 0) ? K2[i + 1] + A[i] : 0;
	}

	int max = 0;

	for (int i = 1; i < A.size() - 1; i++) {
		max = (max > K1[i - 1] + K2[i + 1]) ? max : K1[i - 1] + K2[i + 1];
	}

	return max;
}
 
//countfactors
int factor(int N)
{
	int cnt = 0;
	int i = 1;

	while (i*i < N)
	{
		if (N % i == 0)
		{
			cnt += 2;
		}
		i++;
	}

	if (i * i == N)
		cnt++;

	return cnt;
}

//Count smallest perimeter
int smallestPerimeter(int N) {

	int i = 1;
	int per = 2147483647;
	do
	{
		if (N % i == 0)
		{
			int buf = 2 * (i + (int)(N / i));
			per = (buf < per) ? buf : per;
		}
		i++;
	} while (i*i <= N);

	return per;
}

//peakslicing
int slicing(vector<int> A) {
	int N = A.size();

	// Find all the peaks
	vector<int> peaks;
	for (int i = 1; i < N - 1; i++) {
		if (A[i] > A[i - 1] && A[i] > A[i + 1])
			peaks.push_back(i);
	}

	for (int size = 1; size <= N; size++) {
		if (N % size != 0) continue; // skip if non-divisible
		int find = 0;
		int groups = N / size;
		bool ok = true;
		// Find whether every group has a peak
		for (int peakIdx : peaks) {
			if (peakIdx / size > find) {
				ok = false;
				break;
			}
			if (peakIdx / size == find) 
				find++;
		}
		if (find != groups) 
			ok = false;
		if (ok) 
			return groups;
	}
	return 0;
}


// Flags 
int flagsOnAMountain(vector<int> A) {
	if (A.size() == 1)  return 0;
	vector<int> al;
	for (int i = 1; i<A.size() - 1; i++)
	{
		if (A[i]>A[i - 1] && A[i]>A[i + 1])
		{
			al.push_back(i);
		}
	}
	int s = al.size();
	if (s == 1) return 1;
	if (s == 0)return 0;

	s = (int)ceil(sqrt(A.size()));

	while (s >= 0) {
		int lp = al[0];
		int c = 1;
		for (int i = 1; i<al.size(); i++)
		{
			int d = abs(al[i] - lp);
			if (d >= s)
			{
				lp = al[i];
				c++;
				if (c == s)
					return c;
			}
		}
		s--;
	}
	return 0;
}

//Cpunt non divisibles
vector<int> nonDivisibles(vector<int> A) 
{
	int nIntCount = A.size(); 
	int nMaxInt = 2 * nIntCount; 
	vector<int>  anIntCounts (nMaxInt + 1); 
											
	vector<int>  anDivisorCounts (nMaxInt + 1);
	vector<int>  anNotDivCounts(nIntCount); 
	for(int a : A) 
		anIntCounts[a]++;
	for (int i = 0; i <= nMaxInt; i++) 
		if (anIntCounts[i] > 0) 
			for (int im = i; im <= nMaxInt; im += i) 
													
				anDivisorCounts[im] += anIntCounts[i]; 
													   
	for (int i = 0; i < nIntCount; i++)
		anNotDivCounts[i] = nIntCount - anDivisorCounts[A[i]];
															   
	return anNotDivCounts;
}

//common prime divisors
bool containedSet(int M, int N) {
	int g = gcd(min(N, M), max(N, M));
	while (g != 1) {
		M /= g;
		g = gcd(min(N, M), max(N, M));
	}
	return M == 1;
}


int solution(vector<int>& A, vector<int>& B) {
	int ans = 0;
	for (unsigned i = 0; i < A.size(); ++i)
	{
		//divisor A contained in divisor of B
		//divisor A contained in divisor of A
		//implies divisor A =  divisor of B 
		if (containedSet(A[i], B[i]) && containedSet(B[i], A[i]))
			ans++;

	}
	return ans;
}

//
int dynamicFibbonaci(int n)
{
	vector<int> fibs(n + 2);
	fibs[0] = 0;
	fibs[1] = 1;
	int i = 2;

	while (i != n + 1)
	{
		fibs[i] = fibs[i - 1] + fibs[i - 2];
		i++;
	}

	return fibs[n];
}

//fibonacci frog jumps
int fibFrog(vector<int> &A) {
	// write your code in C++14 (g++ 6.2.0)
	int N = A.size();

	vector<int> fib;
	fib.push_back(1);
	fib.push_back(1);
	while (fib[fib.size() - 1] <= N + 1) fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);

	set<int> positions;
	positions.insert(N);
	for (int j = 1; ; j++)
	{
		set<int> indexes;
		for (int i : positions)
		{
			for (int f : fib)
			{
				int p = i - f;
				if (p == -1) return j;
				if (p < 0) break;
				if (A[p]) indexes.insert(p);
			}
		}
		if (indexes.size() == 0)
			return -1;
		positions = indexes;
	}

	return -1;
}

//binary search
int search(vector<int> A, int element)
{
	int begin = 0;
	int end = A.size() - 1;
	int result;

	while (begin <= end)
	{
		int mid = (begin + end) / 2;
		if (A[mid] < element)
		{
			begin = mid + 1;
			result = mid;
		}
		else
		{
			end = mid - 1;
		}
	}

	return result;
}

// MinMaxDivision
int MinMaxDivision(int K, int M, vector<int> &A) {
	int len = A.size();
	long long high = accumulate(A.begin(), A.end(), 0ll);
	long long low = *std::max_element(A.begin(), A.end());
	long long m, sum;
	int partition;
	while (low < high)
	{
		m = low + (high - low) / 2;
		partition = 1;
		sum = 0;
		for (int i = 0; i < len; ++i)
		{
			if (sum + A[i] <= m)
				sum += A[i];
			else
			{
				++partition;
				sum = A[i];
			}
		}
		if (partition <= K)
			high = m;
		else
			low = m + 1;
	}
	return (int)low;
}

