#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Function 1: Decrypt text with given shift
void decrypt(char text[], int shift, char result[]) {
    int i;
    for(i = 0; text[i]!= '\0'; i++) {
        if(isalpha(text[i])) {
            char base = isupper(text[i])? 'A' : 'a';
            // +26 to handle negative, %26 for wrap around
            result[i] = (text[i] - base - shift + 26) % 26 + base;
        } else {
            result[i] = text[i]; // space, numbers same rehne do
        }
    }
    result[i] = '\0';
}

// Function 2: DSA - Frequency count of letters
void countFrequency(char text[], int freq[]) {
    // Initialize array
    for(int i = 0; i < 26; i++) freq[i] = 0;

    for(int i = 0; text[i]!= '\0'; i++) {
        if(isalpha(text[i])) {
            char ch = tolower(text[i]);
            freq[ch - 'a']++; // 'a'=0, 'b'=1,... 'z'=25
        }
    }
}

// Function 3: Find most frequent letter - DSA concept
char mostFrequentLetter(int freq[]) {
    int max = 0, index = 0;
    for(int i = 0; i < 26; i++) {
        if(freq[i] > max) {
            max = freq[i];
            index = i;
        }
    }
    return 'a' + index;
}

int main() {
    char encrypted[MAX], decrypted[MAX];
    int freq[26];

    printf("=== Caesar Cipher Breaker - BCA Cyber Security ===\n");
    printf("Enter encrypted text: ");
    fgets(encrypted, MAX, stdin);
    encrypted[strcspn(encrypted, "\n")] = '\0'; // remove newline

    printf("\nBrute Force All 25 Shifts:\n");
    printf("----------------------------------------\n");

    int bestShift = 0, maxE = 0;

    for(int shift = 1; shift <= 25; shift++) {
        decrypt(encrypted, shift, decrypted);
        countFrequency(decrypted, freq);
        int eCount = freq['e' - 'a']; // Count of 'e'

        printf("Shift %2d: %s | E count: %d\n", shift, decrypted, eCount);

        // DSA logic: jis shift me 'E' sabse zyada, woh answer ho sakta
        if(eCount > maxE) {
            maxE = eCount;
            bestShift = shift;
        }
    }

    printf("----------------------------------------\n");
    decrypt(encrypted, bestShift, decrypted);
    printf("\nMost Likely Answer:\n");
    printf("Shift: %d\n", bestShift);
    printf("Decrypted: %s\n", decrypted);

    countFrequency(decrypted, freq);
    printf("Most frequent letter: %c\n", mostFrequentLetter(freq));
    printf("\nNote: In English, 'E' is most common. So high E count = correct shift\n");

    return 0;
}