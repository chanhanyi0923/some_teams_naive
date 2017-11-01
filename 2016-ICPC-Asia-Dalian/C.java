import java.util.*;
import java.math.BigDecimal;

public class Main
{
    private static BigDecimal sqrt(int N)
    {
        BigDecimal L = new BigDecimal("1");
        BigDecimal R = BigDecimal.valueOf(N);
        BigDecimal TWO = BigDecimal.valueOf(2);
        BigDecimal TEN = BigDecimal.valueOf(10);
        BigDecimal eps = TEN;

        for (int i = 0; i < 120; i ++) {
            eps = eps.divide(TEN, 120, BigDecimal.ROUND_DOWN);
        }
        while (R.subtract(L).compareTo(eps) > 0) {
            BigDecimal mid = L.add(R).divide(TWO, 120, BigDecimal.ROUND_DOWN);
            if (mid.multiply(mid).compareTo(BigDecimal.valueOf(N)) > 0) {
                R = mid;
            } else {
                L = mid;
            }
        }
        return L;
    }
    public static void main(String args[])
    {
        Scanner sin = new Scanner(System.in);
        BigDecimal a, b;
        BigDecimal sqrt5 = sqrt(5);
        BigDecimal gold = sqrt5.add(BigDecimal.valueOf(1));
        while (sin.hasNext()) {
            a = sin.nextBigDecimal();
            b = sin.nextBigDecimal();
            if (a.compareTo(b) > 0) {
                BigDecimal t = b; b = a; a = t;
            }
            BigDecimal x = b.subtract(a).multiply(gold).divide(BigDecimal.valueOf(2));
            x = x.setScale(0, BigDecimal.ROUND_DOWN);

            if (x.equals(a)) {
                System.out.println("0");
            } else {
                System.out.println("1");
            }
        }
    }
}