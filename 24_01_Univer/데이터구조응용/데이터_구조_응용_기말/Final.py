import cv2
import random
import numpy as np
import matplotlib.pyplot as plt
import pyautogui
from matplotlib.widgets import Button
import heapq

# 이미지 로드
imgList11 = ['num_1.png', 'num_2.png', 'num_3.png']
imgList12 = ['num_4.png', 'num_5.png', 'num_6.png']
imgList13 = ['num_7.png', 'num_8.png', 'num_0.png']

# 한칸만 움직이면됌
#imgList111 = ['num_1.png', 'num_2.png', 'num_3.png']
#imgList123 = ['num_4.png', 'num_5.png', 'num_0.png']
#imgList134 = ['num_7.png', 'num_8.png', 'num_6.png']

# 역순
#imgList114 = ['num_0.png', 'num_8.png', 'num_7.png']
#imgList125 = ['num_6.png', 'num_5.png', 'num_4.png']
#imgList136 = ['num_3.png', 'num_2.png', 'num_1.png']

imgList1 = imgList11 + imgList12 + imgList13
imgList2 = random.sample(imgList1, 9)

#imgList2 = imgList111 + imgList123 + imgList134

#imgList2 = imgList114 + imgList125 + imgList136

# 이미지 로드 헬퍼 함수
def load_images(imgList):
    return [cv2.imread(img) for img in imgList]

# 이미지 로드
images = load_images(imgList2)
img0 = cv2.imread('num_0.png')

# 이미지 표시 --> 3X3 형태로 가로 5 세로 5 크기인 사진 나열
fig, axes = plt.subplots(3, 3, figsize=(5, 5))

for i, ax in enumerate(axes.flat):
    ax.imshow(images[i])
    ax.axis('off')

# 지정된 위치에 이미지를 업데이트
def update_image(pos, new_img):
    images[pos] = new_img
    ax = axes.flat[pos]
    ax.clear()
    ax.imshow(new_img)
    ax.axis('off')
    # 다시 그리기
    plt.draw()

# 지정된 위치의 이미지를 교체
def swap_images(pos1, pos2):
    images[pos1], images[pos2] = images[pos2], images[pos1]
    update_image(pos1, images[pos1])
    update_image(pos2, images[pos2])

# 휴리스틱 함수
def heuristic(state):
    global imgList1

    # t는 state 리스트의 한개의 요소임
    #for index, t in enumerate(state) :
    #    print(f"{index + 1}: {state}")

    #for s, t in zip(state, imgList1):
    #    print(f"현 상태: {state}")
              #, 목표: {imgList1}")

    return sum(s != t for s, t in zip(state, imgList1))
# state = [1, 2, 3], target = [4, 5, 6]이라면 
# zip(state, target)의 결과는 [(1, 4), (2, 5), (3, 6)]이 되는데
# 1!=4, 2!=5, 3!=6 --> true true true 이렇게 반환 차이의 갯수를 반환하는거임

# 가능한 이동을 반환하는 함수
def get_neighbors(state):
    # 가능한 이동 한 후 상태를 저장할 리스트
    neighbors = []
    # 숫자 0의위치
    zero_index = state.index('num_0.png') # 이동 가능한 숫자 0을 지정
    # 0의 위치를 ?,?로 맹금
    row, col = divmod(zero_index, 3)

    def swap_and_create(new_index):
        #변경된 점을 원래거에 지장없이 변경
        new_state = state[:] 
        #쉽게 0이랑 자리 바꿈
        new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index] 
        neighbors.append(new_state) #리스트에 추가 바꾼 수
    
    # 빈 공간이 0을 뜻
    if row > 0: swap_and_create(zero_index - 3) #빈 공간이 맨위에 있지 않다 위쪽 ㄱㄱ
    if row < 2: swap_and_create(zero_index + 3) #빈 공간이 아래에 있지 않다 아래 ㄱㄱ
    if col > 0: swap_and_create(zero_index - 1) #빈 공간이 왼쪽에 있지 않다 왼쪽 ㄱㄱ
    if col < 2: swap_and_create(zero_index + 1) #빈 공간이 오른쪽에 있지않다 오른쪽 ㄱㄱ

    return neighbors

