import java.util.Scanner;

public class Checksum16bit {
    
    // Function to convert int → 16-bit binary string
    static String toBinary16(int val) {
        return String.format("%16s", Integer.toBinaryString(val & 0xFFFF)).replace(' ', '0');
    }

    // Function to calculate 16-bit checksum
    static String checksumFunc(String[] datawords, int n, boolean showSteps) {
        int sum = 0;
        
        // Add all words
        for (int i = 0; i < n; i++) {
            int val = Integer.parseInt(datawords[i], 16);
            sum += val;
            
            // Wrap-around carry until within 16 bits
            while (sum > 0xFFFF) {
                sum = (sum & 0xFFFF) + 1;
            }
        }
        
        if (showSteps) {
            System.out.printf("Sum before 1's complement = %04X  (%s)\n", sum, toBinary16(sum));
        }

        // One’s complement (16-bit)
        int checksumVal = ~sum & 0xFFFF;

        if (showSteps) {
            System.out.printf("After 1's complement      = %04X  (%s)\n", checksumVal, toBinary16(checksumVal));
        }
        
        // Return as uppercase hex (4-digit padded)
        return String.format("%04X", checksumVal);
    }

    // Function to corrupt 1 bit in the received data
    static String corruptOneBit(String hexWord) {
        int val = Integer.parseInt(hexWord, 16);
        // Flip (XOR) the least significant bit
        val = val ^ 0x0001;  
        return String.format("%04X", val);
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter total number of hex codes: ");
        int n = sc.nextInt();

        String[] datawords = new String[n];
        System.out.println("Enter hex codes:");
        for (int i = 0; i < n; i++) {
            datawords[i] = sc.next();
        }

        // Sender’s Checksum (show steps here)
        String sentChecksum = checksumFunc(datawords, n, true);
        System.out.println("Sent Checksum = " + sentChecksum);

        // Receiver’s End
        System.out.println("\n******** AT RECEIVER'S END ********");
        String[] receivedDatawords = new String[n + 1];
        for (int i = 0; i < n; i++) receivedDatawords[i] = datawords[i];
        receivedDatawords[n] = sentChecksum;

        System.out.println("Received Data (before corruption):");
        for (String word : receivedDatawords) {
            System.out.println(word);
        }

        // CORRUPT one bit in the first word
        receivedDatawords[0] = corruptOneBit(receivedDatawords[0]);
        System.out.println("\nReceived Data (after corruption):");
        for (String word : receivedDatawords) {
            System.out.println(word);
        }

        // Now check checksum
        String receivedChecksum = checksumFunc(receivedDatawords, n + 1, true);
        System.out.println("Received Checksum = " + receivedChecksum);

        if (Integer.parseInt(receivedChecksum, 16) == 0) {
            System.out.println("Data Successfully Transmitted ✅");
        } else {
            System.out.println("Data Corrupted ❌");
        }

        sc.close();
    }
}
