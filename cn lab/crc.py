def crc_remainder(message_bits: str, generator_bits: str) -> str:
    g = int(generator_bits, 2)
    r = len(generator_bits) - 1
    value = int(message_bits, 2) << r
    while value.bit_length() >= len(generator_bits):
        shift = value.bit_length() - len(generator_bits)
        value ^= (g << shift)
    return format(value, f'0{r}b')


def generate_codeword(message_bits: str, generator_bits: str):
    fcs = crc_remainder(message_bits, generator_bits)
    return message_bits + fcs, fcs


def verify_codeword(codeword_bits: str, generator_bits: str) -> tuple[str, bool]:
    rem = crc_remainder(codeword_bits, generator_bits)
    return rem, rem == '0' * (len(generator_bits) - 1)


def flip_bit(bitstring: str, index: int) -> str:
    b = list(bitstring)
    b[index] = '1' if b[index] == '0' else '0'
    return ''.join(b)


message = "1101011011111001"
generator = "1011"

codeword, fcs = generate_codeword(message, generator)
print("=== SENDER SIDE ===")
print("Original Message: ", message)
print("Generator:        ", generator)
print("FCS (3 bits):     ", fcs)
print("Codeword:         ", codeword)

rem0, ok0 = verify_codeword(codeword, generator)
print("\n=== RECEIVER SIDE (NO ERROR) ===")
print("Received Codeword:        ", codeword)
print("Remainder after division: ", rem0)
print("OK?: ", "No error" if ok0 else "Error")

corrupted = flip_bit(codeword, 4)
rem1, ok1 = verify_codeword(corrupted, generator)
print("\n=== RECEIVER SIDE (WITH ERROR) ===")
print("Corrupted Codeword:       ", corrupted)
print("Remainder after division: ", rem1)
print("OK?: ", "No error" if ok1 else "Error")
