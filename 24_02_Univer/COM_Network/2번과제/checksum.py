# """
# 0. 다항식을 입력 받음
# 1. 다항식을 "+"기준으로 나눠줌
# 2. 더해줄 0의 갯수를 구하기 위해 최고차항 수 구함
# 3. 다항식을 2진수로 변환해줌
# 4. 전송 데이터를 입력받음
# 5. 최고 차항 수 만큼 0을 붙여줌
# 6. 전송 데이터(2진수+0)와 다항식(2진수)을 XOR연산을하고 몫과 나머지?를 구함
# 7. 나머지를 원래 전송데이터 뒤에 붙임
# 8. 계산을 할거임 다항식과 전송데이터를 xor(베타)연산을 함
# - 우선 다항식이 전송 데이터보다 길다? 그럼 계산 끝
# - 아니다? 그러면 길이 차이 만큼 전송 데이터 뒤에 0을 추가해줌
# - b가 다항식 전송 데이터 길이 만큼 계산
# - 다르면 1 같으면 0
# - 그리고 계산 값에 1을 찾아서 자름
# """
# Max_num =0
# def poly_to_binary(polynomial):
#     # 항을 '+' 기준으로 분리
#     terms = polynomial.replace(' ', '').split('+')
#     binary_representation = 0
#     global Max_num
    
#     # 각 항을 확인하며 비트를 설정
#     for term in terms:
#         if 'x' in term:
#             # 'x' 다음의 숫자를 차수로 해석 (예: x5 → 5)
#             power = int(term[1:])
#             Max_num = max(Max_num, power)
#             # 해당 차수에 맞는 비트를 설정
#             binary_representation |= (1 << power)
#         else:
#             # 상수항인 경우 (1)
#             binary_representation |= 1
    
#     return binary_representation, Max_num

# # 사용자 입력
# user_input = input("다항식 입력: ")

# # 이진수로 변환하여 출력
# binary_output, Max_num = poly_to_binary(user_input)
# print(f"다항식 --> 2진수: {format(binary_output, 'b')}")

# binary_output_str = format(binary_output, 'b')

# print("최고차항 수: ", Max_num)

# # 사용자 입력
# user_input2 = input("전송 데이터 입력: ")
# data_normal = user_input2
# print("전송 데이터 값",user_input2)

# # 최고차항 수만큼 0을 데이터에 추가
# data_plus_zeros = user_input2 + '0' * Max_num

# # 결과 출력
# print(f"전송 데이터 값 (최고차항 수만큼 0 추가): {data_plus_zeros}")

# """
# 8. 계산을 할거임 다항식과 전송데이터를 xor(베타)연산을 함
# - 우선 다항식이 전송 데이터보다 길다? 그럼 계산 끝
# - 아니다? 그러면 길이 차이 만큼 전송 데이터 뒤에 0을 추가해줌
# - b가 다항식 전송 데이터 길이 만큼 계산
# - 다르면 1 같으면 0
# - 그리고 계산 값에 1을 찾아서 자름
# data_plus_zeros 전송 데이터
# binary_output 다항식
# """

# print(data_plus_zeros)
# print(binary_output_str)

# def crc(data_plus_zeros, binary_output_str):
#     bcal = ""
#     key = binary_output_str
#     if len(binary_output_str) > len(data_plus_zeros):
#         return data_plus_zeros
#     else:
#         gap = len(data_plus_zeros) - len(binary_output_str)
#         for i in range(gap):
#              binary_output_str += "0"
#     """
#     다르면 1 같으면 0
#     100101 다항식
#     101101001 전송데이터
#     갭 더하기
#     100101000 다항식
#     101101001 전송데이터
#     계산 
#     """
#     for i in range(len(data_plus_zeros)):
#         if binary_output_str[i] == data_plus_zeros[i]:
#             bcal += "0"
#         else :
#             bcal += "1"

#     bcal = bcal[bcal.find("1"):] # 1을 찾아서 자름
#     return crc(bcal, key)

# result = crc(data_plus_zeros, binary_output_str)
# print(Max_num)
# data_plus_zeros = user_input2 + '0' * (Max_num-1)
# print("결과", data_plus_zeros+result)

Max_num =0
def poly_to_binary(polynomial):
    # 항을 '+' 기준으로 분리
    terms = polynomial.replace(' ', '').split('+')
    binary_representation = 0
    global Max_num
    
    # 각 항을 확인하며 비트를 설정
    for term in terms:
        if 'x' in term:
            # 'x' 다음의 숫자를 차수로 해석 (예: x5 → 5)
            power = int(term[1:])
            Max_num = max(Max_num, power)
            # 해당 차수에 맞는 비트를 설정
            binary_representation |= (1 << power)
        else:
            # 상수항인 경우 (1)
            binary_representation |= 1
    
    return binary_representation, Max_num

# 사용자 입력
user_input = input("다항식 입력: ")

# 이진수로 변환하여 출력
binary_output, Max_num = poly_to_binary(user_input)
print(f"다항식 --> 2진수: {format(binary_output, 'b')}")

binary_output_str = format(binary_output, 'b')

print("최고차항 수: ", Max_num)

# 사용자 입력
user_input2 = input("전송 데이터 입력: ")
data_normal = user_input2
print("전송 데이터 값",user_input2)

# 최고차항 수만큼 0을 데이터에 추가
data_plus_zeros = user_input2 + '0' * Max_num

# 결과 출력
print(f"전송 데이터 값 (최고차항 수만큼 0 추가): {data_plus_zeros}")

def crc(data_plus_zeros, binary_output_str,cnt =1):
    bcal = ""
    
    key = binary_output_str
    if len(binary_output_str) > len(data_plus_zeros):
        return data_plus_zeros
    else:
        gap = len(data_plus_zeros) - len(binary_output_str)
        for i in range(gap):
             binary_output_str += "0"

    for i in range(len(data_plus_zeros)):
        if binary_output_str[i] == data_plus_zeros[i]:
            bcal += "0"
        else :
            bcal += "1"
    print("연산["+str(cnt)+"회]""값",bcal)
    bcal = bcal[bcal.find("1"):] # 1을 찾아서 자름
    cnt +=1
    return crc(bcal, key, cnt)

result = crc(data_plus_zeros, binary_output_str)
data_plus_zeros = user_input2 + '0' * (Max_num-1)
print("결과", data_plus_zeros+result)