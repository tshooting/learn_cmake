#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int maxCompatibilitySum(vector<vector<int> > &students, vector<vector<int> > &mentors)
    {
        int n = students.size();
        vector<vector<int> > c(n, vector<int>(n, 0)); // student[i]与teacher[j]的兼容性,相当于是权重
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int K = students[i].size();
                for (int k = 0; k < K; ++k)
                {
                    c[i][j] += students[i][k] == mentors[j][k];
                }
            }
        }
        // 左右顶点个数相等，都为n，然后权重也给了
        return KM(n, c);
    }

    int KM(int n, vector<vector<int> > &c)
    {
        // match[i]是每一个老师匹配的学生的编号
        vector<int> match(n, -1);    // match[i]为teacher[i]匹配的student编号
        vector<int> exStudent(n);    // student的期望
        vector<int> exTeacher(n, 0); // teacher的期望
        // 学生是左边的顶点，老师是右边的顶点，我们记录的时候，记录的是右边的顶点匹配上左边哪个顶点了
        for (int i = 0; i < n; ++i)
        {
            exStudent[i] = *max_element(c[i].begin(), c[i].end());
        }
        // 为每个student匹配teacher
        for (int i = 0; i < n; ++i)
        {
            while (true)
            {
                // 首先我们会记录顶点有没有被使用过，每一次都会进行初始化
                vector<bool> visStudent(n, false);
                vector<bool> visTeacher(n, false);
                // 目前左侧顶点的idx，顶点个数，权重，match的情况，以及使用情况，左右顶点的权重
                if (dfs(i, n, c, match, visStudent, visTeacher, exStudent, exTeacher))
                {
                    break;
                }
                // 无法匹配降低期望，会不会进行死锁的情况，这种情况会进行死锁的
                for (int j = 0; j < n; ++j)
                {
                    if (visStudent[j])
                        exStudent[j]--;
                    if (visTeacher[j])
                        exTeacher[j]++;
                }
            }
        }
        cout << "print match " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "left_idx = " << match[i] << ",match_right_idx = " << i << endl;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += c[match[i]][i];
        }
        return ans;
    }

    // 匈牙利算法寻找完美匹配
    bool dfs(int i, int n, vector<vector<int> > &c, vector<int> &match, vector<bool> &visStudent, vector<bool> &visTeacher, vector<int> &exStudent, vector<int> &exTeacher)
    {
        // 左侧是student
        visStudent[i] = true;
        for (int j = 0; j < n; ++j)
        {
            // 如果说这个右侧顶点已经被访问过 我们就不进行访问
            if (visTeacher[j])
            {
                continue;
            }
            if (c[i][j] == -1000)
            {
                continue;
            }
            int diff = exStudent[i] + exTeacher[j] - c[i][j];
            if (!diff)
            {
                // 相当于匹配上了，如果右侧没有被匹配过那么就return true 结束，如果已经被匹配过，那么match[j]就要去重新匹配
                visTeacher[j] = true;
                if (match[j] == -1 || dfs(match[j], n, c, match, visStudent, visTeacher, exStudent, exTeacher))
                {
                    match[j] = i;
                    return true;
                }
            }
        }
        return false;
    }
};
int main()
{
    Solution solution;
    int n = 3;
    vector<vector<int> > weights(n, vector<int>(n));

    int tmp_weights[n][n] = {{1, -1000, -1000},
                             {4, 3, -1000},
                             {-1000, 4, 5}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            weights[i][j] = tmp_weights[i][j];
        }
    }
    cout << "ans = " << solution.KM(3, weights) << endl;
    return 0;
}