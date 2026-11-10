#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord,
                     std::vector<std::string>& wordList) {
        std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0;
        dict.erase(beginWord);

        std::queue<std::string> q;
        q.push(beginWord);
        int steps = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                std::string word = q.front();
                q.pop();
                if (word == endWord) return steps;

                for (int j = 0; j < static_cast<int>(word.size()); ++j) {
                    char original = word[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        word[j] = c;
                        if (dict.count(word)) {
                            q.push(word);
                            dict.erase(word);
                        }
                    }
                    word[j] = original;
                }
            }
            ++steps;
        }

        return 0;
    }
};
