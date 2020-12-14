vector < int > prefix_function(string s) {
  int n = (int) s.length();
  vector < int > pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

void KMPSearch(string pat, string txt) {
  int M = pat.size();
  int N = txt.size();
  vector < int > lps = prefix_function(pat);
  int i = 0, j = 0;
  while (i < N) {
    if (pat[j] == txt[i]) {
      i++, j++;
    }
    if (j == M) {
      cout << "Found pattern at index " << i - j << "\n";
      j = lps[j - 1];
    }
    else if (i < N && pat[j] != txt[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
}