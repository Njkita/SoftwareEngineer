#include <iostream>
#include <string>
#include <vector>

std::string longestPalindrome(const std::string &s) {
  if (s.empty())
    return "";

  int n = s.size();
  int start = 0, maxLength = 1;

  std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

  for (int i = 0; i < n; ++i) {
    dp[i][i] = true;
  }

  for (int i = 0; i < n - 1; ++i) {
    if (s[i] == s[i + 1]) {
      dp[i][i + 1] = true;
      start = i;
      maxLength = 2;
    }
  }

  for (int len = 3; len <= n; ++len) {
    for (int i = 0; i < n - len + 1; ++i) {
      int j = i + len - 1;
      if (s[i] == s[j] && dp[i + 1][j - 1]) {
        dp[i][j] = true;

        if (len > maxLength) {
          start = i;
          maxLength = len;
        }
      }
    }
  }

  return s.substr(start, maxLength);
}

int main() {
  std::string input;
  std::cin >> input;

  std::string result = longestPalindrome(input);
  std::cout << result << std::endl;

  return 0;
}