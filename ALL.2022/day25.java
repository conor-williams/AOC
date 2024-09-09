import java.math.BigInteger;
import java.util.Scanner;
class day25 {
	//public static String blah[] = { "1=-0-2", "12111", "2=0=", "21", "2=01", "111", "20012", "112", "1=-1=", "1-12", "12", "1=", "122" };
	public static String blah[] = {
"1",
"2",
"1=",
"1-",
"10",
"11",
"12",
"2=",
"2-",
"20",
"1=0",
"1-0",
"1=11-2",
"1-0---0",
"1121-1110-1=0"};
	public static Scanner ui = new Scanner(System.in);
	/*public static String blah[] =  {
		"2-==122-=11202",
		"1-0==",
		"2=2=-0020-0=20",
		"1011=121-210-==",
		"1-00-20-02=2",
		"1-20--22-=0===1-",
		"20",
		"110=0",
		"110=22",
		"1--1-1=2--==00",
		"2=",
		"1-1020-0=0",
		"111=2==1-=11",
		"2=021--",
		"2=--=22==01",
		"1==21201-2--0-2102",
		"220=20-2=22-01-",
		"1=01-0=0201=2=-",
		"1=0",
		"1-21",
		"1=00-=",
		"22=11=21==-00212",
		"1=1=-2-0=202=0202",
		"101",
		"11-=2-=-22200",
		"21",
		"11=2=",
		"111",
		"102=201=-=01-===-0",
		"1=-11",
		"1=-020011",
		"1210100012-1==0-2",
		"101==0-00-",
		"1-=100==10-11022",
		"101-1=10=-0120-0",
		"102=-120",
		"1---10=-12=000==2",
		"1=-",
		"122=-1=00--2=0120-=",
		"1-0==02",
		"21-1-00220",
		"1=0--=121==",
		"12=10--2==-11102==",
		"1-2==-",
		"1-=121-112",
		"2--011001",
		"1=10-202-1",
		"10--=2=-=012=2==-",
		"1==1=00111=101-21-2",
		"1=11",
		"11-111=2-1101",
		"22000-110122220=",
		"20=22-11-2=212-=",
		"1012---=2-112",
		"1=1001=0--20==0-01",
		"202=22=2-1-==",
		"10=1",
		"1-=1=020021-2",
		"200=221=00",
		"1--100=20-02===11",
		"1=0=01-222==-=",
		"1=-==02-12==",
		"1-2-=1===-2=",
		"1-=10=21",
		"1-21--1-=2=",
		"1-212=-=1211=1",
		"1002",
		"2==221-=01-11==",
		"1=01--=--22=",
		"1011==---21-0",
		"11",
		"1111===1-1=1-=0",
		"1=1=2111=2=0122=-11",
		"102000--=-0101",
		"1=2=",
		"12-=2-",
		"210110=11-010=",
		"1==02-1120=-012-2--",
		"101-2=2220=1",
		"1=0-1-201--212",
		"1---02102=22-2-2",
		"1=--0021-2==",
		"1021112120011",
		"2=102=-=",
		"1-0",
		"1=",
		"1==20",
		"1=0211-00-==",
		"2-1",
		"10=01-21220==0-",
		"2-00",
		"2--==-==0-0012",
		"102=2=1101220",
		"1-==2-22-20200=",
		"2--=01=0210=",
		"2010--=0=110-=1=--",
		"1==1=",
		"1-=-0011-2-",
		"2-0",
		"1=-02-2=0201",
		"1-0-12-110====0-",
		"1==21",
		"120121-2",
		"2=010=21--1=0",
		"10=0==00=1==0--=1000",
		"1-=000-=-=0-20",
		"1200",
		"1---=2-==",
		"1-=1--011"};
	*/
	public static void main(String [] args) {
		BigInteger totOfNums = BigInteger.valueOf((long)0);
		for (int i = 0; i < blah.length; i++) {
			//System.out.println(blah[i]);
			ui.nextLine();
			BigInteger thisNum = BigInteger.valueOf((long)0);
			for (int z = blah[i].length() -1; z >= 0; z--) {
				//System.out.println(blah[i].charAt(z));
				long po = ((long)(blah[i].length() - 1 - z));
				BigInteger sz = BigInteger.valueOf((long)(Math.pow(5, po))); 
				//System.out.println("pow: " + sz);
				BigInteger num = BigInteger.valueOf(0);
				switch (blah[i].charAt(z)) {
					case ('2') :
						//System.out.println("two");
						num = BigInteger.valueOf(2);
						break;
					case ('1') :
						//System.out.println("one");
						num = BigInteger.valueOf(1);
						break;
					case ('0') :
						//System.out.println("zero");
						num = BigInteger.valueOf(0);
						break;
					case ('-') :
						//System.out.println("minus");
						num = BigInteger.valueOf(-1);
						break;
					case ('=') :
						//System.out.println("equal");
						//num = new BigInteger(BigInteger.valueOf(-2));
						num = BigInteger.valueOf(-2);
						break;
					default:
						//System.out.println("here1 should not be here\n");
						break;
				}
				//System.out.println(sz.multiply(num));
				thisNum = thisNum.add(sz.multiply(num));
				//System.out.println(thisNum);
			}
			System.out.println("+ " + thisNum);
			totOfNums = totOfNums.add(thisNum);
		}
		//System.out.println("** totOfNums: " + totOfNums);
	}
}
