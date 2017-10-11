/* a ^ x = b (mod c), O(sqrt(c)) */
#define SIZE SQRT_OF_MAX_C
pll M[SIZE];
ll BSGS(ll a, ll b, ll c)
{
  ll m = ceil(sqrt(1.0 * c)) + 1, x = b;
  for (int i = 0; i < m; i ++) {
    M[i] = pll(x, i); x = mul(x, a, c);
  }
  sort(M, M + m);
  ll y = x = qp(a, m, c);
  for (int i = 1; i < m; i ++) {
    pll *it = lower_bound(M, M + m, pll(x, -1));
    if (it != M + m && it->first == x) {
      return i * m - it->second;
    }
    x = mul(x, y, c);
  }
  return -1;
}
