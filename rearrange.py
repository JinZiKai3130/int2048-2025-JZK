import sys

def rearrange_data():
    # 读取所有输入数据
    data = list(map(int, sys.stdin.read().split()))
    
    # 确保有2000个整数
    if len(data) < 2000:
        return
    
    # 分割被除数和除数
    dividends = data[:1000]
    divisors = data[1000:2000]
    
    # 重新排列：被除数1, 除数1, 被除数2, 除数2, ...
    rearranged = []
    for i in range(1000):
        rearranged.append(dividends[i])
        rearranged.append(divisors[i])
    
    # 输出重排后的数据
    for num in rearranged:
        print(num)

if __name__ == "__main__":
    rearrange_data()