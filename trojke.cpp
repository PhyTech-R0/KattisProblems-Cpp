#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define mp make_pair

//Hash struct to create unordered_map with pairs
struct pair_hash
{
    template<class T1, class T2>
        size_t operator() (const pair<T1,T2> &p) const {
            auto h1 = hash<T1>{}(p.first);
            auto h2 = hash<T2>{}(p.second);
            return h1^h2;
        }
};


// Get pair of points (x,y). Calculate slope with help of gcd to prevent precision problems.
int maxPointOnSameLine(vector<pair<int,int>> points)
{
    int N = points.size();
    if(N < 2)
        return N;

    int maxPoint = 0;
    int curMax, overlapPoints, verticalPoints;
    unordered_map<pair<int,int>, int, pair_hash> slopeMap;

    for(int i=0; i<N; i++)
    {
        curMax = overlapPoints = verticalPoints = 0;
        //Loop from i+1 to ignore same pair
        for(int j=i+1; j<N; j++)
        {
            //If points are equal increase overlap
            if(points[i] == points[j])
                overlapPoints++;
            //If x coordinate is same, increment vertical
            else if(points[i].first == points[j].first)
                verticalPoints++;
            else
            {
                int yDif = points[j].second - points[i].second;
                int xDif = points[j].first - points[i].first;
                int g = __gcd(xDif, yDif);

                //Reduce diff by gcd
                xDif /= g;
                yDif /= g;

                slopeMap[make_pair(yDif, xDif)]++;
                curMax = max(curMax, slopeMap[make_pair(yDif, xDif)]);
            }

            curMax = max(curMax, verticalPoints);
        }


        //Update global maximum by current points maximum
        maxPoint = max(maxPoint, curMax + overlapPoints + 1);
        slopeMap.clear();
    }
    return maxPoint;
}



int main()
{
    int n; cin >> n;

    vector<pair<int,int>> points;

    for(int i=0;i<n;i++)
    {
        string s; cin >> s;

        for(int j=0; j<s.length(); j++)
        {
            if(s[j] != '.')
                points.push_back(mp(i, j));
        }
    }

	int ans = 0;

	for(int i=0; i<points.size(); i++)
	{
		for(int j=i+1; j<points.size(); j++)
		{
			for(int k=j+1; k<points.size(); k++)
			{
				if(maxPointOnSameLine(vector<pair<int,int>>{points[i],points[j],points[k]})>=3)
					ans++;
			}
		}
	}

	cout << ans << endl;



    return 0;

}