# A* 알고리즘
def astar(start, imgList1):
    frontier = [(heuristic(start), start)]
    # frontier를 힙 형태로 변환하는거
    heapq.heapify(frontier)
    came_from = {tuple(start): None}
    cost_so_far = {tuple(start): 0}

    while frontier:
        # 최솟값을 찾는 부분
        _, current = heapq.heappop(frontier)

        if current == imgList1:
            break
        # 숫자 0이 움직일 수 있는 위치임
        for neighbor in get_neighbors(current):
            # neighbor로 움직였으니 비용 하나 올림
            new_cost = cost_so_far[tuple(current)] + 1
            # 처음 방문한 위치 혹은 새로운 비용이 기존 비용보다 적을 때 우선 순위 갱쉰
            if tuple(neighbor) not in cost_so_far or new_cost < cost_so_far[tuple(neighbor)]:
                cost_so_far[tuple(neighbor)] = new_cost
                priority = new_cost + heuristic(neighbor)
                heapq.heappush(frontier, (priority, neighbor))
                came_from[tuple(neighbor)] = current
                #print(f"움직임 : {neighbor} 탐색 {current}")

    # 경로를 재구성
    path = []
    current = tuple(imgList1)
    while current != tuple(start):
        path.append(list(current))
        if current in came_from:
            current = tuple(came_from[current])
        else:
            print("경로를 찾을 수 없습니다.")
            return None
    path.reverse()
    return path

# 클릭 이벤트 핸들러
def add_point(event):
    # 마우스 왼쪽 클릭 확인
    if event.button == 1:
        fore = pyautogui.getActiveWindow()
        # 커서 위치
        pos = pyautogui.position()
        x = pos.x - fore.left
        y = pos.y - fore.top
        print("클릭 : ", x, ", ", y)
        
        # 75, 95 보정값 130은 셀 크기
        grid_x = (x - 75) // 130
        grid_y = (y - 95) // 130
        
        if 0 <= grid_x < 3 and 0 <= grid_y < 3:
            clicked_index = grid_y * 3 + grid_x
            # 클릭 위치가 0이 아닐때
            if imgList2[clicked_index] != 'num_0.png':
                # 십자에서 0번사진 찾기
                # 인접 셀 리스트 초기화
                near_cell = []
                # 왼
                if grid_x > 0:
                    near_cell.append(clicked_index - 1)
                # 오
                if grid_x < 2:
                    near_cell.append(clicked_index + 1)
                # 위
                if grid_y > 0:
                    near_cell.append(clicked_index - 3)
                # 아
                if grid_y < 2:
                    near_cell.append(clicked_index + 3)
                
                # 리스트에 4개의 셀에서 0을 찾으면 교환
                for near_index in near_cell :
                    if imgList2[near_index] == 'num_0.png':
                        # 클릭이랑 0이랑 교환 ㄱㄱ
                        swap_images(clicked_index, near_index)
                        imgList2[clicked_index], imgList2[near_index] = imgList2[near_index], imgList2[clicked_index]
                        break

# Solve 버튼
def solve_puzzle(event):
    # 클릭 이벤트가 button_ax1 여기에 발생 했는지 확인
    if event.inaxes == button_ax1:
        # 완성본
        global imgList1
        path = astar(imgList2, imgList1)
        if path is None:
            print("경로를 찾을 수 없습니다.")
            return
        
        # 경로 출력
        print("********************************************************************")
        print("찾은 경로:")
        for index, route in enumerate(path):
            print(f"{index + 1}: {route}")

        for state in path:
            # 현재 퍼즐 상태 업데이트
            imgList2[:] = state
            # 새로운 상태에 맞게 이미지 로드
            images[:] = load_images(imgList2)
            # 반복문을 이용해 이미지 업로드
            for i, ax in enumerate(axes.flat):
                # 축 지우기
                ax.clear()
                # 이미지 표시
                ax.imshow(images[i])
                # 격자? 눈금 지우는거
                ax.axis('off')
            #속도 조절은 이걸로하면 됌    
            plt.pause(0.1) 
        pyautogui.alert("완성")

# Random 버튼
def random_puzzle(event):
    # event.inaxes 는 마우스 이벤트 처리 라이브러리
    if event.inaxes == button_ax2:
        global imgList2, images
        imgList2 = random.sample(imgList1, 9)
        images = load_images(imgList2)
        for i, ax in enumerate(axes.flat):
            ax.clear()
            ax.imshow(images[i])
            ax.axis('off')
        plt.draw()
        print("재시작")

# 버튼 생성 첫 번째 버튼 (Solve)
button_ax1 = plt.axes([0.1, 0.02, 0.15, 0.05])
button1 = Button(button_ax1, 'Solve')

# 두 번째 버튼 (Random)
button_ax2 = plt.axes([0.8, 0.02, 0.15, 0.05])
button2 = Button(button_ax2, 'Random')

# 버튼 클릭 이벤트 핸들러 연결
button1.on_clicked(solve_puzzle)
button2.on_clicked(random_puzzle)

# 이벤트 연결
cid = plt.connect('button_press_event', add_point)
plt.subplots_adjust(wspace=0.01, hspace=0.02)
plt.show()
