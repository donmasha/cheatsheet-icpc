int egcd(int a, int b, int & x, int & y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }
  int x1, y1;
  int d = egcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

int inv(int a, int b) {
  int x, y;
  int g = egcd(a, b, x, y);
  assert(g == 1); // inverse has to exist
  return (x % b + b) % b;
}

int findMinX(int num[], int rem[], int k) {
  int prod = 1;
  for (int i = 0; i < k; i++) {
    prod *= num[i];
  }
  int res = 0;
  for (int i = 0; i < k; i++) {
    int pp = prod / num[i];
    res += (rem[i] * inv(pp, num[i]) * pp) % prod;
  }
  return res % prod;
}