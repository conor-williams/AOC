import java.math.BigInteger;
import java.util.Scanner;

class day25snafu {
	public static String blah[] = {"34818266939311"};
	public static BigInteger blah2 = new BigInteger("34818266939311");
	public static Scanner ui = new Scanner(System.in);
	//base 514030430302314024221
	public static void main(String [] args) {
		
		for (int i = 0; i < 21; i++) {
			System.out.println("Base: 10: " + i);
			System.out.print("Base: snafu: ");
			switch(i) {
				case 0:
					System.out.println("0");
					break;
				case 1:
					System.out.println("1");
					break;
				case 2:
					System.out.println("2");
					break;
				case 3:
					System.out.println("5 - 2 == 1=");
					break;
				case 4:
					System.out.println("5 - 1 == 1-");
					break;
				case 5:
					System.out.println("10");
					break;
				case 6:
					System.out.println("11");
					break;
				case 7:
					System.out.println("12");
					break;
				case 8:
					System.out.println("2=");
					break;
				case 9:
					System.out.println("2-");
					break;
				case 10:
					System.out.println("20");
					break;
				case 11:
					System.out.println("21");
					break;
				case 12:
					System.out.println("22");
					break;
				case 13:
					System.out.println("15 - 2 == 3=");
					break;
				case 14:
					System.out.println("15 - 1 == 3-");
					break;
				case 15:
					System.out.println("15 == 30");
					break;
				case 16:
					System.out.println("31");
					break;
				case 17:
					System.out.println(32);
					break;
				case 18:
					System.out.println("4=");
					break;
				case 19:
					System.out.println("4-");
					break;
				case 20:
					System.out.println("40");
					break;
			}
			
			///Integer.parseInt(String.valueOf(i), 10), 5);
			//int zz = Integer.toString(i, 5);
			//int zz = Integer.parseInt(String.valueOf(i), 5);
		    	String zz = Integer.toString(Integer.parseInt(String.valueOf(i), 10), 5);

			System.out.println("Base: 5:" + zz);
			System.out.println("----------------");
/*
			String blah = String.valueOf(i);
			for (int k = 0; k < blah.length; k++) {
			}
*/
				
		}
		//String zz2 = Integer.toString(Integer.parseInt(blah[0], 10), 5);
		String value = blah2.toString(5);
		System.out.println(blah[0] + "base 5: " + value);
		System.out.println(value.charAt(1));

		char [] oldVal = value.toCharArray();
		char [] newVal = new char[30];
		//for (int kk = 0; kk < value.length(); kk++) 
		for (int kk = value.length()-1; kk >= 0; kk--) {
			if (oldVal[kk] == '5') {
				newVal[kk] = '0';
				oldVal[kk-1] = (char)(Character.getNumericValue(oldVal[kk-1]) + 49);
			} else if (oldVal[kk] == '4') {
				newVal[kk] = '-';
				oldVal[kk-1] = (char)(Character.getNumericValue(oldVal[kk-1]) + 49);
			} else if (oldVal[kk] == '3') {
				newVal[kk] = '=';
				oldVal[kk-1] = (char)(Character.getNumericValue(oldVal[kk-1]) + 49);
			} else {
				newVal[kk] = oldVal[kk];
			}
		}
		newVal[value.length()] = '\0';
		System.out.println("NewVal:");
		System.out.println(newVal);
					
/*
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
*/
		//System.out.println("** totOfNums: " + totOfNums);
	}
}
