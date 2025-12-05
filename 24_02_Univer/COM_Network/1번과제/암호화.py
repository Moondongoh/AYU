# # 1. 키값을 .txt파일로 생성 a~z
# # 2. 키값을 읽어서 원문을 암호문으로 변환
# # 3. 키값을 읽어서 암호문을 읽어서 원문으로 변환
# # 키값 .txt, 원본 > 암호문, 암호문 > 원본 3가지 소스? 제작물
# # *표지* 과목명,교수명,학생명,제출일자,소스코드와 실행결과 있어야함.
# # *핵심* a~z의 갯수를 각각 셈 > 정렬 이후 정렬 된 순서로 a~z까지 매칭(암호화) | 
# # 대소문자 구분 x
# # ++ 체크썸 계산

# alp= {'a': 0, 'b': 0, 'c': 0, 'd': 0, 'e': 0, 'f': 0, 'g': 0, 'h': 0, 'i': 0, 'j': 0, 'k': 0,
#        'l': 0, 'm': 0, 'n': 0, 'o': 0, 'p': 0, 'q': 0, 'r': 0, 's': 0, 't': 0, 'u': 0, 'v': 0,
#        'w': 0, 'x': 0, 'y': 0, 'z': 0}
# alpabet= ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
#            'w', 'x', 'y', 'z']

# alp_s= [] 
# key_s= []

# # 암호화할 파일을 읽어서 저장
# # 첫 번째 파일에서 내용을 읽고 소문자로 변환
# f = open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/test.txt', 'r')
# sen = f.read().lower()  # 함수 호출에 괄호 필요
# f.close()

# # 두 번째 파일에 내용을 쓰기
# f = open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'w')
# for i in sen:
#     f.write(i)  # sen의 각 문자를 파일에 기록
# f.close()

# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/test.txt', 'r')    
# sen= list(sen)
# for i in sen:
#     if i in alp:  
#         alp[i] += 1
# f.close()
# # 키 값을 파일로 저장
# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'w')
# for i in alp:
#     f.write(str(alp[i]) + "\n") 
# f.close()

# print(alp)

# # 암호화 
# alp_s= sorted(alp, key=lambda x: alp[x], reverse=True)
# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/encode.txt', 'w')
# for i in sen:
#     if 96< ord(i) < 123: 
#         temp= ord(i) - 97 
#         f.write(alp_s[temp])  
#     else:
#         f.write(i)
# f.close()

# # 해독하기 위해 키 파일 읽어오기
# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'r')
# temp= f.read()
# key_s= temp.split('\n')
# for i in range(0, 26):
#     alp[alpabet[i]] = int(key_s[i])
# dec_alp= sorted(alp, key=lambda x: alp[x], reverse=True)
# # 해독할 파일 내용 읽어오기
# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/encode.txt', 'r')
# password= f.read()
# f.close()
# # 키 값을 이용해 복호화 시작
# f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/decode.txt', 'w')
# for i in password:
#     if 96< ord(i) < 123: 
#         for j in range(0, 26):
#             if i== dec_alp[j]:  
#                 f.write(alpabet[j])  
#     else:
#         f.write(i)
# f.close()

# 1. 키값을 .txt파일로 생성 a~z
# 2. 키값을 읽어서 원문을 암호문으로 변환
# 3. 키값을 읽어서 암호문을 읽어서 원문으로 변환
# 키값 .txt, 원본 > 암호문, 암호문 > 원본 3가지 소스? 제작물
# *표지* 과목명,교수명,학생명,제출일자,소스코드와 실행결과 있어야함.
# *핵심* a~z의 갯수를 각각 셈 > 정렬 이후 정렬 된 순서로 a~z까지 매칭(암호화) | 
# 대소문자 구분 x
# ++ 체크썸 계산

alp= {'a': 0, 'b': 0, 'c': 0, 'd': 0, 'e': 0, 'f': 0, 'g': 0, 'h': 0, 'i': 0, 'j': 0, 'k': 0,
       'l': 0, 'm': 0, 'n': 0, 'o': 0, 'p': 0, 'q': 0, 'r': 0, 's': 0, 't': 0, 'u': 0, 'v': 0,
       'w': 0, 'x': 0, 'y': 0, 'z': 0}
alpabet= ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
           'w', 'x', 'y', 'z']

alp_s= [] 
key_s= []

f = open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/test.txt', 'r')
sen = f.read().lower()
f.close()

f = open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'w')
for i in sen:
    f.write(i) 
f.close()

f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/test.txt', 'r')    
sen= list(sen)
for i in sen:
    if i in alp:  
        alp[i] += 1
f.close()
f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'w')
for i in alp:
    f.write(str(alp[i]) + "\n") 
f.close()

print(alp)

alp_s= sorted(alp, key=lambda x: alp[x], reverse=True)
f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/encode.txt', 'w')
for i in sen:
    if 96< ord(i) < 123: 
        temp= ord(i) - 97 
        f.write(alp_s[temp])  
    else:
        f.write(i)
f.close()

f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/key.txt', 'r')
temp= f.read()
key_s= temp.split('\n')
for i in range(0, 26):
    alp[alpabet[i]] = int(key_s[i])
dec_alp= sorted(alp, key=lambda x: alp[x], reverse=True)
f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/encode.txt', 'r')
password= f.read()
f.close()
f= open('D:/Git_Hub/24_02_Univer/COM_Network/1번과제/decode.txt', 'w')
for i in password:
    if 96< ord(i) < 123: 
        for j in range(0, 26):
            if i== dec_alp[j]:  
                f.write(alpabet[j])  
    else:
        f.write(i)
f.close()