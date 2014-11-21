#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
Object should hav  obj(&obj)

*/

template <typename T> class IntervalTree {
public:
	int size, start;
	vector <T> leafs;
	vector <T> tree;
	T(*func)(T, T);
	T defaultCustomValue;

	void setValues() {
		size = leafs.size();
		tree.resize(size * 4);
		build(1, 0, size - 1);
	}
	IntervalTree() {}
	IntervalTree(vector <T> & leafs, T(*func)(T, T), T defaultCustomValue) :
		leafs(leafs), func(func), defaultCustomValue(defaultCustomValue)
	{
		setValues();
	}
	IntervalTree(int size, T defaultCustomValue, T(*func)(T, T)) :
		func(func), leafs(size, defaultCustomValue), defaultCustomValue(defaultCustomValue)
	{
		setValues();
	}
	void build(int i, int tl, int tr) {
		if (tl == tr) {
			tree[i] = leafs[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(i * 2, tl, tm);
		build(i * 2 + 1, tm + 1, tr);
		tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
	}


	void update(int pos, T & new_val, int i, int tl, int tr) {
		if (tr == -1) tr = size - 1;
		if (tl == tr)
			tree[i] = new_val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm)
				update(pos, new_val, i * 2, tl, tm);
			else
				update(pos, new_val, i * 2 + 1, tm + 1, tr);
			tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
		}
	}


	void update(int pos, T & new_val) {
		update(pos, new_val, 1, 0, size - 1);
	}


	T get(int v, int tl, int tr, int customL, int customR) {
		if (customL > customR)
			return 0;
		if (customL == tl && customR == tr)
			return tree[v];
		int tm = (tl + tr) / 2;
		T ansl = get(v * 2, tl, tm, customL, min(customR, tm));
		T ansr = get(v * 2 + 1, tm + 1, tr, max(customL, tm + 1), customR);
		return func(ansl, ansr);
	}

	T get(int customL, int customR) {
		return get(1, 0, size - 1, customL, customR);
	}


};

int maxInt(int a, int b) {
	return max(a, b);
}

int main() {
	IntervalTree < int > it(3, 0, maxInt);
	int ans = 3;
	{
		int x = 3;
		it.update(0, x);
	}
	ans = it.get(0, 1);
	cout << ans;
	cin >> ans;
	return 0;
}