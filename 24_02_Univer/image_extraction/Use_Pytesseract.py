# from PIL import Image
# import pytesseract

# # Tesseract 실행 경로 설정 (Windows에서만 필요합니다)
# #pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'

# # 이미지 불러오기
# image_path = "C:/Users/Moon/Desktop/Test_image.png"  # 이미지 파일 경로
# image = Image.open(image_path)

# # OCR로 텍스트 추출
# extracted_text = pytesseract.image_to_string(image)

# # 추출된 텍스트 출력
# print(extracted_text)


from PIL import Image
import pytesseract

image_path = "D:/Git_Hub/24_02_Univer/image_extraction/죽는 날까지 하늘을 우러러001.png"

pytesseract.pytesseract.tesseract_cmd = r'C:\Users\Moon\AppData\Local\tesseract.exe'

text = pytesseract.image_to_string(Image.open(image_path), lang='Eng+kor')

print(text)