import java.util.*;
import java.math.BigInteger;
import java.lang.Math.*;

public class Main
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
    public static boolean leq(Frac a, Frac b)
    {
        BigInteger _a = a.n.multiply(b.d); 
        BigInteger _b = b.n.multiply(a.d);
        if (_a.equals(_a.min(_b))) return true;
        else return false;
    }
    private static class Point
    {
        public Frac x, y;
        public Point() { x = new Frac(); y = new Frac(); }
        public Point(long a, long b)
        {
            x = new Frac(new BigInteger("" + a));
            y = new Frac(new BigInteger("" + b));
        }
    }
    private static class Line
    {
        public Point a, b;
        public Line() { a = new Point(); b = new Point(); }
    }
    public static Point intersection(Line u, Line v)
    {
        Point ret = u.a;
        Frac t1 = u.a.x.subtract(v.a.x).multiply(v.a.y.subtract(v.b.y));
        Frac t2 = u.a.y.subtract(v.a.y).multiply(v.a.x.subtract(v.b.x));
        Frac t3 = u.a.x.subtract(u.b.x).multiply(v.a.y.subtract(v.b.y));
        Frac t4 = u.a.y.subtract(u.b.y).multiply(v.a.x.subtract(v.b.x));
        Frac t = t1.subtract(t2).divide(t3.subtract(t4));
        ret.x = ret.x.add(u.b.x.subtract(u.a.x).multiply(t));
        ret.y = ret.y.add(u.b.y.subtract(u.a.y).multiply(t));
        return ret;
    }
    public static void printP(Point a)
    {
        System.out.printf("point: %d/%d, %d/%d\n", a.x.n, a.x.d, a.y.n, a.y.d);
    }

    public static Point circumcenter(Point a, Point b, Point c)
    {
        Line u = new Line();
        Line v = new Line();
        u.a.x = a.x.add(b.x).divide(new Frac(new BigInteger("2")));
        u.a.y = a.y.add(b.y).divide(new Frac(new BigInteger("2")));
        u.b.x = u.a.x.subtract(a.y).add(b.y);
        u.b.y = u.a.y.add(a.x).subtract(b.x);
        v.a.x = a.x.add(c.x).divide(new Frac(new BigInteger("2")));
        v.a.y = a.y.add(c.y).divide(new Frac(new BigInteger("2")));
        v.b.x = v.a.x.subtract(a.y).add(c.y);
        v.b.y = v.a.y.add(a.x).subtract(c.x);
        //printP(u.a); printP(u.b);
        //printP(v.a); printP(v.b);
        return intersection(u, v);
    }
    public static Frac dist(Point a, Point b)
    {
        Point C = new Point();
        C.x = a.x.subtract(b.x);
        C.y = a.y.subtract(b.y);
        Frac ret = C.x.multiply(C.x).add(C.y.multiply(C.y));
        return ret;
    }
    public static boolean judge(Point a, Point b, Point c, Point d)
    {
        //System.out.printf("a = %d/%d, %d/%d\n", a.x.n, a.x.d, a.y.n, a.y.d);
        //System.out.printf("b = %d/%d, %d/%d\n", b.x.n, b.x.d, b.y.n, b.y.d);
        //System.out.printf("c = %d/%d, %d/%d\n", c.x.n, c.x.d, c.y.n, c.y.d);
        Point O = circumcenter(a, b, c);
        //System.out.printf("%d/%d, %d/%d\n", O.x.n, O.x.d, O.y.n, O.y.d);
        //
        Frac d1 = dist(O, a);
        Frac d2 = dist(O, d);
        
        //System.out.printf("%d/%d\n", d1.n, d1.d);
        //System.out.printf("%d/%d\n", d2.n, d2.d);
        if (leq(d2, d1))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    public static void main(String[] args)
    {
        Scanner sin = new Scanner(System.in);
        int T = sin.nextInt();
        for (int _c = 0; _c < T; _c ++) {
            long x1 = sin.nextLong();
            long y1 = sin.nextLong();
            long x2 = sin.nextLong();
            long y2 = sin.nextLong();
            long x3 = sin.nextLong();
            long y3 = sin.nextLong();
            long x4 = sin.nextLong();
            long y4 = sin.nextLong();
            Point A = new Point(x1, y1);
            Point B = new Point(x2, y2);
            Point C = new Point(x3, y3);
            Point D = new Point(x4, y4);
            if (judge(A, B, C, D))
            {
                System.out.println("Accepted");
            }
            else
            {
                System.out.println("Rejected");
            }
        }
    }
}
