import java.util.Scanner;

public class Checksum16Bit {
    public static int calculateChecksum(int[] data, int length) {
        int sum = 0;
        for (int i = 0; i < length; i++) {
            sum += data[i];
            if ((sum & 0x10000) != 0) { 
                sum = (sum & 0xFFFF) + 1; 
            }
        }
        return (~sum) & 0xFFFF; 
    }

    public static Integer parseHexString(String hexStr) {
        if (hexStr.length() != 4) return null;
        if (!hexStr.matches("[0-9a-fA-F]{4}")) return null;
        try {
            int val = Integer.parseInt(hexStr, 16);
            if (val > 0xFFFF) return null;
            return val;
        } catch (NumberFormatException e) {
            return null;
        }
    }

  public static void printCharBinary(char c) {
        for (int i = 7; i >= 0; i--) {
            System.out.print(((c >> i) & 1) == 1 ? '1' : '0');
        }
    }

    public static void printOnesComplement(char c) {
        char comp = (char) (~c);
        for (int i = 7; i >= 0; i--) {
            System.out.print(((comp >> i) & 1) == 1 ? '1' : '0');
        }
    }

    public static void main(String[] args) {
        final int MAX_VALUES = 100;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter a string (max " + MAX_VALUES + " characters): ");
        String input = scanner.nextLine();

        if (input.length() > MAX_VALUES) {
            input = input.substring(0, MAX_VALUES);
        }

        if (input.length() == 0) {
            System.out.println("Empty input.");
            scanner.close();
            return;
        }

        int length = input.length();
        int[] data = new int[length];
        for (int i = 0; i < length; i++) {
            data[i] = (int) input.charAt(i);
        }

        int checksum = calculateChecksum(data, length);

        System.out.println("Hex values of input characters:");
        for (int i = 0; i < length; i++) {
            System.out.printf("%04X ", data[i]);
        }
        System.out.println();

        System.out.println("ASCII characters to binary and their 1's complement:");
        for (int i = 0; i < length; i++) {
            char ch = input.charAt(i);
            System.out.print(ch + ": ");
            printCharBinary(ch);
            System.out.print("  |  1's complement: ");
            printOnesComplement(ch);
            System.out.println();
        }

        System.out.printf("Calculated checksum: %04X\n", checksum);

        System.out.print("Enter receiver end checksum (4 hex characters): ");
        String receiverChecksumStr = scanner.nextLine().trim();

        Integer receiverChecksum = parseHexString(receiverChecksumStr);
        if (receiverChecksum == null) {
            System.out.println("Invalid checksum input.");
            scanner.close();
            return;
        }

        if (receiverChecksum == checksum) {
            System.out.println("Transmission is correct.");
        } else {
            System.out.println("Transmission error detected.");
        }

        scanner.close();
    }
}
