import sys
import pyfiglet
from typing import Union, Optional


def draw_text_art(
        text: Union[str, int, float],
        font: str = "standard",
        chr_map: Optional[str] = None
) -> None:
    """
    입력된 텍스트를 ASCII Art 그림으로 변환하여 stdout에 출력하는 함수

    Args:
        text: 그림으로 그릴 내용 (문자열, 숫자 등)
        font: 사용할 Figlet 폰트 이름 (기본값: "standard")
              'slant', '3-d', 'alphabet', 'banner' 등 다양함
        chr_map: (선택 사항) 기본 폰트의 문자를 대체할 문자셋 (예: "+-./")
    """
    # 1. 입력을 문자열로 변환
    content: str = str(text)

    try:
        # 2. pyfiglet을 사용하여 아스키 아트 생성
        figlet_obj = pyfiglet.Figlet(font=font)
        art_text: str = figlet_obj.renderText(content)

        # 3. (옵션) 사용자가 원하는 문자셋으로 치환 (그림 효과)
        if chr_map:
            # 기본 아스키 아트에서 사용된 문자들을 수집
            original_chars = set(art_text.replace(" ", "").replace("\n", ""))
            mapped_text = art_text

            # 입력된 chr_map의 문자들을 순환하며 치환
            map_len = len(chr_map)
            for i, char in enumerate(original_chars):
                # 문자들을 chr_map의 문자로 돌아가며 바꿈 (패턴 효과)
                replacement = chr_map[i % map_len]
                mapped_text = mapped_text.replace(char, replacement)

            final_output = mapped_text
        else:
            final_output = art_text

        # 4. stdout으로 출력
        sys.stdout.write(final_output)
        sys.stdout.flush()

    except pyfiglet.FontNotFound:
        sys.stderr.write(f"Error: Font '{font}' not found.\n")
    except Exception as e:
        sys.stderr.write(f"An unexpected error occurred: {e}\n")


if __name__ == "__main__":
    # --- 데모 시작 ---

    # 1. 기본 폰트 사용 데모
    print("\n--- Demo 1: Standard Font ---")
    draw_text_art("GAT-ML")

    # 2. 'slant' 폰트와 숫자(Scalar) 입력 데모 (기울어진 스타일)
    print("\n--- Demo 2: Slant Font with Numbers ---")
    draw_text_art(20260411, font="slant")

    # 3. '3-d' 폰트와 사용자 지정 문자 매핑 (+-./) 데모
    # 글자의 표면을 사용자가 지정한 문자로 채워 그림 효과를 냅니다.
    print("\n--- Demo 3: 3-D Font with Custom Character Mapping (+-./) ---")
    draw_text_art("SENSOR", font="3-d", chr_map="+-./")

    # 4. 'banner' 폰트 사용 데모 (거대한 스타일)
    print("\n--- Demo 4: Banner Font (Large) ---")
    draw_text_art("D O N E", font="banner")