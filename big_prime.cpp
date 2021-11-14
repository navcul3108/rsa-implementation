#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;


ZZ getRandomPosiblePrime(long);
bool rabinMillerTest(ZZ, long);

int main()
{
    int bitsLenght = 500;
    std::cout << getRandomPosiblePrime(bitsLenght);
}

ZZ getRandomNumber(long bitsLength) {
    ZZ possiblePrime;
    RandomBits(possiblePrime, bitsLength);

    // make sure MSB & LSB value are 1

    possiblePrime |= (1 << (bitsLength - 1)) | 1;
    return possiblePrime;
}

ZZ getRandomPosiblePrime(long bitsLength) {
    int numberOfTest = 20;
    while (true) {
        ZZ possilePrime = getRandomNumber(bitsLength);
        if (rabinMillerTest(possilePrime, numberOfTest)) {
            return possilePrime;
        }
    }
}

ZZ powerMod(const ZZ& base, const ZZ& exponent, const ZZ& module) {
    ZZ r = ZZ(1);
    ZZ ex = ZZ(exponent);
    ZZ b = ZZ(base);
    while (ex > 0) {
        if ((ex & 1) == 1) {
            r = r * b % module;
        }
        ex = ex / 2;
        b = b * (b % module);
    }
    return r;
}

bool rabinMillerTest(ZZ possiblePrime, long numberOfTests) {
    ZZ q = ZZ(possiblePrime - 1);
    ZZ r = ZZ(1);
    ZZ base = ZZ(2);
    // possiblePrime  - 1 = q(r^2)

    while ((q & 1) == 0) {
        r += 1;
        q /= 2;
    }
    for (long i = 1; i <= numberOfTests; ++i) {
        ZZ a;
        RandomBnd(a, possiblePrime);
        ZZ remainder = powerMod(a, q, possiblePrime);
        if (remainder == 1 || remainder == (possiblePrime - 1)) {
            continue;
        }
        ZZ j = ZZ(0);
        for (j; j <= r; ++j) {

            // not need to calculate a^(q * 2^r) because remainder = a^q and 2^r is calculated cumulatively
            remainder = powerMod(remainder, base, possiblePrime);
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