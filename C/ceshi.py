from gmpy2 import invert

K = 1074
S = 43
inv = invert(S, K) # 求模逆元

# 背包密码解密
# 这个背包是最重的物件对应每字节8bit里的第1个bit，依此类推
def unpack(num):
    A = [175, 87, 44, 21, 11, 5, 3, 1]
    res = ''
    for i in range(8):
        if num >= A[i]:
            # res = '1' + res
            res = res + '1'
            num -= A[i]
        else:
            # res = '0' + res
            res = res + '0'
    return int(res, 2)

C = [1817, 3100, 2240, 868, 172, 1816, 2025, 50, 172, 2289, 1642, 2067, 1337, 1681, 655, 2588, 691, 2591, 1595, 1552, 2498, 1513, 609, 1075, 602, 1420, 2720, 1042, 947, 2160, 731]

# 对密文直接进行背包解密
tmp = []
for i in C:
    tmp += [unpack(i * inv % K)]
# 由于使用了CBC模式，解密结果要异或其上一位密文或初始向量
# 明文第1位不是flag，所以从第2位开始直接异或上一位密文后8位即可
for i in range(1, len(tmp)):
    print(chr(tmp[i] ^ C[i-1] % 256), end = '')

