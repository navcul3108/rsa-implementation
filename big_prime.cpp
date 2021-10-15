#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;


ZZ getRandomPosiblePrime(long);
bool rabinMillerTest(ZZ, long);

int main()
{
    int bitsLenght = 500;
    int numberOfTest = 20;
    while (true) {
        ZZ possilePrime = getRandomPosiblePrime(bitsLenght);
        if (rabinMillerTest(possilePrime, numberOfTest)) {
            std::cout << possilePrime;
            break;
        }
    }
}

ZZ getRandomPosiblePrime(long bitsLenght) {
    ZZ possiblePrime;
    RandomBits(possiblePrime, bitsLenght);

    // make sure MSB & LSB value are 1

    possiblePrime |= (1 << (bitsLenght - 1)) | 1;
    return possiblePrime;
}

bool rabinMillerTest(ZZ possiblePrime, long numberOfTests) {
    ZZ q = ZZ(possiblePrime - 1);
    ZZ r = ZZ(1);

    // possiblePrime  - 1 = q(r^2)

    while ((q & 1) == 0) {
        r += 1;
        q /= 2;
    }
    for (long i = 1; i <= numberOfTests; ++i) {
        ZZ a;
        RandomBnd(a, possiblePrime);
        ZZ remainder = PowerMod(a, q, possiblePrime);
        if (remainder == 1 || remainder == (possiblePrime - 1)) {
            continue;
        }
        ZZ j = ZZ(0);
        for (j; j <= r; ++j) {

            // not need to calculate a^(q * 2^r) because remainder = a^q and 2^r is calculated cumulatively

            remainder = PowerMod(remainder, 2, possiblePrime);
            if (remainder == (possiblePrime - 1)) {
                break;
            }
            else {
                return false;
            }
        }
    }
    return true;
}