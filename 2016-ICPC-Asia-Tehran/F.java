import java.util.*;
import java.math.BigInteger;
import java.lang.Math.*;

public class F
{
    private static class Frac
    {
        public BigInteger n, d;
        public Frac() {}
        public Frac(BigInteger x)
        {
            n = x;
            d = new BigInteger("1");
        }
        private void cancel()
        {
            if (d.compareTo(BigInteger.ZERO) == -1) {
                BigInteger mone = BigInteger.ZERO.subtract(BigInteger.ONE);
                d = d.multiply(mone);
                n = n.multiply(mone);
            }
            BigInteger g = n.gcd(d);
            n = n.divide(g);
            d = d.divide(g);
        }
        public Frac add(Frac a)
        {
            Frac b = new Frac();
            b.n = n.multiply(a.d).add(a.n.multiply(d));
            b.d = d.multiply(a.d);
            b.cancel();
            return b;
        }
        public Frac subtract(Frac a)
        {
            Frac b = new Frac();
            b.n = n.multiply(a.d).subtract(a.n.multiply(d));
            b.d = d.multiply(a.d);
            b.cancel();
            return b;
        }
        public Frac multiply(Frac a)
        {
            Frac b = new Frac();
            b.n = n.multiply(a.n);
            b.d = d.multiply(a.d);
            b.cancel();
            return b;
        }
        public Frac divide(Frac a)
        {
            Frac b = new Frac();
            b.n = n.multiply(a.d);
            b.d = d.multiply(a.n);
            b.cancel();
            return b;
        }
    }

    private static class SolExp
    {
        Stack<Frac> S1;
        Stack<Character> S2;
        
        public SolExp()
        {
            S1 = new Stack<Frac>();
            S2 = new Stack<Character>();
        }

        private int pri(char c)
        {
            switch (c) {
                case '(': return 0;
                case '+':
                case '-': return 1;
                case '*':
                case '/': return 2;
            }
            return -1;
        }

        private Frac cal(Frac a, Frac b, char c)
        {
            switch (c) {
                case '+': return a.add(b);
                case '-': return a.subtract(b);
                case '*': return a.multiply(b);
                case '/': return a.divide(b);
            }
            return new Frac();
        }

        private boolean calOnce()
        {
            if (S1.size() < 2 || S2.isEmpty()) return false;
            char op = S2.peek(); S2.pop();
            if (op == '(') return false;
            Frac b = S1.peek(); S1.pop();
            Frac a = S1.peek(); S1.pop();
            Frac c = cal(a, b, op);
            S1.push(c);
            return true;
        }

        public Frac work(String S)
        {
            S1.clear(); S2.clear();
            for (int i = 0; i < S.length(); i ++) {
                char c = S.charAt(i);
                if (c == '(' || c == '+' || c == '-' ||
                    c == '*' || c == '/' || c == '%') {
                    while(!S2.isEmpty() && c != '(' &&
                          pri(c) <= pri(S2.peek())) {
                        calOnce();
                    }
                    S2.push(c);
                } else if (c >= '0' && c <= '9') {
                    BigInteger x = new BigInteger("0");
                    for (; i < S.length(); i ++) {
                        c = S.charAt(i);
                        if (c < '0' || c > '9') break;
                        String tmp = ""; tmp += c;
                        x = x.multiply(BigInteger.TEN).add(new BigInteger(tmp));
                    }
                    i --;
                    S1.push(new Frac(x));
                } else if (c == ')') {
                    while (calOnce());
                }
            }
            while (calOnce());
            return S1.peek();
        }
    }

    static String[] S;
    static String exp;

    public static void trans(int x1, int x2, int y1, int y2)
    {
        boolean ex = false;
        int idx_x = -1, idx_y = -1;
        for (int j = y1; j <= y2; j ++) {
            for (int i = x1; i <= x2; i ++) {
                if (j >= S[i].length()) continue;
                char c = S[i].charAt(j);
                if (c == '-' || (c >= '0' && c <= '9')) {
                    idx_x = i; idx_y = j;
                    ex = true; break;
                }
            }
            if (ex) break;
        }
        exp += " ( ";
        int l = 1000, r = -1, len = Math.min(y2, S[idx_x].length() - 1);
        for (int i = idx_y; i <= len; i ++) {
            char c = S[idx_x].charAt(i);
            if (c == '-') {
                l = Math.min(l, i);
                r = Math.max(r, i);
            } else {
                if (l <= r) {
                    trans(x1, idx_x - 1, l, r);
                    exp += " / ";
                    trans(idx_x + 1, x2, l, r);
                }
                l = 1000; r = -1;

                if (c == '+' || c == '*') {
                    exp += " " + c + " ";
                } else if (c >= '0' && c <= '9') {
                    exp += c;
                }
            }
        }
        exp += " ) ";
    }

    public static void main(String[] args)
    {
        S = new String[70];
        Scanner sin = new Scanner(System.in);
        SolExp sol = new SolExp();
        int N;
        while ((N = sin.nextInt()) > 0) {
            sin.nextLine();
            int big = 0;
            for (int i = 0; i < N; i ++) {
                S[i] = sin.nextLine() + " ";
                big = Math.max(big, S[i].length());
            }
            exp = "";
            trans(0, N - 1, 0, big - 1);
            Frac ans = sol.work(exp);
            System.out.printf("%s/%s\n", ans.n, ans.d);
        }
    }
}
